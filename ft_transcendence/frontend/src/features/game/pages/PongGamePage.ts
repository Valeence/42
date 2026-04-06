import { userAuthenticationService } from '@/features/auth/services/userAuthenticationService.js';
import { GameManager } from '../components/PongGameManager';
import { RemotePong } from '../components/OnlinePongGame.js';
import type { ArenaSettings, GameManagerOptions } from '@/types/index.js';
import { DevConsole } from '@/utils/devConsole.js'; 
import { GameModeSelector } from '../components/PlayModeSelector.js';
import { GameSettingsUI as GameSettingsComponent } from '../components/PongGameSettings.js';
import { GameInterface } from '../components/PongGameInterface.js';

export class GamePage 
{
  private gameMode: 'local' | 'remote' | 'tournament' | null = null;
  private gameManager: GameManager | null = null;
  private remotePong: RemotePong | null = null;
  private beforeNavigateHandler: ((event: CustomEvent) => void) | null = null;
  private modeSelector: GameModeSelector | null = null;
  private gameSettingsComponent: GameSettingsComponent | null = null;
  private gameInterface: GameInterface | null = null;

  constructor() 
  {
    this.parseGameMode();
  }

  async mount(selector: string): Promise<void> 
  {
    const element = document.querySelector(selector);
    if (!element) return;
    this.render(element);
    this.bindEvents();
    this.setupNavigationHandler();
  }

  destroy(): void 
  {
    this.cleanupGameInstances();
    this.cleanupEventListeners();
    this.cleanupNavigationHandler();
  }

  private cleanupNavigationHandler(): void 
  {
    if (this.beforeNavigateHandler) {
      window.removeEventListener('beforeNavigate', this.beforeNavigateHandler as EventListener);
      this.beforeNavigateHandler = null;
    }
  }

  private cleanupEventListeners(): void 
  {
    window.removeEventListener('resize', () => this.handleResize());
  }

  private cleanupGameInstances(): void 
  {
    if (this.gameManager) {
      this.gameManager.destroy();
      this.gameManager = null;
    }
    if (this.remotePong) {
      this.remotePong.destroy();
      this.remotePong = null;
    }
  }

  private render(element: Element): void 
  {
    element.innerHTML = `
      <div class="min-h-screen text-white">
        <div class="container mx-auto px-4 py-4 md:py-8">
          ${this.renderHeader()}
          ${this.renderModeSelection()}
          ${this.renderGameSettings()}
          ${this.renderGameContainer()}
        </div>
      </div>
    `;
  }

  private renderHeader(): string 
  {
    return `
      <div class="text-center mb-6 md:mb-8">
        <h1 class="text-2xl md:text-4xl font-bold mb-2">
          Pong Arena - ${this.getGameModeTitle()}
        </h1>
        <p class="text-gray-400 text-sm md:text-base">
          ${this.getGameModeDescription()}
        </p>
      </div>
    `;
  }

  private renderModeSelection(): string 
  {
    this.modeSelector = new GameModeSelector({
      onLocalMode: () => this.selectMode('local'),
      onRemoteMode: () => this.selectMode('remote'),
      onTournamentMode: () => this.selectMode('tournament')
    });
    return `
      <div id="mode-selection" class="${this.gameMode ? 'hidden' : ''}">
        ${this.modeSelector.render()}
      </div>
    `;
  }

  private renderGameSettings(): string 
  {
    if (!this.gameMode) return '';
    this.gameSettingsComponent = new GameSettingsComponent(this.gameMode, {
      onStartLocal: () => this.startLocalGame(),
      onStartRemote: () => this.startRemoteGame(),
      onCreateTournament: () => this.createTournament(),
      onBackToModes: () => this.showModeSelection()
    });
    return `
      <div id="game-settings" class="${!this.gameMode ? 'hidden' : ''}">
        ${this.gameSettingsComponent.render()}
      </div>
    `;
  }

  private renderGameContainer(): string 
  {
    if (!this.gameMode) return '';
    this.gameInterface = new GameInterface(this.gameMode, {
      onPause: () => { this.gameManager?.pauseGame(); this.updatePauseButton(); },
      onQuit: () => this.quitGame()
    });
    return `<div id="game-container" class="hidden">${this.gameInterface.render()}</div>`;
  }

  private bindEvents(): void 
  {
    this.modeSelector?.bindEvents();
    this.gameSettingsComponent?.bindEvents();
    this.gameInterface?.bindEvents();
    window.addEventListener('resize', () => this.handleResize());
    window.addEventListener('startRemoteGame', () => this.startRemoteGame(), { once: true });
  }

  private setupNavigationHandler(): void 
  {
    this.beforeNavigateHandler = (event: CustomEvent) => {
      if (event.detail !== '/game' && this.remotePong && this.isRemoteGameInProgress()) {
        this.destroy();
      }
    };
    window.addEventListener('beforeNavigate', this.beforeNavigateHandler as EventListener);
  }

