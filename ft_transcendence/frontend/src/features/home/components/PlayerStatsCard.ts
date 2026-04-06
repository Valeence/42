import type { AccountProfile } from '@/types/index.js';

export class UserStatsCard {
  constructor(private profileUser: AccountProfile) {}

  private formatValue(value: number | string, suffix = ''): string {
    return `${value}${suffix}`;
  }

  private getStatBlocks(): string[] {
    const stats = this.profileUser?.stats;
    if (!stats) return [];

    // Shuffle the order slightly
    return [
      this.createBlock('Wins', this.formatValue(stats.wins), 'text-green-400'),
      this.createBlock('Games', this.formatValue(stats.totalGames), 'text-purple-400'),
      this.createBlock('Win Rate', this.formatValue(stats.winRate, '%'), 'text-blue-400'),
      this.createBlock('Losses', this.formatValue(stats.losses), 'text-red-400')
    ];
  }

  private createBlock(label: string, value: string | number, colorClass: string): string {
    return `
      <div class="text-center p-3 bg-white/10 rounded-lg backdrop-blur-sm">
        <div class="text-xl md:text-2xl font-bold ${colorClass}">${value}</div>
        <div class="text-xs md:text-sm text-white/80 mt-1">${label}</div>
      </div>
    `;
  }

  render(): string {
    const statsBlocks = this.getStatBlocks();
    if (!statsBlocks.length) return '';

    // Wrap the blocks in the main container
    return `
      <div class="card hover:scale-105 transition-all duration-300">
        ${this.renderHeader()}
        <div class="grid grid-cols-2 gap-4">
          ${statsBlocks.join('')}
        </div>
      </div>
    `;
  }

  private renderHeader(): string {
    return `
      <h3 class="text-lg md:text-xl font-semibold mb-4 md:mb-6 flex items-center text-white">
        <span class="text-xl md:text-2xl mr-3">🎮</span>
        Your Statistics
      </h3>
    `;
  }
}
