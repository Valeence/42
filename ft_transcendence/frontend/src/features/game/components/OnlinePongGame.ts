import { Pong3D } from './Pong3D/Pong3DEngine.js';
import { userAuthenticationService } from '@/features/auth/services/userAuthenticationService.js';
import { MatchService } from '../services/matchService.js';
import { ApiConfig } from '../../../config/api.js';
import { GameEndModal, convertToModalStats } from './MatchResultModal.js';
import type { ArenaSettings } from '@/types/index.js';
import { DevConsole } from '@/utils/devConsole.js';

export class RemotePong extends Pong3D {
  private signalingWS: WebSocket | null = null;
  private peerConnection: RTCPeerConnection | null = null;
  private dataChannel: RTCDataChannel | null = null;
  private isHost: boolean = false;
  private playerId: string = '';
  private matchId: string = '';
  private opponentId: string = '';
  private opponentUsername: string = '';
  private opponentUserId: number | null = null;
  private guestInputs = { up: false, down: false };
  private gameEndedByDisconnection = false;
  private gameWasInterrupted = false;
  private beforeUnloadHandler: ((event: BeforeUnloadEvent) => void) | null = null;
  private visibilityChangeHandler: (() => void) | null = null;
  private navigationHandler: ((event: CustomEvent) => void) | null = null;

  constructor(canvasId: string, settings: ArenaSettings) {
    super(canvasId, settings, true, 'remote');
    this.playerId = `player_${Date.now()}_${Math.random().toString(36).substring(2, 11)}`;
    this.checkForGameInterruption();
    if (this.gameWasInterrupted) {
      DevConsole.print('🚫 Game was interrupted, skipping initialization');
      return;
    }
    this.setupPageLeaveDetection();
    DevConsole.print('🎮 RemotePong initialized, gameWasInterrupted:', this.gameWasInterrupted);
  }

  private checkForGameInterruption(): void {
    const wasInGame = sessionStorage.getItem('remote_game_active');
    const gameData = sessionStorage.getItem('remote_game_data');
    if (wasInGame === 'true' && gameData) {
      DevConsole.print('🔄 Detected page refresh during remote game');
      this.gameWasInterrupted = true;
      this.hideGameInterface();
      let opponentName = 'Adversaire';
      try {
        const data = JSON.parse(gameData);
        DevConsole.print('📊 Previous game data:', data);
        opponentName = data.opponentUsername || opponentName;
        if (window.location.pathname === '/game') return;
      } catch (error) {
        DevConsole.reportError('❌ Failed to parse game data:', error);
      }
      setTimeout(() => this.showGameInterruptionModal(opponentName), 100);
    }
  }

  private hideGameInterface(): void {
    DevConsole.print('🙈 Hiding game interface');
    ['game-status', 'connection-status', 'game-overlay', 'cancel-matchmaking', 'leave-game'].forEach(id => {
      const el = document.getElementById(id);
      if (el) {
        el.style.display = 'none';
        el.style.visibility = 'hidden';
      }
    });
    document.querySelectorAll('canvas').forEach(canvas => {
      if (canvas instanceof HTMLCanvasElement) {
        canvas.style.display = 'none';
        canvas.style.visibility = 'hidden';
      }
    });
  }

  public async startRemoteGame(): Promise<void> {
    if (this.gameWasInterrupted) return DevConsole.print('🚫 Preventing matchmaking due to interruption');
    DevConsole.print('🌐 Starting remote game...');
    this.updateGameStatus("Connecting to server...");
    try {
      await this.connectToSignalingServer();
      this.joinMatchmaking();
    } catch (error) {
      DevConsole.reportError('❌ Failed to start remote game:', error);
      this.updateGameStatus("Connection failed");
    }
  }

  private async connectToSignalingServer(): Promise<void> {
    return new Promise((resolve, reject) => {
      const wsUrl = ApiConfig.WS_URL;
      DevConsole.print('🔗 Connecting to WebSocket:', wsUrl);
      ApiConfig.logUrls();
      this.signalingWS = new WebSocket(wsUrl);

      this.signalingWS.onopen = () => {
        DevConsole.print('✅ Connected to signaling server');
        resolve();
      };

      this.signalingWS.onmessage = (event) => this.handleSignalingMessage(JSON.parse(event.data));
      this.signalingWS.onclose = () => this.handleSignalingDisconnect();
      this.signalingWS.onerror = (error) => reject(DevConsole.reportError('❌ Signaling server error:', error));

      setTimeout(() => {
        if (this.signalingWS?.readyState !== WebSocket.OPEN) reject(new Error('Connection timeout'));
      }, 10000);
    });
  }

