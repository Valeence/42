import { GameManager } from '@/features/game/components/PongGameManager';
import type { GameManagerOptions, ArenaSettings } from '@/types/index.js';
import { DevConsole } from '@/utils/devConsole.js';
export class TournamentMatch
{
  private gameManager: GameManager | null = null;
  private isLandscape: boolean = false;
  private gameSettings?: ArenaSettings;
  constructor(private match: any, private tournamentId: number, gameSettings?: ArenaSettings)
  {
    this.match = match;
    this.tournamentId = tournamentId;
    this.gameSettings = gameSettings;
    this.registerOrientationListeners();
  }
  private registerOrientationListeners(): void
  {
    this.handleOrientationChange = this.handleOrientationChange.bind(this);
    window.addEventListener('orientationchange', this.handleOrientationChange);
    window.addEventListener('resize', this.handleOrientationChange);
  }
  render(): string
  {
    return `
      <div class="bg-gray-800 rounded-lg p-6">
        <h3 class="text-xl font-semibold mb-4 text-center">
          ${this.match.round} - Match ${this.match.matchNumber}
        </h3>
        <!-- Vue d'avant match -->
        <div id="tournament-match-setup">
          <div class="grid grid-cols-2 gap-6 mb-6">
            <div class="bg-blue-900/30 rounded-lg p-4 text-center border border-blue-500/30">
              <h4 class="text-lg font-semibold mb-2 text-blue-400">${this.match.player1}</h4>
              <span class="text-gray-400">Player 1</span>
            </div>
            <div class="bg-red-900/30 rounded-lg p-4 text-center border border-red-500/30">
              <h4 class="text-lg font-semibold mb-2 text-red-400">${this.match.player2}</h4>
              <span class="text-gray-400">Player 2</span>
            </div>
          </div>
          <div class="text-center">
            <button id="start-tournament-match"
                    class="bg-primary-600 hover:bg-primary-700 px-8 py-3 rounded-lg font-medium transition-colors">
              Start Match
            </button>
          </div>
        </div>
        <!-- Interface de jeu complète (cachée par défaut) -->
        <div id="tournament-game-interface" class="hidden">
          ${this.renderGameInterface()}
        </div>
      </div>
    `;
  }
  bindEvents(): void
  {
    setTimeout(() =>
    {
      this.bindStartButton();
      this.bindGameControls();
      this.bindMobileControls();
    }, 100);
  }
  private bindStartButton(): void
  {
    const startBtn = document.getElementById('start-tournament-match');
    if (!startBtn) return;
    startBtn.addEventListener('click', () =>
    {
      DevConsole.print('🎮 Start tournament match clicked!');
      this.startMatch();
    });
  }
  destroy(): void
  {
    window.removeEventListener('orientationchange', this.handleOrientationChange);
    window.removeEventListener('resize', this.handleOrientationChange);
    this.teardownGameManager();
  }
  private renderGameInterface(): string
  {
    return `
      <!-- Header du jeu -->
      <div class="bg-gray-800/50 backdrop-blur-sm rounded-t-lg p-4 flex justify-between items-center border-b border-gray-700/50 mb-4">
        <h2 class="text-xl font-bold">Match de Tournoi</h2>
        <div class="flex gap-3">
          <button id="pause-tournament-game" class="bg-yellow-600 hover:bg-yellow-700 px-4 py-2 rounded-lg text-sm transition-colors">
            ⏸️ Pause
          </button>
          <button id="quit-tournament-game" class="bg-red-600 hover:bg-red-700 px-4 py-2 rounded-lg text-sm transition-colors">
            Abandonner
          </button>
        </div>
      </div>
      <!-- Zone de jeu avec overlay complet -->
      <div class="relative bg-gray-800 rounded-lg overflow-hidden">
        <!-- Canvas Container -->
        <div class="relative w-full" style="padding-bottom: 56.25%;">
          <canvas id="tournament-game-canvas"
                  class="absolute top-0 left-0 w-full h-full"
                  style="background: linear-gradient(45deg, #1a1a2e, #16213e);">
          </canvas>
          <!-- Game Overlay avec scores -->
          ${this.renderTournamentGameOverlay()}
        </div>
        <!-- Game Controls -->
        ${this.renderTournamentGameControls()}
      </div>
    `;
  }
  private renderTournamentGameOverlay(): string
  {
    return `
      <div id="tournament-game-overlay" class="absolute inset-0 pointer-events-none">
        <!-- Overlay responsive pour les scores -->
        <div class="absolute top-2 left-2 right-2 md:top-4 md:left-4 md:right-4 flex justify-between items-start">
          <!-- Score Joueur 1 -->
          <div class="bg-black/60 backdrop-blur-sm rounded-lg md:rounded-xl p-2 md:p-4 shadow-lg border border-blue-500/30 min-w-0 flex-shrink-0">
            <div id="tournament-player1-info" class="text-white">
              <div class="font-bold text-blue-400 text-xs md:text-sm truncate" id="tournament-player1-name">${this.match.player1}</div>
              <div class="text-xl md:text-3xl font-mono font-bold" id="tournament-player1-score">0</div>
            </div>
          </div>
          <!-- Timer central -->
          <div class="bg-black/60 backdrop-blur-sm rounded-lg md:rounded-xl p-2 md:p-4 shadow-lg border border-gray-500/30 mx-2 min-w-0 flex-shrink-0">
            <div id="tournament-game-timer" class="text-white text-center">
              <div class="text-xs md:text-sm opacity-75 uppercase tracking-wide">Temps</div>
              <div class="text-lg md:text-2xl font-mono font-bold">00:00</div>
            </div>
            <div class="text-xs text-center mt-1 text-gray-400 hidden md:block">
              ${this.match.round}
            </div>
          </div>
          <!-- Score Joueur 2 -->
          <div class="bg-black/60 backdrop-blur-sm rounded-lg md:rounded-xl p-2 md:p-4 shadow-lg border border-red-500/30 min-w-0 flex-shrink-0">
            <div id="tournament-player2-info" class="text-white text-right">
              <div class="font-bold text-red-400 text-xs md:text-sm truncate" id="tournament-player2-name">${this.match.player2}</div>
              <div class="text-xl md:text-3xl font-mono font-bold" id="tournament-player2-score">0</div>
            </div>
          </div>
        </div>
        <!-- Status mobile en bas (visible uniquement sur mobile) -->
        <div class="absolute bottom-2 left-2 right-2 md:hidden">
          <div class="bg-black/60 backdrop-blur-sm rounded-lg p-2 text-center border border-gray-500/30">
            <div id="tournament-game-status-mobile" class="text-green-400 text-xs">
              Préparation...
            </div>
            <div class="text-xs text-gray-400 mt-1">
              ${this.match.round}
            </div>
          </div>
        </div>
      </div>
    `;
  }
  private renderTournamentGameControls(): string
  {
    return `
      <div class="p-4 grid grid-cols-1 lg:grid-cols-2 gap-4">
        <!-- Desktop Controls -->
        <div class="bg-gray-700/50 rounded-lg p-4 hidden md:block">
          <h4 class="text-lg mb-3">Contrôles Clavier</h4>
          <div class="grid grid-cols-2 gap-4 text-sm">
            <div><strong>${this.match.player1}:</strong> W/S ou ↑/↓</div>
            <div><strong>${this.match.player2}:</strong> I/K</div>
          </div>
          <div class="mt-2 text-xs text-gray-400">
            Appuyez sur ESPACE pour pause
          </div>
        </div>
        <!-- Game Status -->
        <div class="bg-gray-700/50 rounded-lg p-4">
          <h4 class="text-lg mb-3">Status du Match</h4>
          <div id="tournament-game-status" class="text-green-400 text-sm">
            Préparation...
          </div>
          <div id="tournament-game-scores" class="text-lg mt-2">0 - 0</div>
          <div id="tournament-game-timer-display" class="text-sm text-gray-300 mt-1">00:00</div>
        </div>
      </div>
      <!-- Mobile Touch Controls -->
      <div id="tournament-mobile-controls" class="p-4 md:hidden">
        ${this.renderTournamentMobileControls()}
      </div>
    `;
  }
  private renderTournamentMobileControls(): string
  {
    return `
      <div class="bg-gray-700/50 rounded-lg p-4 orientation-transition">
        <h4 class="text-lg mb-3 text-center hidden-landscape">Contrôles Tactiles</h4>
        <div class="flex justify-between items-center">
          <div class="text-center player-controls">
            <div class="text-xs mb-2 text-blue-300 font-semibold hidden-landscape">${this.match.player1}</div>
            <div class="flex gap-3 landscape:flex-row portrait:flex-col">
              <button id="tournament-p1-up" class="bg-blue-600 hover:bg-blue-700 text-white p-4 rounded-xl touch-manipulation orientation-transition"
                      style="min-width: 70px; min-height: 70px; font-size: 1.8rem;">↑</button>
              <button id="tournament-p1-down" class="bg-blue-600 hover:bg-blue-700 text-white p-4 rounded-xl touch-manipulation orientation-transition"
                      style="min-width: 70px; min-height: 70px; font-size: 1.8rem;">↓</button>
            </div>
          </div>
          <div class="text-center px-4 flex-1 hidden-landscape">
            <div class="text-xs text-gray-400 mb-2">Maintenez pour bouger</div>
          </div>
          <div class="text-center player-controls">
            <div class="text-xs mb-2 text-red-300 font-semibold hidden-landscape">${this.match.player2}</div>
            <div class="flex gap-3 landscape:flex-row portrait:flex-col">
              <button id="tournament-p2-up" class="bg-red-600 hover:bg-red-700 text-white p-4 rounded-xl touch-manipulation orientation-transition"
                      style="min-width: 70px; min-height: 70px; font-size: 1.8rem;">↑</button>
              <button id="tournament-p2-down" class="bg-red-600 hover:bg-red-700 text-white p-4 rounded-xl touch-manipulation orientation-transition"
                      style="min-width: 70px; min-height: 70px; font-size: 1.8rem;">↓</button>
            </div>
          </div>
        </div>
      </div>
    `;
  }
  private bindGameControls(): void
  {
    const pauseBtn = document.getElementById('pause-tournament-game');
    const quitBtn = document.getElementById('quit-tournament-game');
    pauseBtn?.addEventListener('click', () =>
    {
      if (this.gameManager)
      {
        this.gameManager.pauseGame();
        this.updatePauseButton();
      }
    });
    quitBtn?.addEventListener('click', () =>
    {
      if (confirm('Êtes-vous sûr de vouloir abandonner ce match de tournoi ?'))
      {
        this.quitMatch();
      }
    });
  }
  private bindMobileControls(): void
  {
    const controls = ['tournament-p1-up', 'tournament-p1-down', 'tournament-p2-up', 'tournament-p2-down'];
    controls.forEach(controlId => this.attachMobileHandler(controlId));
  }
  private attachMobileHandler(controlId: string): void
  {
    const controlElement = document.getElementById(controlId);
    if (!controlElement) return;
    const handleStart = (event: Event) =>
    {
      event.preventDefault();
      this.handleMobileControlStart(controlId);
    };
    const handleEnd = (event: Event) =>
    {
      event.preventDefault();
      this.handleMobileControlEnd(controlId);
    };
    controlElement.addEventListener('touchstart', handleStart);
    controlElement.addEventListener('touchend', handleEnd);
    controlElement.addEventListener('mousedown', handleStart);
    controlElement.addEventListener('mouseup', handleEnd);
  }
  private handleMobileControlStart(controlId: string): void
  {
    const mobileInput = this.getMobileInputHandler();
    if (!mobileInput) return;
    const isUp = controlId.includes('up');
    const player = controlId.includes('p1') ? 'player1' : 'player2';
    mobileInput(player, isUp ? 'up' : 'down', true);
  }
  private handleMobileControlEnd(controlId: string): void
  {
    const mobileInput = this.getMobileInputHandler();
    if (!mobileInput) return;
    const isUp = controlId.includes('up');
    const player = controlId.includes('p1') ? 'player1' : 'player2';
    mobileInput(player, isUp ? 'up' : 'down', false);
  }
  private getMobileInputHandler(): ((player: string, direction: 'up' | 'down', active: boolean) => void) | null
  {
    if (!this.gameManager) return null;
    const managerWithMobile = this.gameManager as unknown as {
      handleMobileInput?: (player: string, direction: 'up' | 'down', active: boolean) => void;
    };
    return managerWithMobile.handleMobileInput ?? null;
  }
  private toggleMatchInterface(showGameInterface: boolean): void
  {
    const setupDiv = document.getElementById('tournament-match-setup');
    const gameInterface = document.getElementById('tournament-game-interface');
    if (!setupDiv || !gameInterface) return;
    if (showGameInterface)
    {
      setupDiv.classList.add('hidden');
      gameInterface.classList.remove('hidden');
    }
    else
    {
      gameInterface.classList.add('hidden');
      setupDiv.classList.remove('hidden');
    }
  }
  private updatePauseButton(): void
  {
    const pauseBtn = document.getElementById('pause-tournament-game');
    if (!pauseBtn || !this.gameManager) return;
    const status = this.gameManager.getGameStatus();
    if (status === 'playing')
    {
      pauseBtn.innerHTML = '⏸️ Pause';
      pauseBtn.className = 'bg-yellow-600 hover:bg-yellow-700 px-4 py-2 rounded-lg text-sm transition-colors';
    } else if (status === 'paused')
    {
      pauseBtn.innerHTML = '▶️ Reprendre';
      pauseBtn.className = 'bg-green-600 hover:bg-green-700 px-4 py-2 rounded-lg text-sm transition-colors';
    }
  }
  private startMatch(): void
  {
    DevConsole.print('🚀 Starting tournament match...');
    this.toggleMatchInterface(true);
    const gameConfig: GameManagerOptions = {
      mode: 'tournament',
      canvasId: 'tournament-game-canvas',
      settings: this.composeGameSettings(),
      onGameStart: () =>
      {
        DevConsole.print('✅ Tournament game started');
        this.updateTournamentGameInterface();
      },
      onGameEnd: (winner: string, scores: any, duration: number) =>
      {
        DevConsole.print('🏁 Tournament match ended (callback):', { winner, scores, duration });
        this.handleMatchEnd(winner, scores, duration);
      }
    };
    try
    {
      this.gameManager = new GameManager(gameConfig);
      this.gameManager.startGame().then(() =>
      {
        DevConsole.print('✅ Tournament game started successfully');
      }).catch(error =>
      {
        DevConsole.reportError('❌ Failed to start tournament game:', error);
      });
    } catch (error)
    {
      DevConsole.reportError('❌ Failed to start tournament match:', error);
    }
  }
  private composeGameSettings(): ArenaSettings
  {
    const allowedSpeeds: Array<ArenaSettings['ballSpeed']> = ['slow', 'medium', 'fast'];
    const requestedSpeed = this.gameSettings?.ballSpeed as ArenaSettings['ballSpeed'] | undefined;
    const ballSpeed = allowedSpeeds.includes(requestedSpeed ?? 'medium')
      ? (requestedSpeed ?? 'medium')
      : 'medium';
    return {
      player1Name: this.match.player1,
      player2Name: this.match.player2,
      winScore: this.gameSettings?.winScore ?? 5,
      ballSpeed,
      enableEffects: false
    };
  }
  private updateTournamentGameInterface(): void
  {
    const p1Name = document.getElementById('tournament-player1-name');
    const p2Name = document.getElementById('tournament-player2-name');
    if (p1Name) p1Name.textContent = this.match.player1;
    if (p2Name) p2Name.textContent = this.match.player2;
    const statusEl = document.getElementById('tournament-game-status');
    if (statusEl)
    {
      statusEl.textContent = 'Match en cours';
      statusEl.className = 'text-green-400 text-sm';
    }
  }
  private quitMatch(): void
  {
    this.teardownGameManager();
    this.toggleMatchInterface(false);
  }
  private handleMatchEnd(winner: string, scores: any, duration: number): void
  {
    DevConsole.print('🏆 Tournament match ended, processing results...');
    this.showMatchEndNotification(winner, scores);
    const matchData = {
      tournamentId: this.tournamentId,
      matchNumber: this.match.matchNumber,
      player1: this.match.player1,
      player2: this.match.player2,
      score1: scores.player1,
      score2: scores.player2,
      duration: Math.floor(duration),
      winner
    };
    this.teardownGameManager();
    window.dispatchEvent(new CustomEvent('matchFinished', {
      detail: matchData
    }));
  }
  private handleOrientationChange(): void
  {
    setTimeout(() =>
    {
      const wasLandscape = this.isLandscape;
      this.isLandscape = window.innerWidth > window.innerHeight && window.innerWidth <= 768;
      if (wasLandscape !== this.isLandscape && this.gameManager)
      {
        this.updateTournamentInterfaceForOrientation();
      }
    }, 100);
  }
  private updateTournamentInterfaceForOrientation(): void
  {
    const gameInterface = document.getElementById('tournament-game-interface');
    const mobileControls = document.getElementById('tournament-mobile-controls');
    const gameOverlay = document.getElementById('tournament-game-overlay');
    if (this.isLandscape)
    {
      gameInterface?.classList.add('landscape-game-interface');
      mobileControls?.classList.add('landscape-mobile-controls');
      gameOverlay?.classList.add('landscape-game-overlay');
    } else
    {
      gameInterface?.classList.remove('landscape-game-interface');
      mobileControls?.classList.remove('landscape-mobile-controls');
      gameOverlay?.classList.remove('landscape-game-overlay');
    }
    if (this.gameManager)
    {
      this.gameManager.handleResize();
    }
  }
  private showMatchEndNotification(winner: string, scores: any): void
  {
    const gameInterface = document.getElementById('tournament-game-interface');
    if (!gameInterface) return;
    const overlay = document.createElement('div');
    overlay.className = 'absolute inset-0 bg-black/80 flex items-center justify-center z-50 rounded-lg';
    overlay.innerHTML = `
      <div class="text-center p-8">
        <h3 class="text-2xl font-bold text-green-400 mb-4">🏆 Match Terminé !</h3>
        <div class="text-xl mb-4">
          <span class="font-semibold text-white">${winner}</span> remporte le match !
        </div>
        <div class="text-lg text-gray-300 mb-6">
          Score final : ${scores.player1} - ${scores.player2}
        </div>
        <div class="text-blue-400 font-medium">
          Passage au match suivant...
        </div>
      </div>
    `;
    gameInterface.style.position = 'relative';
    gameInterface.appendChild(overlay);
    setTimeout(() =>
    {
      overlay.remove();
    }, 3000);
  }
  private teardownGameManager(): void
  {
    if (!this.gameManager) return;
    this.gameManager.destroy();
    this.gameManager = null;
  }
}
