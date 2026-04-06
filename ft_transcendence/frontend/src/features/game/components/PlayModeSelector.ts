export class GameModeSelector 
{
  constructor(private gameModeCallbacks: {
    onLocalMode: () => void;
    onRemoteMode: () => void;
    onTournamentMode: () => void;
  }) {}

  render(): string 
  {
    // Build buttons individually to keep student-style explicit code
    const localButton = `
      <button id="mode-local" class="card hover:scale-105 transition-all duration-300 text-left">
        <div class="text-center p-4">
          <div class="text-4xl mb-3">🎮</div>
          <h4 class="font-bold text-white">Local Game</h4>
        </div>
      </button>
    `;

    const remoteButton = `
      <button id="mode-remote" class="card hover:scale-105 transition-all duration-300 text-left">
        <div class="text-center p-4">
          <div class="text-4xl mb-3">🌐</div>
          <h4 class="font-bold text-white">Online Game</h4>
        </div>
      </button>
    `;

    const tournamentButton = `
      <button id="mode-tournament" class="card hover:scale-105 transition-all duration-300 text-left">
        <div class="text-center p-4">
          <div class="text-4xl mb-3">🏆</div>
          <h4 class="font-bold text-white">Tournament</h4>
        </div>
      </button>
    `;

    return `
      <div class="card mb-6">
        <h3 class="text-xl mb-6 text-white">Choose Game Mode</h3>
        <div class="grid grid-cols-1 md:grid-cols-3 gap-4">
          ${remoteButton}
          ${tournamentButton}
          ${localButton}
        </div>
      </div>
    `;
  }

  bindEvents(): void 
  {
    const localBtn = document.getElementById('mode-local');
    const remoteBtn = document.getElementById('mode-remote');
    const tournamentBtn = document.getElementById('mode-tournament');

    if (remoteBtn) remoteBtn.addEventListener('click', this.gameModeCallbacks.onRemoteMode);
    if (tournamentBtn) tournamentBtn.addEventListener('click', this.gameModeCallbacks.onTournamentMode);
    if (localBtn) localBtn.addEventListener('click', this.gameModeCallbacks.onLocalMode);
  }
}