  private joinMatchmaking(): void {
    if (!this.signalingWS || this.gameWasInterrupted) return;
    const currentUser = userAuthenticationService.getCurrentUser();
    const username = currentUser?.username || 'Guest';
    const userId = currentUser?.id;
    this.showCurrentGameSettings();

    this.signalingWS.send(JSON.stringify({
      type: 'join_matchmaking',
      playerId: this.playerId,
      username,
      userId,
      gameSettings: {
        ballSpeed: this.settings.ballSpeed,
        winScore: this.settings.winScore,
        enableEffects: this.settings.enableEffects
      }
    }));
    this.updateGameStatus("Searching for opponent...");
  }

  private showCurrentGameSettings(): void {
    const statusEl = document.getElementById('game-status');
    if (!statusEl) return;
    statusEl.innerHTML = `
      <div class="text-center space-y-3">
        <div class="text-lg text-blue-400">🔍 Recherche d'un adversaire...</div>
        <div class="text-sm text-gray-300">
          <div class="font-medium text-blue-200 mb-2">Vos paramètres (en tant qu'hôte) :</div>
          <div>⚡ ${this.getSpeedDisplayName(this.settings.ballSpeed)}</div>
          <div>🏆 ${this.settings.winScore} points</div>
        </div>
        <div class="text-xs text-gray-400 italic">
          L'adversaire recevra ces paramètres automatiquement
        </div>
      </div>
    `;
  }

  private async handleSignalingMessage(message: any): Promise<void> {
    DevConsole.print('📨 Signaling message:', message.type);
    switch (message.type) {
      case 'waiting_opponent':
        this.updateGameStatus("Waiting for opponent...");
        break;
      case 'match_found':
        await this.handleMatchFound(message);
        break;
      case 'webrtc_offer':
        await this.handleWebRTCOffer(message);
        break;
      case 'webrtc_answer':
        await this.handleWebRTCAnswer(message);
        break;
      case 'webrtc_ice_candidate':
        await this.handleICECandidate(message);
        break;
      case 'opponent_disconnected':
        DevConsole.print(`❌ Opponent disconnected: ${message.disconnectedPlayer} (${message.reason})`);
        this.updateGameStatus("Opponent disconnected");
        this.handleOpponentDisconnection(message.reason || 'unknown');
        break;
    }
  }

  private async handleMatchFound(message: any): Promise<void> {
    this.matchId = message.matchId;
    this.isHost = message.role === 'host';
    this.opponentId = message.opponent.id;
    this.opponentUsername = message.opponent.username;
    this.opponentUserId = message.opponent.userId;

    if (!this.isHost) {
      this.gameState.status = 'playing';
      this.saveGameStateToSession();
    }

    this.updateGameStatus("Setting up connection...");
    await this.setupWebRTCConnection();
  }

  private handleSignalingDisconnect(): void {
    DevConsole.print('📡 Signaling server disconnected');
    if (this.gameState.status === 'playing' && !this.gameEndedByDisconnection) {
      this.updateGameStatus("Connection lost");
      if (!this.dataChannel || this.dataChannel.readyState !== 'open') {
        setTimeout(() => {
          if (!this.gameEndedByDisconnection) this.handleOpponentDisconnection('signaling_disconnect');
        }, 5000);
      }
    }
  }

  private async setupWebRTCConnection(): Promise<void> {
    this.peerConnection = new RTCPeerConnection({
      iceServers: [{ urls: 'stun:stun.l.google.com:19302' }, { urls: 'stun:stun1.l.google.com:19302' }]
    });

    this.peerConnection.onicecandidate = (event) => {
      if (event.candidate && this.signalingWS) {
        this.signalingWS.send(JSON.stringify({ type: 'webrtc_ice_candidate', candidate: event.candidate }));
      }
    };

    if (this.isHost) {
      this.dataChannel = this.peerConnection.createDataChannel('gameData', { ordered: false, maxRetransmits: 0 });
      this.setupDataChannelHandlers();
      const offer = await this.peerConnection.createOffer();
      await this.peerConnection.setLocalDescription(offer);
      this.signalingWS?.send(JSON.stringify({ type: 'webrtc_offer', offer }));
    } else {
      this.peerConnection.ondatachannel = (event) => {
        this.dataChannel = event.channel;
        this.setupDataChannelHandlers();
      };
    }
  }

