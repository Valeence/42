import { userAuthenticationService } from '@/features/auth/services/userAuthenticationService';
import { serverStatsService } from '../services/serverStatsService';
import { DevConsole } from '@/utils/devConsole.js'; 
import { HeroSection } from '../components/WelcomeSection';
import { GlobalStatsCard } from '../components/ServerStatsCard';
import { UserStatsCard } from '../components/PlayerStatsCard';
import { GameModeButtons } from '../components/PlayModeButtons';
import type { ServerSnapshot, GameModeHandlers } from '@/types/index.js';

export class HomePage {
  private authListener: (() => void) | null = null;
  private globalStatsData: ServerSnapshot | null = null;

  async mount(selector: string): Promise<void> {
    const element = document.querySelector(selector);
    if (!element) return;

    this.destroy();
    await Promise.all([this.loadGlobalStats(), this.verifyAuthentication()]);
    this.render(element);
    this.setupEventListeners();
  }

  destroy(): void {
    DevConsole.print('🧹 Cleaning up HomePage...');
    if (this.authListener) {
      window.removeEventListener('authStateChanged', this.authListener);
      this.authListener = null;
    }
  }

  private async loadGlobalStats(): Promise<void> {
    try {
      DevConsole.print('📊 Loading global stats...');
      this.globalStatsData = await serverStatsService.getGlobalStats();
      DevConsole.print('✅ Global stats loaded:', this.globalStatsData);
    } catch (error) {
      DevConsole.reportError('❌ Failed to load global stats:', error);
      this.globalStatsData = { totalPlayers: 0, totalGames: 0, onlinePlayers: 0 };
    }
  }

  private async verifyAuthentication(): Promise<void> {
    try {
      DevConsole.print('🔐 Checking user authentication...');
      if (userAuthenticationService.isAuthenticated()) {
        const currentUser = userAuthenticationService.getCurrentUser();
        if (!currentUser?.stats) await userAuthenticationService.loadCurrentUser();
      }
      DevConsole.print('✅ Authentication verified');
    } catch (error) {
      DevConsole.reportError('❌ Failed to verify authentication:', error);
    }
  }

  private setupEventListeners(): void {
    DevConsole.print('🎧 Setting up event listeners...');
    this.authListener = () => {
      DevConsole.print('🔐 Auth state changed, re-rendering page');
      const element = document.querySelector('#page-content');
      if (element) this.render(element);
    };
    window.addEventListener('authStateChanged', this.authListener);
  }

  private render(element: Element): void {
    DevConsole.print('🎨 Rendering HomePage...');
    const isAuthenticated = userAuthenticationService.isAuthenticated();
    const currentUser = userAuthenticationService.getCurrentUser();

    const heroSection = new HeroSection();
    const userStatsCard = isAuthenticated && currentUser ? new UserStatsCard(currentUser) : null;
    const globalStatsCard = this.globalStatsData ? new GlobalStatsCard(this.globalStatsData) : null;

    const gameModeCallbacks: GameModeHandlers = {
      onLocalGame: () => window.dispatchEvent(new CustomEvent('navigate', { detail: '/game?mode=local' })),
      onRemoteGame: () => {
        if (isAuthenticated) {
          window.dispatchEvent(new CustomEvent('navigate', { detail: '/game?mode=remote' }));
        } else {
          window.dispatchEvent(new CustomEvent('navigate', { detail: '/login?redirect=/game?mode=remote' }));
        }
      },
      onTournament: () => window.dispatchEvent(new CustomEvent('navigate', { detail: '/game?mode=tournament' })),
      onLogin: () => window.dispatchEvent(new CustomEvent('navigate', { detail: '/login?redirect=/game?mode=remote' })),
    };

    const gameModeButtons = new GameModeButtons(isAuthenticated, gameModeCallbacks);

    element.innerHTML = `
      <div class="min-h-screen text-white">
        <div class="container mx-auto px-4 py-8">
          ${heroSection.render()}
          ${this.renderStatsSection(globalStatsCard, userStatsCard)}
          ${gameModeButtons.render()}
        </div>
      </div>
    `;
    gameModeButtons.bindEvents();
    DevConsole.print('✅ HomePage rendered successfully');
  }

  private renderStatsSection(globalStatsCard: GlobalStatsCard | null, userStatsCard: UserStatsCard | null): string {
    if (!globalStatsCard && !userStatsCard) {
      DevConsole.print('📊 No stats to display');
      return '';
    }

    if (globalStatsCard && !userStatsCard) {
      DevConsole.print('📊 Displaying only global stats');
      return `<div class="flex justify-center mb-12">
                <div class="w-full max-w-md">${globalStatsCard.render()}</div>
              </div>`;
    }

    if (!globalStatsCard && userStatsCard) {
      DevConsole.print('📊 Displaying only user stats');
      return `<div class="flex justify-center mb-12">
                <div class="w-full max-w-md">${userStatsCard.render()}</div>
              </div>`;
    }

    DevConsole.print('📊 Displaying global and user stats');
    return `<div class="grid grid-cols-1 lg:grid-cols-2 gap-6 max-w-4xl mx-auto mb-12">
              ${globalStatsCard.render()}
              ${userStatsCard.render()}
            </div>`;
  }
}
