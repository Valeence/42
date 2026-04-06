import * as BABYLON from '@babylonjs/core';
import { GameRenderer } from './Pong3DRenderer.js';
import { GamePhysics } from './Pong3DPhysics.js';
import { GameControls } from './Pong3DControls.js';
import { MatchService } from '../../services/gameMatchService.js';
import { GameEndModal, convertToModalStats } from '../MatchResultModal.js';
import type { ArenaSettings, PongSessionState, MatchCompletionSummary, MatchLifecycleHooks } from '@/types/index.js';
import { DevConsole } from '@/utils/devConsole.js';

export class Pong3D {
  private canvas: HTMLCanvasElement;
  private engine: BABYLON.Engine;
  private scene: BABYLON.Scene;
  protected renderer: GameRenderer;
  protected physics: GamePhysics;
  protected controls: GameControls;
  protected gameState: PongSessionState = {
    status: 'waiting',
    scores: { player1: 0, player2: 0 },
    timer: 0
  };
  protected settings: ArenaSettings;
  protected isRemoteGame: boolean;
  protected matchStartTime: number = 0;
  protected isMatchDataSent: boolean = false;
  private gameEndModal: GameEndModal | null = null;
  private mode: 'local' | 'tournament' | 'remote' = 'local';
  public onGameEnd?: (winner: string, scores: any, duration: number) => void;

  constructor(canvasId: string, settings: ArenaSettings, isRemote = false, mode: 'local' | 'tournament' | 'remote' = 'local') {
    this.canvas = document.getElementById(canvasId) as HTMLCanvasElement;
    if (!this.canvas) throw new Error(`Canvas with id "${canvasId}" not found`);
    
    this.settings = settings;
    this.isRemoteGame = isRemote;
    this.mode = mode;

    DevConsole.print(`🎮 Initializing Pong3D in ${mode} mode on canvas:`, canvasId);

    this.initEngine();
    this.initComponents();
    this.bindEvents();
  }

  private initEngine(): void {
    this.engine = new BABYLON.Engine(this.canvas, true, { adaptToDeviceRatio: true, antialias: true });
    this.scene = new BABYLON.Scene(this.engine);
    this.scene.clearColor = new BABYLON.Color4(0.1, 0.1, 0.2, 1);

    window.addEventListener('resize', () => this.engine.resize());
  }

  private initComponents(): void {
    DevConsole.print('🔧 Initializing game components...');
    this.renderer = new GameRenderer(this.scene, this.canvas);
    this.physics = new GamePhysics(this.settings);
    this.controls = new GameControls();

    this.startRenderLoop();
  }

  private startRenderLoop(): void {
    this.engine.runRenderLoop(() => {
      if (this.gameState.status === 'playing') this.updateGame();
      this.scene.render();
    });
  }

  public startGame(): void {
    DevConsole.print('🚀 Starting game...');
    if (this.isRemoteGame) this.connectToServer();
    else this.startLocalGame();
  }

  public togglePause(): void {
    if (this.gameState.status === 'playing') {
      this.gameState.status = 'paused';
      this.updateGameStatus('Game Paused');
    } else if (this.gameState.status === 'paused') {
      this.gameState.status = 'playing';
      this.updateGameStatus('Game Resumed');
    }
  }

  public getGameStatus(): string {
    return this.gameState.status;
  }


  public handleResize(): void {
    this.engine.resize();
    this.renderer.adjustCameraForScreen();
  }


  public destroy(): void {
    DevConsole.print('🗑️ Destroying Pong3D...');
    this.clearAllEffectIndicators();

    this.gameEndModal?.close();
    this.gameEndModal = null;
    this.controls.destroy();
    this.renderer.destroy();
    this.engine?.dispose();
    window.removeEventListener('resize', () => {});
  }

  protected updateGame(): void {
    if (!this.renderer.isInitialized()) {
      DevConsole.reportError('🚨 Renderer not fully initialized yet');
      return;
    }

    const paddleInputs = this.getModifiedInputs();
    this.applyPhysicsEffects();
    const physicsUpdate = this.physics.update(paddleInputs);
    const deltaTime = this.engine.getDeltaTime() / 1000;

    this.renderer.updatePositions(physicsUpdate.positions);

    if (physicsUpdate.events.goal) this.handleGoal(physicsUpdate.events.goal.scorer);

    this.updateTimer();
    this.updateUI();
  }

