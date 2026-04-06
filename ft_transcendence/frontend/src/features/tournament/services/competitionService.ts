import { DevConsole } from '@/utils/devConsole.js';
class TournamentService {
  private readonly baseURL: string;
  constructor() {
    this.baseURL = this.computeBaseUrl();
  }
  private computeBaseUrl(): string {
    return process.env.NODE_ENV === 'production'
      ? '/api'
      : `http://${window.location.hostname}:8000/api`;
  }
  private async fetchJson<T>(url: string, options: RequestInit): Promise<T> {
    const response = await fetch(url, options);
    if (!response.ok) {
      const errorText = await response.text();
      throw new Error(`HTTP error! status: ${response.status} - ${errorText || response.statusText}`);
    }
    return await response.json();
  }
  async createTournament(participants: string[], gameSettings?: {
    ballSpeed: string;
    winScore: number;
    powerUps?: boolean;
  }): Promise<any> {
    const payload = {
      participants,
      gameSettings
    };
    const data = await this.fetchJson<{ tournament: any }>(`${this.baseURL}/tournament/create`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      credentials: 'include',
      body: JSON.stringify(payload)
    });
    return data.tournament;
  }
  async getTournament(tournamentId: number): Promise<any> {
    return await this.fetchJson(`${this.baseURL}/tournament/${tournamentId}`, {
      method: 'GET',
      credentials: 'include'
    });
  }
  async finishMatch(
    tournamentId: number,
    matchNumber: number,
    player1: string,
    player2: string,
    score1: number,
    score2: number,
    duration: number
  ): Promise<any> {
    try {
      const normalizedScore1 = Number(score1);
      const normalizedScore2 = Number(score2);
      const requestData = {
        player1,
        player2,
        score1: normalizedScore1,
        score2: normalizedScore2,
        duration: Math.floor(Number(duration)),
        winner: normalizedScore1 > normalizedScore2 ? player1 : player2,
        matchNumber,
        tournamentId
      };
      const url = `${this.baseURL}/tournament/${tournamentId}/matches/${matchNumber}/finish`;
      DevConsole.print('🔍 Sending match finish data:', requestData);
      DevConsole.print('🔍 URL:', url);
      const response = await fetch(url, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        credentials: 'include',
        body: JSON.stringify(requestData)
      });
      DevConsole.print('🔍 Response status:', response.status);
      if (!response.ok) {
        const errorText = await response.text();
        DevConsole.reportError('❌ Backend error response:', errorText);
        throw new Error(`HTTP error! status: ${response.status} - ${errorText}`);
      }
      const result = await response.json();
      DevConsole.print('✅ Tournament match finished:', result);
      return result;
    } catch (error) {
      DevConsole.reportError('❌ Failed to finish tournament match:', error);
      throw error;
    }
  }
}
export const competitionService = new TournamentService();
