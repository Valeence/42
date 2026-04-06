import type { GameSettings } from '@/features/game/types/pongGameTypes.js';

export type TournamentStatus = 'waiting' | 'in_progress' | 'completed';
export type MatchStatus = 'pending' | 'in_progress' | 'completed';

export interface Tournament {
  id: string;
  name: string;
  participants: string[];
  bracket: TournamentMatch[];
  status: TournamentStatus;
  winnerId?: string;
  createdAt: string;
  settings: GameSettings;
  currentRound: number;
  totalRounds: number;
}

export interface TournamentMatch {
  id: string;
  round: number;
  player1: string;
  player2: string;
  winner?: string;
  score?: {
    player1: number;
    player2: number;
  };
  status: MatchStatus;
  scheduledAt?: string;
  completedAt?: string;
}

export interface TournamentBracket {
  rounds: TournamentRound[];
  finalMatch?: TournamentMatch;
}

export interface TournamentRound {
  roundNumber: number;
  matches: TournamentMatch[];
}
