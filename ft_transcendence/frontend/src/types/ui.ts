export interface GameModeHandlers {
  onLocalGame: () => void;
  onRemoteGame: () => void;
  onTournament: () => void;
  onLogin?: () => void;
}
