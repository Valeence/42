import type { AccountProfile, FriendProfile } from '@/types/index.js';
import { DevConsole } from '@/utils/devConsole.js';

export class FriendService {
  private static singleton: FriendService;
  private apiEndpoint: string;

  private constructor() {
    this.apiEndpoint = process.env.NODE_ENV === 'production'
      ? '/api'
      : `http://${location.hostname}:8000/api`;
  }

  public static getInstance(): FriendService {
    if (!FriendService.singleton) {
      FriendService.singleton = new FriendService();
    }
    return FriendService.singleton;
  }

  private async request<T>(url: string, options: RequestInit = {}): Promise<T | null> {
    try {
      const res = await fetch(url, { credentials: 'include', ...options });
      if (!res.ok) return null;
      return (await res.json()) as T;
    } catch (err) {
      DevConsole.reportError('API request failed:', err);
      return null;
    }
  }

  public async searchUsers(keyword: string): Promise<AccountProfile[]> {
    const users = await this.request<AccountProfile[]>(`${this.apiEndpoint}/user/users`);
    if (!users) return [];

    const normalized = keyword.toLowerCase();
    return users.filter(u => u.username.toLowerCase().includes(normalized)).slice(0, 10);
  }

  public async sendFriendRequest(friendId: number): Promise<boolean> {
    const res = await this.request<unknown>(`${this.apiEndpoint}/friends/add`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ userId: friendId })
    });
    return res !== null;
  }

  public async removeFriend(friendId: number): Promise<boolean> {
    const res = await this.request<unknown>(`${this.apiEndpoint}/friends/remove/${friendId}`, {
      method: 'DELETE'
    });
    return res !== null;
  }

  public async getFriends(): Promise<FriendProfile[]> {
    const friends = await this.request<FriendProfile[]>(`${this.apiEndpoint}/friends/list`);
    return friends ?? [];
  }
}

export const socialConnectionsService = FriendService.getInstance();