  protected applyPhysicsEffects(): void {
  }

  protected startLocalGame(): void {
    this.updateGameStatus('Starting Local Game...');
    this.physics.reset();
    this.matchStartTime = Date.now();
    this.isMatchDataSent = false;
    this.startCountdown();
  }

  protected endGame(winner: 'player1' | 'player2'): void {
    this.gameState.status = 'finished';
    this.gameState.winner = winner;

    const winnerName = winner === 'player1' ? this.settings.player1Name : this.settings.player2Name;
    const loserName = winner === 'player1' ? this.settings.player2Name : this.settings.player1Name;

    DevConsole.print(`🏁 Game finished! Winner: ${winnerName}`);
    this.clearAllEffectIndicators();

    if (this.onGameEnd) {
      const duration = (Date.now() - this.matchStartTime) / 1000;
      DevConsole.print('🏆 Tournament match ended, calling callback');
      this.onGameEnd(winnerName, this.gameState.scores, duration);
    }

    if (this.mode === 'local') {
      DevConsole.print('🎮 Local game - showing end modal');
      this.showGameEndModal(winner, winnerName, loserName);
    } else {
      DevConsole.print(`🏆 ${this.mode} game - modal handled by parent component`);
    }

    if (this.mode === 'local' && !this.isMatchDataSent) this.sendMatchDataToBackend();
  }

  protected updateUI(): void {
    const getEl = (id1: string, id2?: string) => document.getElementById(id1) || (id2 ? document.getElementById(id2) : null);

    const p1Score = getEl('player1-score', 'tournament-player1-score');
    const p2Score = getEl('player2-score', 'tournament-player2-score');
    if (p1Score) p1Score.textContent = this.gameState.scores.player1.toString();
    if (p2Score) p2Score.textContent = this.gameState.scores.player2.toString();

    const p1Name = getEl('player1-name', 'tournament-player1-name');
    const p2Name = getEl('player2-name', 'tournament-player2-name');
    if (p1Name) p1Name.textContent = this.settings.player1Name;
    if (p2Name) p2Name.textContent = this.settings.player2Name;

    const scoresDesktop = getEl('game-scores');
    if (scoresDesktop) scoresDesktop.textContent = `${this.gameState.scores.player1} - ${this.gameState.scores.player2}`;

    this.updateActiveEffectsDisplay();
  }

  protected updateGameStatus(status: string): void {
    const statusEl = document.getElementById('game-status') || document.getElementById('tournament-game-status');
    if (statusEl) statusEl.textContent = status;

  }

  private bindEvents(): void {
    this.controls.bindKeyboardEvents();

    document.addEventListener('keydown', (e) => {
      if (e.code === 'Space') {
        e.preventDefault();
        this.togglePause();
      }
    });
  }

  private getModifiedInputs(): any {
    return this.controls.getInputs();
  }


  private handleGoal(scorer: 'player1' | 'player2'): void {
    this.gameState.scores[scorer]++;
    DevConsole.print(`🥅 Goal by ${scorer}! Score: ${this.gameState.scores.player1}-${this.gameState.scores.player2}`);

    if (this.gameState.scores[scorer] >= this.settings.winScore) this.endGame(scorer);
    else {
      this.physics.reset();
      setTimeout(() => this.physics.launchBall(), 2000);
    }
  }

  private startCountdown(): void {
    let count = 3;
    const countdown = setInterval(() => {
      if (count > 0) this.updateGameStatus(`Starting in ${count--}...`);
      else {
        clearInterval(countdown);
        this.gameState.status = 'playing';
        this.updateGameStatus('GO!');
        this.physics.launchBall();
      }
    }, 1000);
  }

  private updateTimer(): void {
    this.gameState.timer += this.engine.getDeltaTime() / 1000;
    const minutes = Math.floor(this.gameState.timer / 60);
    const seconds = Math.floor(this.gameState.timer % 60);
    const timeStr = `${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`;

    const timerEls = [
      document.querySelector('#game-timer .text-lg, #game-timer .text-2xl'),
      document.querySelector('#tournament-game-timer .text-lg, #tournament-game-timer .text-2xl'),
      document.getElementById('game-timer-display'),
      document.getElementById('tournament-game-timer-display'),
    ];
    timerEls.forEach(el => { if (el) el.textContent = timeStr; });
  }

