// Public surface for the tournament feature
export { TournamentBracket } from './components/CompetitionBracket';
export { TournamentMatch } from './components/CompetitionMatch';

// Views
export { TournamentCreatePage } from './pages/CompetitionCreatePage';
export { TournamentPage } from './pages/CompetitionPage';

// Services
export { competitionService } from './services/competitionService';

// Types remain re-exported for convenience
export * from './types/competitionTypes';
