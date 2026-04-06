import { userAuthenticationService } from '@/features/auth/services/userAuthenticationService';
import { DevConsole } from '@/utils/devConsole.js';
import type { ArenaSettings } from '@/types/index.js';
import { competitionService } from '../services/competitionService';
import { TournamentPage } from './CompetitionPage';

const DEFAULT_PARTICIPANT_TOTAL = 8;
type TournamentGameSettings = {
  ballSpeed: ArenaSettings['ballSpeed'];
  winScore: number;
  powerUps: boolean;
};

export class TournamentCreatePage
{
  private participantCount: number = DEFAULT_PARTICIPANT_TOTAL;
  private isAuthenticated: boolean = false;
  private tournamentParticipants: string[] = [];
  private gameSettings: TournamentGameSettings | null = null;
  async mount(selector: string): Promise<void>
  {
    const element = document.querySelector(selector);
    if (!element) return;

    const urlParams = new URLSearchParams(window.location.search);
    const mode = this.initializeFromParams(urlParams);

    if (this.shouldRedirectToLogin(mode))
    {
      this.redirectToLogin();
      return;
    }

    this.render(element);
    this.bindEvents();
  }
  private collectParticipantNames(inputs: NodeListOf<HTMLInputElement>): string[]
  {
    return Array.from(inputs).map(input => input.value.trim());
  }
  private buildFinalParticipants(enteredParticipants: string[]): string[]
  {
    if (!this.isAuthenticated)
    {
      return [...enteredParticipants];
    }
    if (!userAuthenticationService.isAuthenticated())
    {
      throw new Error('Session expirée. Veuillez vous reconnecter.');
    }
    const currentUser = userAuthenticationService.getCurrentUser();
    if (!currentUser || !currentUser.username)
    {
      throw new Error('Impossible de récupérer les informations utilisateur.');
    }
    return [currentUser.username, ...enteredParticipants];
  }
  private assertTournamentRules(finalParticipants: string[]): void
  {
    if (finalParticipants.length !== DEFAULT_PARTICIPANT_TOTAL)
    {
      throw new Error('Le tournoi doit avoir exactement 8 participants.');
    }
    const uniqueParticipants = new Set(finalParticipants.map(p => p.toLowerCase()));
    if (uniqueParticipants.size !== finalParticipants.length)
    {
      throw new Error('Tous les participants doivent avoir des noms uniques.');
    }
  }
  private initializeFromParams(params: URLSearchParams): string | null
  {
    const mode = params.get('mode');
    const participantValue = parseInt(params.get('participants') || `${DEFAULT_PARTICIPANT_TOTAL}`, 10);
    this.participantCount = Number.isFinite(participantValue) ? participantValue : DEFAULT_PARTICIPANT_TOTAL;
    this.gameSettings = this.extractGameSettings(params);
    this.isAuthenticated = mode === 'authenticated' && userAuthenticationService.isAuthenticated();
    return mode;
  }
  private extractGameSettings(params: URLSearchParams): TournamentGameSettings
  {
    const allowedSpeeds = ['slow', 'medium', 'fast'] as const;
    const rawSpeed = params.get('ballSpeed');
    const ballSpeed = allowedSpeeds.includes(rawSpeed as typeof allowedSpeeds[number])
      ? rawSpeed as TournamentGameSettings['ballSpeed']
      : 'medium';
    return {
      ballSpeed,
      winScore: parseInt(params.get('winScore') || '5', 10),
      powerUps: params.get('powerUps') === 'true'
    };
  }
  private shouldRedirectToLogin(mode: string | null): boolean
  {
    return mode === 'authenticated' && !userAuthenticationService.isAuthenticated();
  }
  private redirectToLogin(): void
  {
    window.dispatchEvent(new CustomEvent('navigate', {
      detail: '/login?redirect=' + encodeURIComponent(window.location.pathname + window.location.search)
    }));
  }
  private render(element: Element): void
  {
    const currentUser = userAuthenticationService.getCurrentUser();
    element.innerHTML = `
      <div class="min-h-screen">
        <div class="max-w-2xl mx-auto px-4 py-8">
          <div class="card">
          <h1 class="text-3xl font-bold text-center mb-8">
            Create Tournament
          </h1>
          ${this.isAuthenticated ? `
            <div class="mb-6 p-4 bg-blue-900/30 rounded-lg border border-blue-700/50">
              <p class="text-blue-300">
                <strong>You are the host</strong><br>
                You will be automatically added as the first participant
              </p>
              <div class="mt-2 flex items-center gap-2">
                <div class="w-10 h-10 bg-blue-600 rounded-full flex items-center justify-center">
                  <span class="text-white font-bold">1</span>
                </div>
                <span class="text-white font-medium">${currentUser?.username || 'You'}</span>
                <span class="text-green-400">✓ Confirmed</span>
              </div>
            </div>
          ` : `
            <div class="mb-6 p-4 bg-purple-900/30 rounded-lg border border-purple-700/50">
              <p class="text-purple-300">
                You are creating a local tournament. All participants will play on this device.
              </p>
            </div>
          `}
          <form id="tournament-form" class="space-y-4">
            <div id="participants-container">
              ${this.renderParticipantInputs()}
            </div>
            <div class="flex gap-4 pt-6">
              <button
                type="button"
                id="cancel-action-trigger"
                class="flex-1 bg-gray-600 hover:bg-gray-700 text-white py-3 px-6 rounded-lg transition-colors"
              >
                Cancel
              </button>
              <button
                type="submit"
                id="create-tournament-action-trigger"
                class="flex-1 bg-primary-600 hover:bg-primary-700 text-white py-3 px-6 rounded-lg transition-colors disabled:opacity-50"
              >
                Create Tournament
              </button>
            </div>
          </form>
          </div>
        </div>
      </div>
    `;
  }
  private renderParticipantInputs(): string
  {
    const startIndex = this.isAuthenticated ? 2 : 1;
    const endIndex = this.participantCount;
    return Array.from({ length: endIndex - startIndex + 1 }, (_, offset) =>
    {
      const index = startIndex + offset;
      return `
        <div class="flex items-center gap-3">
          <div class="w-10 h-10 bg-gray-600 rounded-full flex items-center justify-center">
            <span class="text-white font-bold">${index}</span>
          </div>
          <input
            type="text"
            id="participant-${index}"
            placeholder="Enter participant name"
            class="flex-1 bg-gray-700 border border-gray-600 rounded-lg px-4 py-3 text-white placeholder-gray-400 focus:border-primary-500 focus:outline-none"
            required
            maxlength="20"
          />
        </div>
      `;
    }).join('');
  }
  private bindEvents(): void
  {
    const form = document.getElementById('tournament-form') as HTMLFormElement | null;
    const cancelBtn = document.getElementById('cancel-action-trigger');

    form?.addEventListener('submit', (event) => this.handleFormSubmit(event));
    cancelBtn?.addEventListener('click', () => this.handleCancel());

    this.getParticipantInputs().forEach(input =>
    {
      input.addEventListener('input', () => this.validateForm());
    });
  }
  private handleFormSubmit(event: Event): void
  {
    event.preventDefault();
    void this.handleCreateTournament();
  }
  private handleCancel(): void
  {
    window.dispatchEvent(new CustomEvent('navigate', { detail: '/' }));
  }
  private getParticipantInputs(): NodeListOf<HTMLInputElement>
  {
    return document.querySelectorAll('input[id^="participant-"]') as NodeListOf<HTMLInputElement>;
  }
  private validateForm(): boolean
  {
    const inputs = this.getParticipantInputs();
    const submitBtn = document.getElementById('create-tournament-action-trigger') as HTMLButtonElement;
    const allFilled = Array.from(inputs).every(input => input.value.trim().length > 0);
    const allUnique = new Set(Array.from(inputs).map(input => input.value.trim().toLowerCase())).size === inputs.length;
    const isValid = allFilled && allUnique;
    submitBtn.disabled = !isValid;
    return isValid;
  }
  private async handleCreateTournament(): Promise<void>
  {
    try
    {
      const inputs = this.getParticipantInputs();
      const enteredParticipants = this.collectParticipantNames(inputs);
      const finalParticipants = this.buildFinalParticipants(enteredParticipants);

      this.assertTournamentRules(finalParticipants);

      const tournamentResponse = await competitionService.createTournament(
        finalParticipants,
        this.gameSettings 
      );
      DevConsole.print('Tournament created:', tournamentResponse);
      const tournamentPage = new TournamentPage();
      const tournamentData = tournamentResponse.tournament ?? tournamentResponse;
      await tournamentPage.mount('#page-content', tournamentData);
      window.history.pushState(
        { tournamentId: tournamentData.id },
        '',
        `/tournament/${tournamentData.id}`
      );
    }
    catch (error)
    {
      DevConsole.reportError('Failed to create tournament:', error);
      const errorMessage = (error as Error).message || 'Une erreur est survenue lors de la création du tournoi.';
      this.showError(errorMessage);
    }
  }
  private showError(message: string): void
  {
    let errorElement = document.getElementById('tournament-error');
    if (!errorElement)
    {
      errorElement = document.createElement('div');
      errorElement.id = 'tournament-error';
      errorElement.className = 'mt-4 p-3 bg-red-900/30 border border-red-700/50 rounded-lg text-red-300 text-sm';
      const form = document.getElementById('tournament-form');
      form?.insertBefore(errorElement, form.firstChild);
    }
    errorElement.textContent = message;
    setTimeout(() =>
    {
      errorElement?.remove();
    }, 5000);
  }
}
