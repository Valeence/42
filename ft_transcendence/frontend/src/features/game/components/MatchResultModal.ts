import type { MatchCompletionSummary } from '@/types/index.js';

export interface GameEndModalStats {
  winnerName: string;
  loserName: string;
  winnerScore: number;
  loserScore: number;
  matchDuration: number;
  totalScore: number;
  gameMode: 'local' | 'remote';
  winScore: number;
}

export interface GameEndModalCallbacks {
  onPlayAgain?: () => void;
  onBackToMenu: () => void;
  onViewStats?: () => void;
}

export function convertToModalStats(stats: MatchCompletionSummary): GameEndModalStats {
  const winnerScore = stats.winnerScore ?? stats.finalScore?.winner ?? 0;
  const loserScore = stats.loserScore ?? stats.finalScore?.loser ?? 0;
  const duration = stats.matchDuration ?? parseInt(stats.duration) ?? 0;
  const totalScore = stats.totalScore ?? (winnerScore + loserScore);

  return {
    winnerName: stats.winnerName || stats.winner,
    loserName: stats.loserName || stats.loser,
    winnerScore,
    loserScore,
    matchDuration: duration,
    totalScore,
    gameMode: stats.gameMode === 'remote' ? 'remote' : 'local',
    winScore: stats.winScore ?? 5
  };
}

export class GameEndModal {
  private modal: HTMLElement | null = null;
  private stats: GameEndModalStats;
  private callbacks: GameEndModalCallbacks;
  private isVisible: boolean = false;
  private isRemoteGame: boolean = false;
  private modalContainer: HTMLElement | null = null;

  constructor(stats: GameEndModalStats, callbacks: GameEndModalCallbacks) {
    this.stats = stats;
    this.callbacks = callbacks;
    this.isRemoteGame = stats.gameMode === 'remote';
  }

  public show(): void {
    this.createModal();
    this.bindEvents();
    requestAnimationFrame(() => {
      if (this.modal) {
        this.modal.classList.replace('opacity-0', 'opacity-100');
        const content = this.modal.querySelector('.modal-content');
        content?.classList.replace('scale-95', 'scale-100');
      }
    });
  }

  public close(): void {
    if (!this.modal) return;
    this.modal.classList.replace('opacity-100', 'opacity-0');
    const content = this.modal.querySelector('.modal-content');
    content?.classList.replace('scale-100', 'scale-95');
    setTimeout(() => {
      this.modal?.remove();
      this.modal = null;
    }, 500);
  }

