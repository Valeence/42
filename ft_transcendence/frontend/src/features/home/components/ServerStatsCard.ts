import type { ServerSnapshot } from '@/types/index.js';

export class GlobalStatsCard {
  constructor(private globalStatsData: ServerSnapshot) {}

  private formatNumber(value: number): string {
    return value.toLocaleString();
  }

  private createStatBlock(formattedValue: string, label: string, colorClass: string): string {
    return `
      <div class="text-center p-3 bg-white/10 rounded-lg backdrop-blur-sm">
        <div class="text-xl md:text-2xl font-bold ${colorClass}">${formattedValue}</div>
        <div class="text-xs md:text-sm text-white/80 mt-1">${label}</div>
      </div>
    `;
  }

  private renderHeader(): string {
    return `
      <h3 class="text-lg md:text-xl font-semibold mb-4 md:mb-6 flex items-center text-white">
        <span class="text-xl md:text-2xl mr-3">📊</span>
        Platform Statistics
      </h3>
    `;
  }

  render(): string {
    const totalPlayers = this.formatNumber(this.globalStatsData.totalPlayers);
    const onlineNow = this.formatNumber(this.globalStatsData.onlinePlayers);
    const totalGames = this.formatNumber(this.globalStatsData.totalGames);

    const blocks = [
      this.createStatBlock(totalPlayers, 'Total Players', 'text-blue-400'),
      this.createStatBlock(totalGames, 'Games Played', 'text-green-400'),
      this.createStatBlock(onlineNow, 'Online Now', 'text-yellow-400')
    ];

    return `
      <div class="card hover:scale-105 transition-all duration-300">
        ${this.renderHeader()}
        <div class="grid grid-cols-1 sm:grid-cols-3 gap-4">
          ${blocks.join('')}
        </div>
      </div>
    `;
  }
}
