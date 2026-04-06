import { userAuthenticationService } from '../../features/auth/services/userAuthenticationService';
import { userProfileService } from '../../features/profile/services/userProfileService';
import { DevConsole } from '@/utils/devConsole.js';

interface NavigationSnapshot {
  isLoggedIn: boolean;
  user: ReturnType<typeof userAuthenticationService.getCurrentUser>;
}

export class PrimaryNavigationBar {
  private mountPoint: Element | null = null;
  private readonly refreshDelay = 120;

  private readonly handleAuthChange = (): void => {
    if (!this.mountPoint) return;
    window.setTimeout(() => {
      if (!this.mountPoint) return;
      this.drawNavigation(this.mountPoint);
      this.hookListeners();
      DevConsole.print('🔄 Navigation refreshed after auth change');
    }, this.refreshDelay);
  };

  bindTo(selector: string): void {
    const target = document.querySelector(selector);
    if (!target) {
      DevConsole.warn('Navigation mount element missing for selector:', selector);
      return;
    }
    this.mountPoint = target;
    window.removeEventListener('authStateChanged', this.handleAuthChange);
    window.addEventListener('authStateChanged', this.handleAuthChange);
    this.drawNavigation(target);
    this.hookListeners();
  }

  unbind(): void {
    window.removeEventListener('authStateChanged', this.handleAuthChange);
    this.mountPoint = null;
  }

  private drawNavigation(element: Element): void {
    const state: NavigationSnapshot = {
      isLoggedIn: userAuthenticationService.isAuthenticated(),
      user: userAuthenticationService.getCurrentUser()
    };

    element.innerHTML = `
      <nav class="bg-gray-800 shadow-lg">
        <div class="container mx-auto px-4">
          <div class="flex justify-between items-center h-16">
            <div class="flex items-center space-x-4">
              <h1 class="text-2xl font-orbitron font-bold text-primary-400">
                ft_transcendence
              </h1>
            </div>
            <div class="hidden md:flex items-center space-x-6">
              <a href="/" class="topbar-link">Home</a>
              <a href="/game" class="topbar-link">Play</a>
              ${state.isLoggedIn && state.user ? this.renderAuthenticatedLinks(state.user) : this.renderGuestLinks()}
            </div>
            <button id="nav-toggle-button" class="md:hidden text-white">
              <svg class="w-6 h-6" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 6h16M4 12h16M4 18h16"></path>
              </svg>
            </button>
          </div>
          ${this.renderMobileMenu(state)}
        </div>
      </nav>
    `;
  }

  private renderAuthenticatedLinks(user: NonNullable<NavigationSnapshot['user']>): string {
    const avatarUrl = userProfileService.getAvatarUrl(user.avatarUrl);
    return `
      <a href="/profile" class="topbar-link">Profile</a>
      <div class="flex items-center space-x-3 ml-4">
        <div class="flex items-center space-x-2 text-gray-300 hover:text-white transition-colors">
          <img
            src="${avatarUrl}"
            alt="${user.username}"
            class="w-8 h-8 rounded-full object-cover border-2 border-gray-600 hover:border-primary-500 transition-colors"
            onerror="this.src='/default.jpg'"
          />
          <span class="font-medium hidden lg:inline">${user.username}</span>
          <div class="w-2 h-2 ${user.isOnline ? 'bg-green-500' : 'bg-gray-500'} rounded-full"></div>
        </div>
        <button id="desktop-signout" class="topbar-link text-red-400 hover:text-red-300 ml-2">
          Logout
        </button>
      </div>
    `;
  }

  private renderGuestLinks(): string {
    return `<a href="/login" class="topbar-link">Login</a>`;
  }

  private renderMobileMenu(state: NavigationSnapshot): string {
    const baseMenu = `
      <div id="nav-mobile-panel" class="hidden md:hidden pb-4">
        <a href="/" class="block py-2 topbar-link">Home</a>
        <a href="/game" class="block py-2 topbar-link">Play</a>
    `;
    const closing = `</div>`;

    if (state.isLoggedIn && state.user) {
      const avatarUrl = userProfileService.getAvatarUrl(state.user.avatarUrl);
      return `
        ${baseMenu}
          <div class="flex items-center space-x-3 py-3 border-t border-gray-600 mt-2 pt-4">
            <img
              src="${avatarUrl}"
              alt="${state.user.username}"
              class="w-10 h-10 rounded-full object-cover border-2 border-gray-600"
              onerror="this.src='/default.jpg'"
            />
            <div class="flex-1">
              <div class="font-medium text-white">${state.user.username}</div>
              <div class="flex items-center text-sm text-gray-400">
                <div class="w-2 h-2 ${state.user.isOnline ? 'bg-green-500' : 'bg-gray-500'} rounded-full mr-2"></div>
                ${state.user.isOnline ? 'Online' : 'Offline'}
              </div>
            </div>
          </div>
          <a href="/profile" class="block py-2 topbar-link">Profile</a>
          <button id="mobile-signout" class="block py-2 topbar-link text-red-400 hover:text-red-300 w-full text-left">
            Logout
          </button>
        ${closing}
      `;
    }

    return `
      ${baseMenu}
        <a href="/login" class="block py-2 topbar-link">Login</a>
      ${closing}
    `;
  }

  private hookListeners(): void {
    const toggleButton = document.getElementById('nav-toggle-button');
    const mobileMenu = document.getElementById('nav-mobile-panel');

    toggleButton?.addEventListener('click', () => {
      mobileMenu?.classList.toggle('hidden');
    });

    const signOutButton = document.getElementById('desktop-signout');
    const mobileSignOutButton = document.getElementById('mobile-signout');

    signOutButton?.addEventListener('click', event => {
      event.preventDefault();
      this.triggerLogout();
    });

    mobileSignOutButton?.addEventListener('click', event => {
      event.preventDefault();
      this.triggerLogout();
    });

    document.querySelectorAll('.topbar-link').forEach(link => {
      link.addEventListener('click', event => {
        const target = event.target as HTMLElement;
        if (target.id === 'desktop-signout' || target.id === 'mobile-signout') {
          return;
        }
        event.preventDefault();
        const destination = (target as HTMLAnchorElement).getAttribute('href');
        if (destination) {
          window.dispatchEvent(new CustomEvent('navigate', { detail: destination }));
        }
      });
    });
  }

  private triggerLogout(): void {
    DevConsole.print('🚪 Logging out from navigation bar');
    userAuthenticationService.logout();
  }
}
