import type { GameModeHandlers } from '@/types/index.js';

export class GameModeButtons {
  constructor(
    private userAuthenticated: boolean, 
    private gameModeCallbacks: GameModeHandlers
  ) {}

  private createCard(icon: string, title: string, description: string, buttonId: string, buttonLabel: string, extraInfo = ''): string {
    return `
      <div class="card hover:scale-105 transition-all duration-300">
        <div class="text-center p-6">
          <div class="text-4xl mb-4">${icon}</div>
          <h3 class="text-xl font-semibold text-white mb-3">${title}</h3>
          <p class="text-white text-opacity-80 text-sm md:text-base mb-3 min-h-[3rem]">${description}</p>
          ${extraInfo}
          <button id="${buttonId}" class="action-trigger ${buttonId === 'remote-game-action-trigger' && !this.userAuthenticated ? 'action-secondary' : 'action-primary'} w-full">
            ${buttonLabel}
          </button>
        </div>
      </div>
    `;
  }

  render(): string {
    const cards = [
      this.renderLocalGameCard(),
      this.renderTournamentCard(),
      this.renderRemoteGameCard()
    ];
    return `
      <div class="mb-16">
        <h2 class="text-2xl md:text-3xl font-bold text-center mb-8">Choose Your Game Mode</h2>
        <div class="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6 max-w-5xl mx-auto">
          ${cards.join('')}
        </div>
      </div>
    `;
  }

  bindEvents(): void {
    const handlers: Record<string, () => void> = {
      'local-game-action-trigger': () => this.gameModeCallbacks.onLocalGame(),
      'remote-game-action-trigger': () => {
        if (!this.userAuthenticated) this.gameModeCallbacks.onLogin?.();
        else this.gameModeCallbacks.onRemoteGame();
      },
      'tournament-action-trigger': () => this.gameModeCallbacks.onTournament()
    };

    Object.entries(handlers).forEach(([id, handler]) => {
      document.getElementById(id)?.addEventListener('click', handler);
    });
  }

  private renderLocalGameCard(): string {
    return this.createCard(
      '🎮',
      'Local Game',
      'Play with a friend on the same computer. Perfect for quick games!',
      'local-game-action-trigger',
      'Play Locally'
    );
  }

  private renderRemoteGameCard(): string {
    const extraInfo = !this.userAuthenticated
      ? `<p class="text-yellow-400 text-xs md:text-sm mb-3 flex items-center justify-center">
           <i class="fas fa-lock mr-1"></i>Login required to play online
         </p>`
      : '';

    return this.createCard(
      '🌐',
      'Online Game',
      'Challenge players online.',
      'remote-game-action-trigger',
      this.userAuthenticated ? 'Play Online' : 'Login',
      extraInfo
    );
  }

  private renderTournamentCard(): string {
    return this.createCard(
      '🏆',
      'Tournament',
      'Create an 8-player tournament and see who is the best!',
      'tournament-action-trigger',
      'Create Tournament'
    );
  }
}
