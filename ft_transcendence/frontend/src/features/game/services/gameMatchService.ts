import { userAuthenticationService } from "@/features/auth/services/userAuthenticationService";  
import { ApiConfig } from "../../../config/api";
import { DevConsole } from '@/utils/devConsole.js'; 

export class MatchService {
  private baseURL = ApiConfig.API_URL;

  async sendLocalMatchData(
    player1: string, 
    player2: string, 
    score1: number,
    score2: number,
    duration: number,
  ): Promise<void> {
    try {
      if (!userAuthenticationService.isAuthenticated()) {
        DevConsole.print('🔒 User not authenticated, skipping match data send');
        return;
      }
      await this.createAndFinishLocalMatch(player1, player2, score1, score2, duration);
      DevConsole.print('✅ Local match data sent successfully');
    } catch (error) {
      DevConsole.reportError('❌ Failed to send local match data:', error);
    }
  }

  async sendRemoteMatchData(
    opponentUserId: number,
    score1: number,
    score2: number,
    duration: number,
  ): Promise<void> {
    try {
      if (!userAuthenticationService.isAuthenticated()) {
        DevConsole.print('🔒 User not authenticated, cannot send remote match data');
        return;
      }

      const response = await fetch(`${this.baseURL}/match/remote`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        credentials: 'include',
        body: JSON.stringify({ opponentUserId, score1, score2, duration })
      });

      if (!response.ok) throw new Error('Failed to create remote match');

      DevConsole.print('✅ Remote match data sent successfully');
    } catch (error) {
      DevConsole.reportError('❌ Failed to send remote match data:', error);
    }
  }

  async createAndFinishLocalMatch(
    player1: string, 
    player2: string, 
    score1: number,
    score2: number,
    duration: number,
  ): Promise<any> {
    try {
      const response = await fetch(`${this.baseURL}/match/local`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        credentials: 'include',
        body: JSON.stringify({ player1, player2, score1, score2, duration })
      });

      if (!response.ok) throw new Error('Failed to create local match');

      return await response.json();
    } catch (error) {
      DevConsole.reportError('Failed to create local match:', error);
      throw error;
    }
  }
}

export const matchService = new MatchService();
