import type { AccountProfile } from '@/types/index.js';

export class StatsCard {
  private playerData: AccountProfile;

  constructor(user: AccountProfile) {
    this.playerData = user;
  }

  render(): string {
    return this.playerData ? this.buildCardHTML() : this.buildErrorHTML();
  }

  private buildCardHTML(): string {
    const stats = this.playerData.stats ?? this.getEmptyStats();
    const totalGames = this.calculateTotalGames(stats);
    const winPercentage = this.calculateWinRate(stats.wins, totalGames);

    return `
      <div class="bg-gray-800 rounded-lg p-6">
        ${this.renderTitle()}
        ${this.renderStatsGrid(stats, totalGames, winPercentage)}
      </div>
    `;
  }

  private buildErrorHTML(): string {
    return `
      <div class="bg-gray-800 rounded-lg p-6">
        <div class="text-center py-8">
          <div class="text-red-500 text-4xl mb-4">📊</div>
          <h3 class="text-lg font-medium text-red-400 mb-2">Erreur</h3>
          <p class="text-gray-400">Impossible de charger les statistiques</p>
        </div>
      </div>
    `;
  }

  private renderTitle(): string {
    return `
      <h2 class="text-xl font-bold mb-6 text-primary-400 flex items-center">
        <svg class="w-6 h-6 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24">
          <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2"
            d="M9 19v-6a2 2 0 00-2-2H5a2 2 0 00-2 2v6a2 2 0 002 2h2a2 2 0 002-2zm0 0V9a2 2 0 012-2h2a2 2 0 012 2v10m-6 0a2 2 0 002 2h2a2 2 0 002-2m0 0V5a2 2 0 012-2h2a2 2 0 012 2v14a2 2 0 01-2 2h-2a2 2 0 01-2-2z">
          </path>
        </svg>
        Statistics
      </h2>
    `;
  }

  private renderStatsGrid(stats: any, totalGames: number, winRate: number): string {
    const winRateColor = this.getWinRateColor(winRate);
    const bgClass = this.getWinRateBg(winRate);
    const borderClass = this.getWinRateBorder(winRate);

    return `
      <div class="grid grid-cols-2 md:grid-cols-4 gap-4 mb-6">
        ${this.renderStatItem(stats.wins, 'Wins', 'text-green-400', 'bg-green-900/20', 'border-green-700/30')}
        ${this.renderStatItem(stats.losses, 'Losses', 'text-red-400', 'bg-red-900/20', 'border-red-700/30')}
        ${this.renderStatItem(totalGames, 'Total Games', 'text-blue-400', 'bg-blue-900/20', 'border-blue-700/30')}
        <div class="text-center p-4 ${bgClass} rounded-lg border ${borderClass}">
          <div class="text-2xl font-bold ${winRateColor} mb-1">${winRate}%</div>
          <div class="text-gray-400 text-sm mb-2">Win Rate</div>
          <div class="w-full bg-gray-600 rounded-full h-2">
            <div class="${winRateColor.replace('text-', 'bg-')} h-2 rounded-full transition-all duration-500" style="width: ${winRate}%"></div>
          </div>
        </div>
      </div>
    `;
  }

  private renderStatItem(value: number, label: string, color: string, bg: string, border: string): string {
    return `
      <div class="text-center p-4 ${bg} rounded-lg border ${border}">
        <div class="text-2xl font-bold ${color} mb-1">${value}</div>
        <div class="text-gray-400 text-sm">${label}</div>
      </div>
    `;
  }

  private getEmptyStats() {
    return {
      wins: 0,
      losses: 0,
      totalGames: 0,
      winRate: 0,
      rank: 0,
      highestScore: 0,
      currentStreak: 0,
      longestStreak: 0
    };
  }

  private calculateTotalGames(stats: any): number {
    return (stats.wins ?? 0) + (stats.losses ?? 0);
  }

  private calculateWinRate(wins: number, totalGames: number): number {
    return totalGames > 0 ? Math.round((wins / totalGames) * 100) : 0;
  }

  private getWinRateColor(rate: number): string {
    switch (true) {
      case rate >= 70: return 'text-green-400';
      case rate >= 50: return 'text-yellow-400';
      case rate >= 30: return 'text-orange-400';
      default: return 'text-red-400';
    }
  }

  private getWinRateBg(rate: number): string {
    return rate >= 70 ? 'bg-green-900/20' : rate >= 50 ? 'bg-yellow-900/20' : rate >= 30 ? 'bg-orange-900/20' : 'bg-red-900/20';
  }

  private getWinRateBorder(rate: number): string {
    return rate >= 70 ? 'border-green-700/30' : rate >= 50 ? 'border-yellow-700/30' : rate >= 30 ? 'border-orange-700/30' : 'border-red-700/30';
  }
}
