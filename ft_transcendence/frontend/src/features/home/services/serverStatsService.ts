import type { ServerSnapshot } from '@/types/index.js';
import { DevConsole } from '@/utils/devConsole.js';

export class GlobalStatsService {
  private baseURL: string;

  constructor() {
    this.baseURL = process.env.NODE_ENV === 'production'
      ? '/api'
      : `http://${location.hostname}:8000/api`;
  }

  async getGlobalStats(): Promise<ServerSnapshot> {
    try {
      const url = `${this.baseURL}/home/stats`;
      DevConsole.print('Fetching global stats from:', url);

      const response = await fetch(url, { method: 'GET', credentials: 'include' });
      DevConsole.print('Global stats response status:', response.status);

      if (!response.ok) {
        await this.logErrorResponse(response);
        return this.defaultStats();
      }

      const stats: ServerSnapshot = await response.json();
      DevConsole.print('Global stats received:', stats);
      return stats;

    } catch (error) {
      DevConsole.reportError('Failed to fetch global stats:', error);
      return this.defaultStats();
    }
  }

  private async logErrorResponse(response: Response) {
    DevConsole.reportError('Global stats API error:', response.status, response.statusText);
    const errorText = await response.text();
    DevConsole.reportError('Error response:', errorText);
  }

  private defaultStats(): ServerSnapshot {
    return {
      totalPlayers: 0,
      totalGames: 0,
      onlinePlayers: 0
    };
  }
}

export const serverStatsService = new GlobalStatsService();
