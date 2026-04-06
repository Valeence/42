export interface ProfileComponents {
  stats: any;  
  header: any; 
  friends?: any; 
  history?: any; 
}

export interface MatchHistory {
  opponent: string;
  id: string;
  result: 'win' | 'loss';
  opponentAvatar?: string | null;
  score: {
    opponent: number;
    player: number;
  };
  gameMode?: 'local' | 'remote' | 'tournament';
  date: string;
  duration?: number;
}