  private async selectMode(mode: 'local' | 'remote' | 'tournament'): Promise<void> 
  {
    this.gameMode = mode;
    this.updateUrlWithMode(mode);
    const element = document.querySelector('#page-content');
    if (element) { this.render(element); this.bindEvents(); }
    await this.handleAutoStartRemoteGame(mode);
  }

  private showModeSelection(): void 
  {
    this.gameMode = null;
    this.updateUrlWithMode(null);
    const element = document.querySelector('#page-content');
    if (element) { this.render(element); this.bindEvents(); }
  }

  private updateUrlWithMode(mode: string | null): void 
  {
    const url = new URL(window.location.href);
    if (mode) url.searchParams.set('mode', mode);
    else url.searchParams.delete('mode');
    window.history.replaceState({}, '', url.toString());
  }

  private async startLocalGame(): Promise<void> 
  {
    const settings = this.gameSettingsComponent?.getGameSettings();
    if (!settings) return;

    const config: GameManagerOptions = {
      mode: 'local',
      canvasId: 'game-canvas',
      settings,
      onGameStart: () => this.updateGameInterface(settings),
      onGameEnd: async (winner, scores, duration) => await this.handleGameEnd(winner, scores, duration, settings)
    };
    this.gameManager = new GameManager(config);
    this.showGameInterface();
    await this.gameManager.startGame();
  }

  private async startRemoteGame(): Promise<void> 
  {
    const settings = this.gameSettingsComponent?.getGameSettings();
    if (!settings) return;
    this.showGameInterface();
    this.remotePong = new RemotePong('game-canvas', settings);
    await this.remotePong.startRemoteGame();
  }

  private showGameInterface(): void 
  {
    this.toggleInterfaceVisibility('game-settings', 'game-container');
  }

  private updateGameInterface(settings: ArenaSettings): void 
  {
    if (!this.gameInterface) return;
    this.gameInterface.updatePlayerNames(settings.player1Name, settings.player2Name);
    this.gameInterface.updateGameStatus('Playing', '0 - 0', '00:00');
  }

  private updatePauseButton(): void 
  {
    if (!this.gameManager || !this.gameInterface) return;
    this.gameInterface.updatePauseButton(this.gameManager.getGameStatus() === 'paused');
  }

  private toggleInterfaceVisibility(hideId: string, showId: string): void 
  {
    const hideEl = document.getElementById(hideId);
    const showEl = document.getElementById(showId);
    if (hideEl && showEl) { hideEl.classList.add('hidden'); showEl.classList.remove('hidden'); }
  }

  private async handleGameEnd(winner: string, scores: any, duration: number, settings: ArenaSettings): Promise<void> 
  {
    // Intentionally empty, Pong3D already saved data
  }

  private quitGame(): void 
  {
    this.cleanupGameInstances();
    this.toggleInterfaceVisibility('game-container', 'game-settings');
  }

  private showError(message: string): void 
  {
    if (!this.gameInterface) return;
    this.gameInterface.updateGameStatus(message, '0 - 0', '00:00');
  }

  private createTournament(): void 
  {
    const settings = this.gameSettingsComponent?.getGameSettings();
    if (!settings) return;
    const isAuth = userAuthenticationService.isAuthenticated();
    const params = new URLSearchParams({
      participants: '8',
      mode: isAuth ? 'authenticated' : 'guest',
      ballSpeed: settings.ballSpeed,
      winScore: settings.winScore.toString(),
    });
    window.dispatchEvent(new CustomEvent('navigate', { detail: `/tournament/create?${params.toString()}` }));
  }

  private parseGameMode(): void 
  {
    const params = new URLSearchParams(window.location.search);
    this.gameMode = params.get('mode') as 'local' | 'remote' | 'tournament' || null;
  }

  private handleResize(): void 
  {
    this.gameManager?.handleResize();
  }

  private isRemoteGameInProgress(): boolean 
  {
    return this.remotePong !== null;
  }

   private async handleAutoStartRemoteGame(mode: string): Promise<void> 
   {
     const wasInGame = sessionStorage.getItem('remote_game_active');
     if (mode !== 'remote') return;
     if (userAuthenticationService.isAuthenticated() && wasInGame !== 'true') return;
   }

   private getGameModeTitle(): string 
   {
     switch (this.gameMode) 
     {
       case 'local': return 'Local';
       case 'remote': return 'Online';
       case 'tournament': return 'Tournament';
       default: return 'Mode Selection';
     }
   }

   private getGameModeDescription(): string 
   {
     switch (this.gameMode) 
     {
       case 'local': return 'Play with a friend on the same computer. Perfect for quick games!';
       case 'remote': return 'Challenge players online.';
       case 'tournament': return 'Create an 8-player tournament and see who is the best!';
       default: return 'Choose your preferred game mode';
     }
   }
 }