  private setupDataChannelHandlers(): void {
    if (!this.dataChannel) return;
    this.dataChannel.onopen = () => {
      DevConsole.print('🔗 WebRTC P2P connection established');
      if (this.isHost) {
        this.sendGameSettingsToGuest();
        this.updateGameStatus("Starting game...");
        this.startGameAsHost();
      } else {
        this.updateGameStatus("Waiting for host...");
      }
    };

    this.dataChannel.onmessage = (event) => this.handleP2PMessage(JSON.parse(event.data));
    this.dataChannel.onclose = () => {
      DevConsole.print('❌ P2P connection closed unexpectedly');
      if (this.gameState.status === 'playing' && !this.gameEndedByDisconnection) {
        this.handleOpponentDisconnection('connection_lost');
      }
    };
    this.dataChannel.onerror = (error) => {
      DevConsole.reportError('❌ P2P connection error:', error);
      if (this.gameState.status === 'playing' && !this.gameEndedByDisconnection) {
        this.handleOpponentDisconnection('connection_error');
      }
    };
  }

  private async handleWebRTCOffer(message: any): Promise<void> {
    if (!this.peerConnection) return;
    await this.peerConnection.setRemoteDescription(message.offer);
    const answer = await this.peerConnection.createAnswer();
    await this.peerConnection.setLocalDescription(answer);
    this.signalingWS?.send(JSON.stringify({ type: 'webrtc_answer', answer }));
  }

  private async handleWebRTCAnswer(message: any): Promise<void> {
    if (!this.peerConnection) return;
    await this.peerConnection.setRemoteDescription(message.answer);
  }

  private async handleICECandidate(message: any): Promise<void> {
    if (!this.peerConnection) return;
    await this.peerConnection.addIceCandidate(message.candidate);
  }

  private startGameAsHost(): void {
    this.settings.player1Name = userAuthenticationService.getCurrentUser()?.username || 'Host';
    this.settings.player2Name = this.opponentUsername;
    this.startLocalGame();
    this.startGameUpdateLoop();
  }

  private startGameUpdateLoop(): void {
    if (!this.isHost) return;
    const sendUpdate = () => {
      if (this.dataChannel?.readyState === 'open') {
        const positions = this.physics.getPositions();
        const gameUpdate = {
          type: 'game_update',
          state: { ball: positions.ball, paddles: { player1Paddle: positions.player1Paddle, player2Paddle: positions.player2Paddle }, scores: this.gameState.scores, timer: this.gameState.timer, status: this.gameState.status, winner: this.gameState.winner }
        };
        this.dataChannel.send(JSON.stringify(gameUpdate));
      }
      if (this.gameState.status !== 'finished') requestAnimationFrame(sendUpdate);
    };
    sendUpdate();
  }

  protected updateGame(): void {
    if (!this.isHost) return this.sendContinuousInputToHost();
    const hostInputs = this.controls.getInputs();
    const modifiedInputs = { player1: hostInputs.player1, player2: this.guestInputs };
    const originalGetInputs = this.controls.getInputs;
    this.controls.getInputs = () => modifiedInputs;
    super.updateGame();
    this.controls.getInputs = originalGetInputs;
  }

  private sendContinuousInputToHost(): void {
    if (!this.dataChannel || this.dataChannel.readyState !== 'open') return;
    const inputs = this.controls.getInputs();
    const input = { up: inputs.player1.up, down: inputs.player1.down };
    this.dataChannel.send(JSON.stringify({ type: 'player_input', input }));
    if (input.up || input.down) DevConsole.print('📤 Guest sending input to host:', input);
  }

  private handleP2PMessage(data: any): void {
    switch (data.type) {
      case 'game_settings':
        this.applyHostGameSettings(data.settings);
        break;
      case 'game_update':
        if (!this.isHost) this.applyRemoteGameState(data.state);
        break;
      case 'player_input':
        if (this.isHost) this.applyRemoteInput(data.input);
        break;
      case 'player_disconnect':
      case 'voluntary_disconnect':
        if (!this.gameEndedByDisconnection) this.handleOpponentQuit(data.reason);
        break;
      case 'match_saved':
        this.isMatchDataSent = true;
        break;
    }
  }

