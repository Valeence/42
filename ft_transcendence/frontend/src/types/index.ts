export type {
  User as AccountProfile,
  UserStats as AccountPerformanceStats,
  LoginData as AuthLoginPayload,
  RegisterData as AuthRegistrationPayload,
  TwoFactorResponse as TwoFactorResult,
  MatchHistory as CompletedMatchRecord
} from '../features/auth/types/userAuthTypes.js';

export { TwoFactorRequiredError as TwoFactorRequiredProblem } from '../features/auth/types/userAuthTypes.js';

export type {
  GameSettings as ArenaSettings,
  GameState as PongSessionState,
  GameManagerConfig as GameManagerOptions,
  GameObjects as GameEntityMap,
  ObjectPositions as EntityPositions,
  GameEndStats as MatchCompletionSummary,
  GameEndCallbacks as MatchLifecycleHooks
} from '../features/game/types/pongGameTypes.js';

export type {
  Friend as FriendProfile,
  FriendRequest as FriendRequestData,
  FriendshipStatus as FriendshipState
} from '../features/profile/types/socialConnectionsTypes.js';

export type {
  ProfileComponents as ProfileRenderSections
} from '../features/profile/types/userProfileTypes.js';

export type { GameModeHandlers } from './ui.js';

export type {
  Tournament as TournamentOverview,
  TournamentMatch as TournamentMatchInfo,
  TournamentBracket as BracketLayout,
  TournamentRound as BracketRoundInfo
} from '../features/tournament/types/competitionTypes.js';

export type { GlobalStats as ServerSnapshot } from '../features/home/types/serverStatsTypes.js';

export type { AppRouteEntry } from './router.js';

export type {
  WebRTCConfig as RealtimeConfig,
  GameMessage as SessionMessage,
  ConnectionState as ConnectionStatus,
  RemoteGameConfig as RemoteSessionConfig
} from '../features/game/types/multiplayerNetworkTypes.js';

export type {
  ServicePayload,
  PaginatedPayload,
  ServiceErrorInfo
} from './api.js';
