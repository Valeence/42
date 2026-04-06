import { DevConsole } from '@/utils/devConsole.js';
import { competitionService } from '../services/competitionService';
import { TournamentBracket } from '../components/CompetitionBracket';
import { TournamentMatch as TournamentMatchComponent } from '../components/CompetitionMatch';
export class TournamentPage
{
  private tournament: any = null;
  private currentMatch: any = null;
  private getPageElement(selector: string): Element | null
  {
    return document.querySelector(selector);
  }
  private ensureBracketStructure(): any
  {
    if (!this.tournament.bracket)
    {
      this.tournament.bracket = {
        quarterFinals: [],
        semiFinals: [],
        final: null
      };
    }
    return this.tournament.bracket;
  }
  private applyTournamentData(tournamentData: any): void
  {
    this.tournament = tournamentData;
    this.currentMatch = tournamentData?.nextMatch ?? null;
  }
  private extractTournamentIdFromLocation(): number | null
  {
    const pathParts = window.location.pathname.split('/');
    const idCandidate = parseInt(pathParts[pathParts.length - 1], 10);
    return Number.isFinite(idCandidate) ? idCandidate : null;
  }
  async mount(selector: string, tournamentData?: any): Promise<void>
  {
    const element = this.getPageElement(selector);
    if (!element) return;

    if (tournamentData)
    {
      this.applyTournamentData(tournamentData);
      this.render(element);
      this.bindEvents();
      return;
    }

    const tournamentId = this.extractTournamentIdFromLocation();
    if (!tournamentId)
    {
      this.renderError(element, 'Tournament not found');
      return;
    }

    await this.loadTournamentData(tournamentId);
    this.render(element);
    this.bindEvents();
  }
  private async loadTournamentData(tournamentId: number): Promise<void>
  {
    try
    {
      DevConsole.print('📊 Chargement des données du tournoi:', tournamentId);
      const tournament = await competitionService.getTournament(tournamentId);
      this.applyTournamentData(tournament);
      DevConsole.print('✅ Données du tournoi chargées:', this.tournament);
    }
    catch (error)
    {
      DevConsole.reportError('❌ Échec du chargement du tournoi:', error);
      throw error;
    }
  }
  private render(element: Element): void
  {
    if (!this.tournament)
    {
      this.renderError(element, 'Failed to load tournament data');
      return;
    }
    DevConsole.print('🎨 Rendu de la page tournoi');

    const bracketData = this.ensureBracketStructure();
    const bracket = new TournamentBracket(bracketData);
    element.innerHTML = `
      <div class="min-h-screen">
        <!-- Header épuré -->
        <div class="navbar">
          <div class="max-w-7xl mx-auto px-4 py-6">
            <div class="flex items-center justify-between">
              <div>
                <h1 class="text-3xl font-bold font-orbitron-alt bg-gradient-to-r from-blue-400 to-purple-500 bg-clip-text text-transparent">
                  Tournament
                </h1>
                <p class="text-gray-400 mt-1">Tournoi #${this.tournament.id}</p>
              </div>
              <div class="text-right">
                <div class="flex items-center gap-3">
                    <div class="text-sm text-gray-400">
                      <div>Participants</div>
                     <div class="text-2xl font-bold text-white">${this.tournament.participants?.length || 0}/8</div>
                    </div>
                </div>
              </div>
            </div>
          </div>
        </div>
        <!-- Contenu principal -->
        <div class="max-w-7xl mx-auto px-4 py-8">
          ${this.renderCurrentMatchSection()}
          <!-- Bracket organigramme -->
          <div class="bg-gray-800/30 backdrop-blur-sm rounded-xl border border-gray-700/50 overflow-hidden">
            <div id="tournament-bracket">
              ${bracket.render()}
            </div>
          </div>
          ${this.renderWinnerSection()}
        </div>
      </div>
    `;
    bracket.bindEvents();
    this.bindMatchDetailsEvents();
  }
  private renderCurrentMatchSection(): string
  {
    if (!this.currentMatch) return '';
    return `
      <!-- Match en cours -->
      <div class="mb-8">
        <div class="bg-gradient-to-r from-blue-900/30 to-purple-900/30 rounded-xl border border-blue-500/30 p-6">
          <h2 class="text-xl font-semibold mb-4 flex items-center gap-2">
            <div class="w-3 h-3 rounded-full bg-blue-500 animate-pulse"></div>
            Current Match
          </h2>
          <div id="current-match-section">
            ${this.renderCurrentMatch()}
          </div>
        </div>
      </div>
    `;
  }
  private renderWinnerSection(): string
  {
    if (this.tournament.status !== 'completed') return '';
    return `
      <!-- Champion -->
      <div class="mt-8 text-center">
        <div class="bg-gradient-to-r from-yellow-900/30 to-orange-900/30 rounded-xl border border-yellow-500/30 p-8">
          <h2 class="text-3xl font-bold text-yellow-400 mb-2">🏆 Champion</h2>
          <p class="text-2xl font-semibold text-white">${this.tournament.winner}</p>
        </div>
      </div>
    `;
  }
  private renderCurrentMatch(): string
  {
    if (!this.currentMatch) return '';
    const match = new TournamentMatchComponent(this.currentMatch, this.tournament.id, this.tournament.gameSettings);
    const html = match.render();
    setTimeout(() =>
    {
      match.bindEvents();
    }, 50);
    return html;
  }
  private renderError(element: Element, message: string): void
  {
    element.innerHTML = `
      <div class="max-w-2xl mx-auto text-center">
        <div class="bg-red-900/30 border border-red-700/50 rounded-lg p-8">
          <h2 class="text-xl font-semibold text-red-400 mb-4">Error</h2>
          <p class="text-gray-300 mb-6">${message}</p>
          <button onclick="window.dispatchEvent(new CustomEvent('navigate', { detail: '/' }))" 
                  class="bg-primary-600 hover:bg-primary-700 px-6 py-3 rounded-lg font-medium transition-colors">
            Back to Home
          </button>
        </div>
      </div>
    `;
  }
  private bindEvents(): void
  {
    DevConsole.print('🎧 Configuration des écouteurs d\'événements');
    window.addEventListener('matchFinished', (event: CustomEvent) =>
    {
      this.handleMatchFinished(event.detail);
    });
    window.addEventListener('refreshTournament', () =>
    {
      this.handleRefreshTournament();
    });
  }
  private bindMatchDetailsEvents(): void
  {
    window.addEventListener('viewMatchDetails', (event: CustomEvent) =>
    {
      const { matchId } = event.detail;
      this.showMatchDetails(matchId);
    });
  }
  private async handleMatchFinished(matchData: any): Promise<void>
  {
    try
    {
      DevConsole.print('🏆 Traitement du match terminé:', matchData);
      const result = await competitionService.finishMatch(
        this.tournament.id,
        matchData.matchNumber,
        matchData.player1,
        matchData.player2,
        matchData.score1,
        matchData.score2,
        matchData.duration
      );
      DevConsole.print(' Réponse du backend:', result);
      if (result.tournament)
      {
        this.tournament = result.tournament;
        this.currentMatch = result.tournament.nextMatch;
      }
      const element = document.querySelector('#page-content');
      if (element) this.render(element);
      this.showMatchResultNotification();
    }
    catch (error)
    {
      DevConsole.reportError('❌ Échec de la finalisation du match:', error);
      this.showNotification('Erreur lors de la sauvegarde du match', 'error');
    }
  }
  private async handleRefreshTournament(): Promise<void>
  {
    if (!this.tournament) return;
    try
    {
      await this.loadTournamentData(this.tournament.id);
      const element = document.querySelector('#page-content');
      if (element) this.render(element);
    }
    catch (error)
    {
      DevConsole.reportError('Échec du rafraîchissement du tournoi:', error);
    }
  }
  private showMatchResultNotification(): void
  {
    const message = this.buildMatchCompletionMessage();
    this.showNotification(message, 'success');
  }
  private buildMatchCompletionMessage(): string
  {
    if (this.tournament.status === 'completed')
    {
      return `🏆 Tournoi terminé ! Gagnant : ${this.tournament.winner || 'Inconnu'}`;
    }
    if (this.currentMatch)
    {
      return `✅ Match terminé ! Prochain match : ${this.currentMatch.round}`;
    }
    return '✅ Match terminé !';
  }
  private showMatchDetails(matchId: number): void
  {
    DevConsole.print('📋 Affichage des détails du match:', matchId);
    const allMatches = [
      ...(this.tournament.bracket?.quarterFinals || []),
      ...(this.tournament.bracket?.semiFinals || []),
      this.tournament.bracket?.final
    ].filter(Boolean);
    const match = allMatches.find(m => m.id === matchId);
    if (!match)
    {
      DevConsole.reportError('Match non trouvé:', matchId);
      return;
    }
    const modal = document.createElement('div');
    modal.className = 'fixed inset-0 bg-black/50 backdrop-blur-sm flex items-center justify-center z-50';
    modal.innerHTML = `
      <div class="bg-gray-800 rounded-xl border border-gray-700 p-6 max-w-md w-full mx-4">
        <div class="flex justify-between items-center mb-4">
          <h3 class="text-xl font-semibold">Détails du Match #${match.id}</h3>
          <button class="text-gray-400 hover:text-white" onclick="this.closest('.fixed').remove()">
            ✕
          </button>
        </div>
        <div class="space-y-4">
          <div class="grid grid-cols-2 gap-4">
            <div class="text-center p-4 bg-gray-700 rounded-lg">
              <div class="font-semibold ${match.winner === match.player1 ? 'text-green-400' : 'text-gray-300'}">
                ${match.player1}
              </div>
              ${match.score1 !== undefined ? `<div class="text-2xl font-bold mt-2">${match.score1}</div>` : ''}
            </div>
            <div class="text-center p-4 bg-gray-700 rounded-lg">
              <div class="font-semibold ${match.winner === match.player2 ? 'text-green-400' : 'text-gray-300'}">
                ${match.player2}
              </div>
              ${match.score2 !== undefined ? `<div class="text-2xl font-bold mt-2">${match.score2}</div>` : ''}
            </div>
          </div>
          <div class="text-center">
            <span class="px-3 py-1 rounded-full text-sm font-medium ${this.getMatchStatusClasses(match.status)}">
              ${this.getMatchStatusText(match.status)}
            </span>
          </div>
        </div>
      </div>
    `;
    document.body.appendChild(modal);
  }
  private getMatchStatusClasses(status: string): string
  {
    switch (status)
    {
      case 'pending': return 'bg-gray-600 text-gray-300';
      case 'in_progress': return 'bg-blue-600 text-blue-100';
      case 'completed': return 'bg-green-600 text-green-100';
      default: return 'bg-gray-600 text-gray-300';
    }
  }
  private getMatchStatusText(status: string): string
  {
    switch (status)
    {
      case 'pending': return 'Pending';
      case 'in_progress': return 'In Progress';
      case 'completed': return 'Completed';
      default: return 'Unknown';
    }
  }
  private getStatusClasses(): string
  {
    switch (this.tournament.status)
    {
      case 'waiting': return 'bg-yellow-900/30 text-yellow-400 border border-yellow-700/50';
      case 'in_progress': return 'bg-blue-900/30 text-blue-400 border border-blue-700/50';
      case 'completed': return 'bg-green-900/30 text-green-400 border border-green-700/50';
      default: return 'bg-gray-900/30 text-gray-400 border border-gray-700/50';
    }
  }
  private showNotification(message: string, type: 'success' | 'error'): void
  {
    DevConsole.print('🔔 Affichage de la notification:', message);
    const notification = this.createNotificationElement(message, type);
    document.body.appendChild(notification);
    setTimeout(() =>
    {
      notification.remove();
    }, 3000);
  }
  private createNotificationElement(message: string, type: 'success' | 'error'): HTMLDivElement
  {
    const notification = document.createElement('div');
    notification.className = `fixed top-4 right-4 z-50 px-6 py-3 rounded-lg font-medium transition-all duration-300 ${
      type === 'success'
        ? 'bg-green-900/30 text-green-400 border border-green-700/50'
        : 'bg-red-900/30 text-red-400 border border-red-700/50'
    }`;
    notification.textContent = message;
    return notification;
  }
}
