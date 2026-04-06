import type { CompletedMatchRecord } from '@/types/index.js';
import { userProfileService } from '../services/userProfileService.js';
import { DevConsole } from '@/utils/devConsole.js';

export class MatchHistoryCard {
  private matchesToShow: CompletedMatchRecord[];
  private resultFilter: string = 'all';
  private modeFilter: string = 'all';

  constructor(private matchHistory: CompletedMatchRecord[], private isProfileOwner: boolean) {
    this.matchesToShow = [...matchHistory];
    DevConsole.print('MatchHistoryCard initialized with matches:', matchHistory);
  }

  mountFilters(container: Element) {
    const resultSelect = container.querySelector('#match-filter') as HTMLSelectElement;
    const modeSelect = container.querySelector('#mode-filter') as HTMLSelectElement;
    if (!resultSelect || !modeSelect) {
      DevConsole.reportError('Filter elements missing');
      return;
    }

    const handleChange = () => {
      const selectedResult = resultSelect.value || 'all';
      const selectedMode = modeSelect.value || 'all';
      this.filterMatches(selectedResult, selectedMode);
      this.refreshVisuals(container);
    };

    resultSelect.addEventListener('change', handleChange);
    modeSelect.addEventListener('change', handleChange);

    DevConsole.print('Filter events successfully mounted');
  }

  filterMatches(result: string = 'all', mode: string = 'all') {
    DevConsole.print('Filtering matches by:', { result, mode });
    this.resultFilter = result;
    this.modeFilter = mode;

    this.matchesToShow = this.matchHistory.filter((m) => {
      const passesResult = result === 'all' ? true : result === 'wins' ? m.result === 'win' : m.result === 'loss';
      const passesMode = mode === 'all' ? true : (m.gameMode || '').toLowerCase() === mode.toLowerCase();
      return passesResult && passesMode;
    });

    DevConsole.print('Matches after filter:', this.matchesToShow.length, 'of', this.matchHistory.length);
  }

  render(): string {
    const heroSection = `
      <h2 class="text-xl font-bold text-primary-400 flex items-center mb-6">
        <svg class="w-6 h-6 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24">
          <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 5H7a2 2 0 00-2 2v10a2 2 0 002 2h8a2 2 0 002-2V7a2 2 0 00-2-2h-2M9 5a2 2 0 002 2h2a2 2 0 002-2M9 5a2 2 0 012-2h2a2 2 0 012 2"></path>
        </svg>
        Match History
      </h2>
    `;

    return `
      <div class="bg-gray-800 rounded-lg p-6">
        <div class="flex justify-between items-center mb-6">
          ${heroSection}
          ${this.generateFilters()}
        </div>
        ${this.generateStatsSection()}
        ${this.generateMatchList()}
      </div>
    `;
  }

  private generateFilters(): string {
    const modes = Array.from(new Set(this.matchHistory.map(m => m.gameMode).filter(Boolean)));
    return `
      <div class="flex flex-col sm:flex-row gap-2">
        <select id="match-filter" class="bg-gray-700 text-white text-sm rounded px-3 py-1 border border-gray-600">
          <option value="all" ${this.resultFilter === 'all' ? 'selected' : ''}>All Results</option>
          <option value="wins" ${this.resultFilter === 'wins' ? 'selected' : ''}>Wins Only</option>
          <option value="losses" ${this.resultFilter === 'losses' ? 'selected' : ''}>Losses Only</option>
        </select>
        <select id="mode-filter" class="bg-gray-700 text-white text-sm rounded px-3 py-1 border border-gray-600">
          <option value="all" ${this.modeFilter === 'all' ? 'selected' : ''}>All Modes</option>
          ${modes.length > 0
            ? modes.map(m => `<option value="${m.toLowerCase()}" ${this.modeFilter === m.toLowerCase() ? 'selected' : ''}>${this.formatModeName(m)}</option>`).join('')
            : `
              <option value="local" ${this.modeFilter === 'local' ? 'selected' : ''}>Local</option>
              <option value="remote" ${this.modeFilter === 'remote' ? 'selected' : ''}>Remote</option>
              <option value="tournament" ${this.modeFilter === 'tournament' ? 'selected' : ''}>Tournament</option>`}
        </select>
      </div>
    `;
  }

