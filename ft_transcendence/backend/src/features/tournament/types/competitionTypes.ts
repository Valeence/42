export interface TournamentParticipant {
  name: string;
  isUser: boolean;
  userId?: number;
}

export interface TournamentMatch {
  id: number;
  round: number;
  position: number;
  player1: TournamentParticipant | null;
  player2: TournamentParticipant | null;
  winner: TournamentParticipant | null;
  status: "pending" | "in_progress" | "completed";
  matchId?: number;
}

export interface TournamentBracket {
  quarterFinals: TournamentMatch[];
  semiFinals: TournamentMatch[];
  final: TournamentMatch;
}

export interface TournamentResponse {
  success: boolean;
  message: string;
  tournament: {
    id: number;
    status: "waiting" | "in_progress" | "completed";
    player_list: TournamentParticipant[];
    bracket: TournamentBracket;
    gameSettings: GameSettings;
    nextMatch?: {
      id: number;
      matchNumber: number;
      round: string;
      player1: string;
      player2: string;
    } | null;
    winner?: string;
  };
}

export interface GameSettings {
  ballSpeed: string;
  winScore: number;
  powerUps: boolean;
}
