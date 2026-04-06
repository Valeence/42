import type { AccountProfile } from '@/types/index.js';
import { DevConsole } from '@/utils/devConsole.js';

export class UserService {
  private static singleton: UserService;
  private apiRoot: string;

  private constructor() {
    this.apiRoot = process.env.NODE_ENV === 'production'
      ? '/api'
      : `http://${location.hostname}:8000/api`;
  }

  public static getInstance(): UserService {
    if (!UserService.singleton) {
      UserService.singleton = new UserService();
    }
    return UserService.singleton;
  }

  private formatAvatar(avatarPath?: string | null): string {
    if (!avatarPath) return '/default.jpg';
    if (/^https?:\/\//.test(avatarPath)) return avatarPath;
    const base = process.env.NODE_ENV === 'production' ? '' : `${location.protocol}//${location.hostname}:8000`;
    return `${base}${avatarPath}`;
  }

  private async request<T>(url: string, options: RequestInit = {}): Promise<T | null> {
    try {
      const res = await fetch(url, { credentials: 'include', ...options });
      if (!res.ok) return null;
      return (await res.json()) as T;
    } catch (err) {
      DevConsole.reportError('Request failed:', err);
      return null;
    }
  }

  public async getUserProfile(userId?: string | null): Promise<AccountProfile | null> {
    DevConsole.print('Fetching profile for userId:', userId);
    const urlPath = userId ? `/user/profile/${userId}` : '/user/me';
    const user = await this.request<AccountProfile>(`${this.apiRoot}${urlPath}`);
    if (!user) return null;
    user.avatarUrl = this.formatAvatar(user.avatarUrl);
    return user;
  }

  public async getMatchHistory(userId?: string | null): Promise<any[]> {
    const urlPath = userId ? `/user/${userId}/matches` : '/user/me/matches';
    const matches = await this.request<any[]>(`${this.apiRoot}${urlPath}`);
    return matches ?? [];
  }

  public async updateProfile(data: { username: string; email: string }, avatarFile?: File): Promise<AccountProfile> {
    const form = new FormData();
    form.append('username', data.username);
    form.append('email', data.email);
    if (avatarFile) form.append('avatar', avatarFile);

    const res = await fetch(`${this.apiRoot}/user/updateProfile`, {
      method: 'PUT',
      credentials: 'include',
      body: form
    });

    if (!res.ok) {
      const err = await res.json();
      throw new Error(err.error || 'Failed to update profile');
    }

    const payload = await res.json();
    return payload.user;
  }

  public async changePassword(currentPassword: string, newPassword: string): Promise<void> {
    const res = await fetch(`${this.apiRoot}/user/change-password`, {
      method: 'PUT',
      headers: { 'Content-Type': 'application/json' },
      credentials: 'include',
      body: JSON.stringify({ currentPassword, newPassword })
    });

    if (!res.ok) {
      const err = await res.json();
      throw new Error(err.message || 'Failed to change password');
    }
  }

  public getAvatarUrl(avatarPath?: string | null): string {
    return this.formatAvatar(avatarPath);
  }
}

export const userProfileService = UserService.getInstance();