  private generateStatsSection(): string {
    if (this.matchesToShow.length === 0) return '';
    const wins = this.matchesToShow.reduce((acc, m) => acc + (m.result === 'win' ? 1 : 0), 0);
    const losses = this.matchesToShow.length - wins;
    const total = this.matchesToShow.length;
    const winRate = total ? Math.round((wins / total) * 100) : 0;

    return `
      <div class="bg-gradient-to-br from-gray-700/50 to-gray-800/50 rounded-xl p-6 mb-6 border border-gray-600/30">
        <div class="grid grid-cols-1 lg:grid-cols-2 gap-8 items-center">
          ${this.generatePieChart(winRate, wins, losses)}
          ${this.generateDetailedStats(total, wins, losses, winRate)}
        </div>
        ${this.generateModeBars()}
      </div>
    `;
  }

  private generatePieChart(winRate: number, wins: number, losses: number): string {
    const winAngle = (winRate / 100) * 360;
    const winPath = this.createArc(80, 80, 60, -90, -90 + winAngle);
    const lossPath = this.createArc(80, 80, 60, -90 + winAngle, 270);
    return `
      <div class="flex flex-col items-center">
        <div class="relative w-40 h-40 mb-4">
          <svg class="w-40 h-40 drop-shadow-lg" viewBox="0 0 160 160">
            <defs>
              <radialGradient id="winGrad"><stop offset="0%" stop-color="#34d399"/><stop offset="100%" stop-color="#10b981"/></radialGradient>
              <radialGradient id="lossGrad"><stop offset="0%" stop-color="#f87171"/><stop offset="100%" stop-color="#ef4444"/></radialGradient>
            </defs>
            ${losses > 0 ? `<path d="${lossPath}" fill="url(#lossGrad)"/>` : ''}
            ${wins > 0 ? `<path d="${winPath}" fill="url(#winGrad)"/>` : ''}
            ${wins === 0 && losses === 0 ? `<circle cx="80" cy="80" r="60" fill="#374151" stroke="#4B5563" stroke-width="2"/>` : ''}
          </svg>
        </div>
        <div class="flex gap-4 text-sm">
          <div class="flex items-center gap-2"><div class="w-3 h-3 rounded-full bg-emerald-500"></div>Wins (${wins})</div>
          <div class="flex items-center gap-2"><div class="w-3 h-3 rounded-full bg-red-500"></div>Losses (${losses})</div>
        </div>
      </div>
    `;
  }

  private generateDetailedStats(total: number, wins: number, losses: number, winRate: number): string {
    const stats = [
      { value: wins, label: "Wins", bg: "bg-emerald-900/30", text: "text-emerald-400", border: "border-emerald-700/50" },
      { value: losses, label: "Losses", bg: "bg-red-900/30", text: "text-red-400", border: "border-red-700/50" },
      { value: total, label: "Total", bg: "bg-blue-900/30", text: "text-blue-400", border: "border-blue-700/50" },
      { value: winRate, label: "Win Rate", bg: "bg-purple-900/30", text: "text-purple-400", border: "border-purple-700/50" },
    ];
    return `<div class="grid grid-cols-2 gap-4">${stats.map(s => `
      <div class="text-center p-4 ${s.bg} rounded-lg border ${s.border} hover:bg-opacity-40 transition-colors">
        <div class="text-3xl font-bold ${s.text} mb-2">${s.value}${s === stats[3] ? '%' : ''}</div>
        <div class="text-sm text-gray-300 uppercase tracking-wide">${s.label}</div>
      </div>
    `).join('')}</div>`;
  }

