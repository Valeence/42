export interface RegisterData {
  username: string;
  email: string;
  password: string;
}

export interface LoginData {
  username: string;
  password: string;
}

export interface UserStats {
  wins: number;
  losses: number;
  totalGames: number;
  winRate: number;
  rank: number;
  highestScore: number;
  currentStreak: number;
  longestStreak: number;
  gamesPlayed: number;
}

export interface User {
  id: number;
  username: string;
  email: string;
  avatarUrl?: string | null;
  isOnline?: boolean;
  twoFactorEnabled?: boolean;
  createdAt?: string;
  lastLogin?: string;
  googleId?: string;
  stats?: UserStats;
}

export interface TwoFactorResponse {
  success: boolean;
  message: string;
}

export interface MatchHistory {
  id: string;
  opponent: string;
  opponentAvatar?: string | null;
  result: 'win' | 'loss';
  score: {
    player: number;
    opponent: number;
  };
  date: string;
  duration?: number;
  gameMode?: 'local' | 'remote' | 'tournament';
}

export class TwoFactorRequiredError extends Error {
  public userId?: number;

  constructor(message: string, userId?: number) {
    super(message);
    this.name = 'TwoFactorRequiredError';
    this.userId = userId;
    // Maintain proper prototype chain
    Object.setPrototypeOf(this, TwoFactorRequiredError.prototype);
  }
}

declare global {
  interface AuthPageBase {
    errorMessage: any;
    oauthButtons: any;
    languageChangeListener: (() => void) | null;
  }
}