  public updateStats(newStats: GameEndModalStats): void {
    this.stats = newStats;
    if (!this.modal) return;

    const content = this.modal.querySelector('.modal-content');
    if (!content) return;

    while (content.firstChild) content.removeChild(content.firstChild);

    content.insertAdjacentHTML('beforeend', this.renderModalContent().match(/<div class="modal-content[^>]*>([\s\S]*)<\/div>/)?.[1] ?? '');
    this.bindEvents();
  }

  private createModal(): void {
    this.close();
    this.modal = document.createElement('div');
    this.modal.id = 'game-end-modal';
    this.modal.className = 'fixed inset-0 z-50 bg-black bg-opacity-90 backdrop-blur-sm flex items-center justify-center p-4 opacity-0 transition-opacity duration-500';
    this.modal.innerHTML = this.renderModalContent();
    document.body.appendChild(this.modal);
  }

  private renderModalContent(): string {
    const durationText = this.formatDuration(this.stats.matchDuration);
    return `
      <div class="modal-content bg-gray-900/95 backdrop-blur-sm rounded-xl p-8 max-w-md w-full mx-4 shadow-2xl border border-gray-700/50 transform scale-95 transition-transform duration-300">
        ${this.renderHeader()}
        ${this.renderScoreSection()}
        ${this.renderStatsSection(durationText)}
        ${this.renderActionButtons()}
      </div>
    `;
  }

  private renderHeader(): string {
    return `
      <div class="text-center mb-6">
        <div class="text-6xl mb-4">🏆</div>
        <h2 class="text-3xl font-bold text-yellow-400 mb-2">Game Over</h2>
        <p class="text-xl text-gray-300">
          <span class="text-green-400 font-bold">${this.stats.winnerName}</span> wins!
        </p>
      </div>
    `;
  }

  private renderScoreSection(): string {
    const winnerColor = this.stats.winnerScore > this.stats.loserScore ? 'text-green-400' : 'text-red-400';
    const loserColor = this.stats.loserScore > this.stats.winnerScore ? 'text-green-400' : 'text-red-400';
    return `
      <div class="bg-gray-800/60 rounded-lg p-6 mb-6 border border-gray-700/50">
        <h3 class="text-lg font-semibold text-center mb-4 text-gray-300">Final Score</h3>
        <div class="flex justify-between items-center">
          <div class="text-center flex-1">
            <div class="text-2xl font-bold ${winnerColor}">${this.stats.winnerName}</div>
            <div class="text-4xl font-mono font-bold ${winnerColor}">${this.stats.winnerScore}</div>
          </div>
          <div class="text-3xl text-gray-500 px-4">-</div>
          <div class="text-center flex-1">
            <div class="text-2xl font-bold ${loserColor}">${this.stats.loserName}</div>
            <div class="text-4xl font-mono font-bold ${loserColor}">${this.stats.loserScore}</div>
          </div>
        </div>
      </div>
    `;
  }

  private renderStatsSection(durationText: string): string {
    const modeText = this.isRemoteGame ? 'Online' : 'Local';
    return `
      <div class="grid grid-cols-2 gap-4 mb-6 text-sm">
        <div class="bg-gray-900 rounded-lg p-3 text-center">
          <div class="text-blue-400 font-semibold">Duration</div>
          <div class="text-xl font-mono">${durationText}</div>
        </div>
        <div class="bg-gray-900 rounded-lg p-3 text-center">
          <div class="text-purple-400 font-semibold">Total Points</div>
          <div class="text-xl font-mono">${this.stats.totalScore}</div>
        </div>
        <div class="bg-gray-900 rounded-lg p-3 text-center">
          <div class="text-orange-400 font-semibold">Mode</div>
          <div class="text-sm">${modeText}</div>
        </div>
        <div class="bg-gray-900 rounded-lg p-3 text-center">
          <div class="text-pink-400 font-semibold">Win Condition</div>
          <div class="text-xl">${this.stats.winScore}</div>
        </div>
      </div>
    `;
  }

  private renderActionButtons(): string {
    const playAgainBtn = this.callbacks.onPlayAgain ? `<button id="play-again-action-trigger" class="bg-blue-600 hover:bg-blue-700 text-white font-medium py-3 px-6 rounded-lg transition-colors">🔄 Play Again</button>` : '';
    const viewStatsBtn = !this.isRemoteGame ? `<button id="view-stats-action-trigger" class="bg-purple-600 hover:bg-purple-700 text-white font-medium py-3 px-6 rounded-lg transition-colors">📊 View Stats</button>` : '';
    return `
      <div class="flex flex-col gap-3">
        ${playAgainBtn}
        <button id="back-to-menu-action-trigger" class="bg-gray-600 hover:bg-gray-700 text-white font-medium py-3 px-6 rounded-lg transition-colors">🏠 Back to Menu</button>
        ${viewStatsBtn}
      </div>
    `;
  }

  private bindEvents(): void {
    if (!this.modal) return;

    const addListener = (selector: string, callback?: () => void) => {
      const target = this.modal!.querySelector(selector);
      target?.addEventListener('click', () => {
        callback?.();
        this.close();
      });
    };

    addListener('#play-again-action-trigger', this.callbacks.onPlayAgain);
    addListener('#back-to-menu-action-trigger', this.callbacks.onBackToMenu);
    addListener('#view-stats-action-trigger', this.callbacks.onViewStats);

    const handleKeydown = (e: KeyboardEvent) => e.key === 'Escape' && this.close();
    document.addEventListener('keydown', handleKeydown);
    this.modal.addEventListener('remove', () => document.removeEventListener('keydown', handleKeydown));
  }

  private formatDuration(seconds: number): string {
    const m = Math.floor(seconds / 60).toString().padStart(2, '0');
    const s = (seconds % 60).toString().padStart(2, '0');
    return `${m}:${s}`;
  }
}