  private generateModeBars(): string {
    const modeCounts = this.matchesToShow.reduce((acc, m) => {
      if (m.gameMode) acc[m.gameMode] = (acc[m.gameMode] || 0) + 1;
      return acc;
    }, {} as Record<string, number>);
    if (!Object.keys(modeCounts).length) return '';

    const colors = ['bg-blue-500', 'bg-green-500', 'bg-purple-500', 'bg-yellow-500', 'bg-pink-500'];
    return `
      <div class="mt-6 pt-6 border-t border-gray-600/50 space-y-3">
        ${Object.entries(modeCounts).map(([mode, count], i) => {
          const width = (count / this.matchesToShow.length) * 100;
          const color = colors[i % colors.length];
          return `
            <div class="group hover:bg-gray-700/30 p-3 rounded-lg transition-all duration-200">
              <div class="flex items-center justify-between text-sm mb-2">
                <span class="text-gray-200 font-medium">${this.formatModeName(mode)}</span>
                <span class="text-gray-400 bg-gray-700 px-2 py-1 rounded text-xs font-mono">${count} (${Math.round(width)}%)</span>
              </div>
              <div class="bg-gray-600 rounded-full h-3 overflow-hidden">
                <div class="${color} h-3 rounded-full transition-all duration-500 ease-out shadow-lg" style="width:${width}%"></div>
              </div>
            </div>
          `;
        }).join('')}
      </div>
    `;
  }

  private generateMatchList(): string {
    if (!this.matchesToShow.length) return this.renderNoMatches();
    const recent = this.matchesToShow.slice(0, 10);
    return `
      <div class="space-y-3 max-h-96 overflow-y-auto scroller-themed">
        ${recent.map(m => this.renderMatch(m)).join('')}
      </div>
      ${this.matchesToShow.length > 10 ? `<div class="mt-6 pt-4 border-t border-gray-700"><button id="view-all-matches" class="w-full action-secondary">View All Matches</button></div>` : ''}
      ${this.renderQuickStats()}
    `;
  }

  private renderMatch(match: CompletedMatchRecord): string {
    const win = match.result === 'win';
    const resultClasses = win ? { text: 'text-emerald-400', bg: 'bg-emerald-900/20', border: 'border-emerald-500/50', icon: 'bg-emerald-500' }
                              : { text: 'text-red-400', bg: 'bg-red-900/20', border: 'border-red-500/50', icon: 'bg-red-500' };
    const avatar = userProfileService.getAvatarUrl(match.opponentAvatar) || '/default.jpg';
    return `
      <div class="flex items-center justify-between p-4 ${resultClasses.bg} rounded-xl border-l-4 ${resultClasses.border} transition-all backdrop-blur-sm">
        <div class="flex items-center space-x-4">
          <div class="flex flex-col items-center">
            <div class="w-4 h-4 rounded-full ${resultClasses.icon} mb-2 shadow-lg flex items-center justify-center">
              ${win ? '<svg class="w-2 h-2 text-white" ...></svg>' : '<svg class="w-2 h-2 text-white" ...></svg>'}
            </div>
            <span class="${resultClasses.text} font-bold text-xs uppercase tracking-wider">${"No matches found"}</span>
          </div>
          <div class="flex items-center space-x-3 flex-1">
            <span class="text-white font-semibold text-lg">vs ${match.opponent}</span>
            <img src="${avatar}" alt="${match.opponent}" class="w-10 h-10 rounded-full bg-gray-600 object-cover border-2 border-gray-500 shadow-md" onerror="this.src='/default.jpg'"/>
            ${match.gameMode ? `<span class="px-3 py-1 bg-gray-600 rounded-full text-xs text-gray-300 font-medium">${this.formatModeName(match.gameMode)}</span>` : ''}
          </div>
        </div>
        <div class="text-right text-white font-bold text-2xl font-mono">${match.score.player} - ${match.score.opponent}</div>
      </div>
    `;
  }

