import type { AccountProfile, CompletedMatchRecord } from '@/types/index.js';
import { TwoFactorRequiredProblem } from '@/types/index.js';
import { userProfileService } from '@/features/profile/services/userProfileService.js';
import { DevConsole } from '@/utils/devConsole.js';

export class AuthService {
  private static instance: AuthService;
  private currentUser: AccountProfile | null = null;
  private authChecked = false;
  private baseURL = process.env.NODE_ENV === 'production'
    ? '/api'
    : `http://${location.hostname}:8000/api`;

  private constructor() {
    DevConsole.print('AuthService baseURL:', this.baseURL);
  }

  public static getInstance(): AuthService {
    if (!AuthService.instance) {
      AuthService.instance = new AuthService();
    }
    return AuthService.instance;
  }

  public getCurrentUser(): AccountProfile | null {
    return this.currentUser;
  }

  public isAuthenticated(): boolean {
    return this.currentUser !== null;
  }

  public updateCurrentUser(user: AccountProfile): void {
    this.currentUser = user;
    DevConsole.print('🔄 Current user updated in authService:', user);
  }

  public initiateGoogleLogin(): void {
    DevConsole.print('Initiating Google OAuth...');
    window.location.href = `${this.baseURL}/auth/oauth/google`;
  }

  public async login(username: string, password: string): Promise<{ user: AccountProfile; token: string }> {
    const response = await fetch(`${this.baseURL}/auth/login`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      credentials: 'include',
      body: JSON.stringify({ username, password })
    });

    const data = await response.json();

    if (response.status === 202 && data.requiresTwoFactor) {
      throw new TwoFactorRequiredProblem(data.message, data.userId);
    }

    if (!response.ok) {
      throw new Error(data.error || 'Login failed');
    }

    if (data.user?.avatarUrl) {
      data.user.avatarUrl = userProfileService.getAvatarUrl(data.user.avatarUrl);
    }

    this.currentUser = data.user;
    window.dispatchEvent(new CustomEvent('authStateChanged'));
    return data;
  }

  public async loginWith2FA(userId: number, code: string): Promise<{ user: AccountProfile; token: string }> {
    const response = await fetch(`${this.baseURL}/auth/loginWith2FA`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      credentials: 'include',
      body: JSON.stringify({ userId, code })
    });

    if (!response.ok) {
      const error = await response.json();
      throw new Error(error.error || '2FA login failed');
    }

    const data = await response.json();
    if (data.user?.avatarUrl) {
      data.user.avatarUrl = userProfileService.getAvatarUrl(data.user.avatarUrl);
    }

    this.currentUser = data.user;
    window.dispatchEvent(new CustomEvent('authStateChanged'));
    return data;
  }

  public async register(username: string, email: string, password: string): Promise<{ user: AccountProfile; token: string }> {
    const response = await fetch(`${this.baseURL}/auth/register`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      credentials: 'include',
      body: JSON.stringify({ username, email, password })
    });

    if (!response.ok) {
      const err = await response.json();
      throw new Error(err.message || 'Registration failed');
    }

    const data = await response.json();
    this.currentUser = data.user;
    window.dispatchEvent(new CustomEvent('authStateChanged'));
    return data;
  }

  public async logout(): Promise<void> {
    try {
      await fetch(`${this.baseURL}/auth/logout`, {
        method: 'POST',
        credentials: 'include'
      });
    } catch (err) {
      DevConsole.reportError('Logout API call failed:', err);
    }

    this.currentUser = null;
    localStorage.removeItem('authToken');
    window.dispatchEvent(new CustomEvent('authStateChanged'));
    window.dispatchEvent(new CustomEvent('navigate', { detail: '/login' }));
  }

  public async checkAuthStatus(): Promise<boolean> {
    if (this.authChecked) return this.currentUser !== null;

    try {
      const response = await fetch(`${this.baseURL}/user/me`, {
        method: 'GET',
        credentials: 'include'
      });

      if (response.ok) {
        const userData = await response.json();
        if (userData.avatarUrl) {
          userData.avatarUrl = userProfileService.getAvatarUrl(userData.avatarUrl);
        }
        this.currentUser = userData;
        this.authChecked = true;
        window.dispatchEvent(new CustomEvent('authStateChanged'));
        return true;
      }

      if (response.status === 401) {
        DevConsole.print('🔐 User not authenticated');
      } else {
        DevConsole.reportError('⚠️ Auth check failed with status:', response.status);
      }

      this.currentUser = null;
      this.authChecked = true;
      return false;
    } catch (err) {
      if (err instanceof TypeError && err.message.includes('fetch')) {
        DevConsole.reportError('🌐 Network error during auth check (server might be down)');
      } else {
        DevConsole.reportError('⚠️ Auth check error:', err);
      }
      this.currentUser = null;
      this.authChecked = true;
      return false;
    }
  }

  public async getUserProfile(userId?: string | null): Promise<AccountProfile | null> {
    try {
      const endpoint = userId ? `/auth/profile/${userId}` : '/auth/me';
      const response = await fetch(`${this.baseURL}${endpoint}`, {
        method: 'GET',
        credentials: 'include'
      });

      return response.ok ? await response.json() : null;
    } catch (err) {
      DevConsole.reportError('Failed to fetch user profile:', err);
      return null;
    }
  }

  public async getMatchHistory(userId?: string | null): Promise<CompletedMatchRecord[]> {
    try {
      const endpoint = userId ? `/users/${userId}/matches` : '/auth/me/matches';
      const response = await fetch(`${this.baseURL}${endpoint}`, { credentials: 'include' });
      return response.ok ? await response.json() : [];
    } catch (err) {
      DevConsole.reportError('Failed to fetch match history:', err);
      return [];
    }
  }

  public async loadCurrentUser(): Promise<AccountProfile | null> {
    if (!this.isAuthenticated()) return null;

    try {
      const response = await fetch(`${this.baseURL}/user/me`, { credentials: 'include' });
      if (!response.ok) return null;

      const userData = await response.json();
      this.currentUser = userData;
      return userData;
    } catch (err) {
      DevConsole.reportError('Failed to load current user:', err);
      return null;
    }
  }
}

export const userAuthenticationService = AuthService.getInstance();