  private updateActiveEffectsDisplay(): void {
    this.clearAllEffectIndicators();
  }

  private clearAllEffectIndicators(): void {
    document.querySelectorAll('.active-effect-indicator').forEach(el => el.remove());
  }

  protected showGameEndModal(winner: 'player1' | 'player2', winnerName: string, loserName: string): void {
    const gameOverlay = document.getElementById('game-overlay');
    if (gameOverlay) {
      gameOverlay.style.display = 'none';
    }
    
    const matchDuration = Math.floor(this.gameState.timer);
    const totalScore = this.gameState.scores.player1 + this.gameState.scores.player2;
    const winnerScore = this.gameState.scores[winner];
    const loserScore = winner === 'player1' ? this.gameState.scores.player2 : this.gameState.scores.player1;
    
    const stats: MatchCompletionSummary = {
      winner: winner,
      loser: winner === 'player1' ? 'player2' : 'player1',
      finalScore: { winner: winnerScore, loser: loserScore },
      duration: matchDuration.toString(),
      gameMode: this.isRemoteGame ? 'remote' : 'local',
      winnerName,
      loserName,
      winnerScore,
      loserScore,
      matchDuration,
      totalScore,
      winScore: this.settings.winScore
    };
    
    const callbacks: MatchLifecycleHooks = {
      onPlayAgain: () => this.restartGame(),
      onBackToMenu: () => this.backToMenu(),
      onViewStats: () => this.showMatchStats()
    };
    
    this.gameEndModal = new GameEndModal(convertToModalStats(stats), callbacks);
    this.gameEndModal.show();
  }

  protected async sendMatchDataToBackend(): Promise<void> {
    try {
      this.isMatchDataSent = true;
      const duration = Math.floor((Date.now() - this.matchStartTime) / 1000);
      const matchData = {
        player1: this.settings.player1Name,
        player2: this.settings.player2Name,
        score1: this.gameState.scores.player1,
        score2: this.gameState.scores.player2,
        duration
      };
      
      DevConsole.print('📊 Match data to send:', matchData);
      await new MatchService().sendLocalMatchData(
        matchData.player1,
        matchData.player2,
        matchData.score1,
        matchData.score2,
        matchData.duration
      );
      DevConsole.print('✅ Match data sent successfully');
    } catch (error) {
      DevConsole.reportError('❌ Failed to send match data:', error);
      this.isMatchDataSent = false;
    }
  }

  protected restartGame(): void {
    DevConsole.print('🔄 Restarting game...');
    const gameOverlay = document.getElementById('game-overlay');
    if (gameOverlay) {
      gameOverlay.style.display = 'block';
    }
    
    this.gameState = {
      status: 'waiting',
      scores: { player1: 0, player2: 0 },
      timer: 0
    };
    this.isMatchDataSent = false;
    this.startGame();
  }

  protected backToMenu(): void {
    DevConsole.print('🏠 Going back to menu...');
    window.dispatchEvent(new CustomEvent('navigate', { detail: '/' }));
  }

  protected showMatchStats(): void {
    DevConsole.print('📊 Showing match statistics...');
    window.dispatchEvent(new CustomEvent('navigate', { detail: '/profile' }));
  }

  private connectToServer(): void {
    DevConsole.print('🌐 Connecting to server...');
    this.updateGameStatus('Connecting to server...');
  }

  protected setupPageLeaveDetection(): void {
  }

  protected showGameInterruptionModal(opponentName: string): void {
  }

  protected saveGameStateToSession(): void {
  }

  protected handleRemoteGameEnd(): void {
  }

  protected updateConnectionStatus(status: string): void {
  }

  protected addSettingsToStatus(settings: any): void {
  }

  protected saveRemoteMatchDataByWinner(winner: 'player1' | 'player2'): void {
  }

  protected notifyMatchSaved(): void {
  }

  protected showForfeitVictoryModal(winnerName: string, loserName: string, reason: string): void {
  }

  protected cleanupConnections(): void {
  }
}