  private renderQuickStats(): string {
    if (!this.matchesToShow.length) return '';
    const wins = this.matchesToShow.filter(m => m.result === 'win').length;
    const total = this.matchesToShow.length;
    const winRate = total ? Math.round((wins / total) * 100) : 0;
    return `
      <div class="mt-6 pt-6 border-t border-gray-700 grid grid-cols-3 gap-4 text-center">
        <div class="bg-blue-900/40 p-4 rounded-xl border border-blue-700/30"><div class="text-2xl font-bold text-blue-400">${total}</div><div class="text-xs text-gray-300 uppercase tracking-wide">${"No matches found"}</div></div>
        <div class="bg-green-900/40 p-4 rounded-xl border border-green-700/30"><div class="text-2xl font-bold ${winRate >= 50 ? 'text-green-400' : 'text-red-400'}">${winRate}%</div><div class="text-xs text-gray-300 uppercase tracking-wide">${"No matches found"}</div></div>
        <div class="bg-purple-900/40 p-4 rounded-xl border border-purple-700/30"><div class="text-2xl font-bold text-purple-400">${wins}</div><div class="text-xs text-gray-300 uppercase tracking-wide">${"No matches found"}</div></div>
      </div>
    `;
  }

  private renderNoMatches(): string {
    return `
      <div class="text-center py-12">
        <div class="text-gray-400 text-6xl mb-4">🏓</div>
        <h3 class="text-lg font-medium text-gray-300 mb-2">No matches found</h3>
        <p class="text-gray-500 mb-6">Start playing to see your match history here</p>
        ${this.isProfileOwner ? `<button class="action-primary" onclick="window.dispatchEvent(new CustomEvent('navigate', { detail: '/game' }))">Play Game</button>` : ''}
      </div>
    `;
  }

  private createArc(cx: number, cy: number, r: number, startDeg: number, endDeg: number): string {
    const startRad = (startDeg * Math.PI) / 180;
    const endRad = (endDeg * Math.PI) / 180;
    const x1 = cx + r * Math.cos(startRad);
    const y1 = cy + r * Math.sin(startRad);
    const x2 = cx + r * Math.cos(endRad);
    const y2 = cy + r * Math.sin(endRad);
    const largeArc = endDeg - startDeg <= 180 ? 0 : 1;
    return `M ${cx} ${cy} L ${x1} ${y1} A ${r} ${r} 0 ${largeArc} 1 ${x2} ${y2} Z`;
  }

  private formatModeName(mode: string): string {
    const mapping: Record<string, string> = { local: 'Local', remote: 'Remote', tournament: 'Tournament' };
    return mapping[mode] || mode.charAt(0).toUpperCase() + mode.slice(1);
  }

  private formatDate(dateStr: string): string {
    const date = new Date(dateStr);
    const diff = Math.floor((Date.now() - date.getTime()) / (1000 * 60 * 60 * 24));
    return diff === 0 ? 'Today' : diff === 1 ? 'Yesterday' : diff < 7 ? `${diff} days ago` : date.toLocaleDateString('fr-FR');
  }

  private formatDuration(sec: number): string {
    const m = Math.floor(sec / 60);
    const s = sec % 60;
    return `${m}:${s.toString().padStart(2, '0')}`;
  }

  private refreshVisuals(container: Element) {
    const statsEl = container.querySelector('.bg-gradient-to-br.from-gray-700\\/50');
    if (statsEl) statsEl.replaceWith(this.createElementFromHTML(this.generateStatsSection()));
    const matchesEl = container.querySelector('.space-y-3.max-h-96');
    if (matchesEl) matchesEl.innerHTML = this.matchesToShow.slice(0, 10).map(m => this.renderMatch(m)).join('');
    const quickStatsEl = container.querySelector('.mt-6.pt-6.border-t');
    if (quickStatsEl) quickStatsEl.replaceWith(this.createElementFromHTML(this.renderQuickStats()));
  }

  private createElementFromHTML(html: string): HTMLElement {
    const div = document.createElement('div');
    div.innerHTML = html.trim();
    return div.firstElementChild as HTMLElement;
  }
}