  private applyRemoteGameState(state: any): void {
    this.renderer.updatePositions({ player1Paddle: state.paddles.player1Paddle, player2Paddle: state.paddles.player2Paddle, ball: state.ball });
    this.gameState.scores = state.scores;
    this.gameState.timer = state.timer;
    this.gameState.status = state.status;
    this.gameState.winner = state.winner;
    this.saveGameStateToSession();
    this.updateUI();
    this.updateTimerDisplay();
    if (state.status === 'finished') {
      sessionStorage.removeItem('remote_game_active');
      sessionStorage.removeItem('remote_game_data');
      this.handleRemoteGameEnd();
    }
  }

  private applyRemoteInput(input: any): void {
    this.guestInputs = { up: input.up || false, down: input.down || false };
  }

  private sendGameSettingsToGuest(): void {
    if (!this.dataChannel || this.dataChannel.readyState !== 'open') return;
    this.dataChannel.send(JSON.stringify({ type: 'game_settings', settings: { ballSpeed: this.settings.ballSpeed, winScore: this.settings.winScore, enableEffects: this.settings.enableEffects } }));
  }

  private applyHostGameSettings(hostSettings: any): void {
    this.settings.ballSpeed = hostSettings.ballSpeed;
    this.settings.winScore = hostSettings.winScore;
    this.settings.enableEffects = hostSettings.enableEffects;
    this.updateConnectionStatus("Connected");
    setTimeout(() => this.addSettingsToStatus(hostSettings), 500);
    setTimeout(() => this.startLocalGameAsGuest(), 3000);
  }

  private startLocalGameAsGuest(): void {
    this.settings.player1Name = this.opponentUsername;
    this.settings.player2Name = userAuthenticationService.getCurrentUser()?.username || 'Guest';
    this.matchStartTime = Date.now();
    this.isMatchDataSent = false;
  }

  private handleOpponentQuit(reason: string): void {
    if (this.gameState.status === 'finished' || this.gameEndedByDisconnection) return;
    this.gameEndedByDisconnection = true;
    this.awardVictoryByForfeit('opponent_quit', reason);
  }

  private handleOpponentDisconnection(reason: string): void {
    if (this.gameState.status === 'finished' || this.gameEndedByDisconnection) return;
    this.gameEndedByDisconnection = true;
    this.awardVictoryByForfeit('opponent_disconnected', reason);
  }

  private awardVictoryByForfeit(type: 'opponent_quit' | 'opponent_disconnected', reason: string): void {
    const currentUser = userAuthenticationService.getCurrentUser();
    let winner: 'player1' | 'player2', winnerName: string, loserName: string;
    if (this.isHost) {
      winner = 'player1'; winnerName = currentUser?.username || 'Host'; loserName = this.opponentUsername;
    } else {
      winner = 'player2'; winnerName = currentUser?.username || 'Guest'; loserName = this.opponentUsername;
    }
    this.gameState.status = 'finished';
    this.gameState.winner = winner;
    this.gameState.scores.player1 = winner === 'player1' ? 5 : 0;
    this.gameState.scores.player2 = winner === 'player2' ? 5 : 0;
    this.updateGameStatus("Game ended - opponent disconnected");
    this.processForfeitVictory(winner, winnerName, loserName, reason);
  }

  private async processForfeitVictory(winner: 'player1' | 'player2', winnerName: string, loserName: string, reason: string): Promise<void> {
    if (this.opponentUserId && !this.isMatchDataSent) {
      try {
        await this.saveRemoteMatchDataByWinner(winner);
        this.notifyMatchSaved();
      } catch (error) { DevConsole.reportError('❌ Failed to save forfeit match data:', error); }
    }
    setTimeout(() => this.showForfeitVictoryModal(winnerName, loserName, reason), 1000);
    setTimeout(() => this.cleanupConnections(), 3000);
  }

  private getSpeedDisplayName(speed: string): string {
    return { slow: 'Lent', medium: 'Moyen', fast: 'Rapide' }[speed] || speed;
  }

  private updateTimerDisplay(): void {
    const minutes = Math.floor(this.gameState.timer / 60);
    const seconds = Math.floor(this.gameState.timer % 60);
    const timeString = `${minutes.toString().padStart(2,'0')}:${seconds.toString().padStart(2,'0')}`;
    ['#game-timer .text-lg','#game-timer .text-2xl','#game-timer-display'].forEach(sel => {
      const el = document.querySelector(sel);
      if(el) el.textContent = timeString;
    });
  }

  protected updateGameStatus(status: string): void {
    if (this.gameWasInterrupted) return;
    super.updateGameStatus(status);
  }
}
