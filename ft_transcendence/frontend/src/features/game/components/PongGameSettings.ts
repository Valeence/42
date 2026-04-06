import { userAuthenticationService } from '@/features/auth/services/userAuthenticationService.js';
import type { ArenaSettings as PongArenaSettings } from '@/types/index.js';
import { DevConsole } from '@/utils/devConsole.js';

export class GameSettingsUI
{
  constructor(
    private mode: 'local' | 'remote' | 'tournament',
    private gameCallbacks: {
      onStartLocal: () => void;
      onStartRemote: () => void;
      onCreateTournament: () => void;
      onBackToModes: () => void;
    }
  ) 
  {
    DevConsole.print(`🛠️ GameSettingsUI initialized for mode: ${this.mode}`);
  }

  render(): string 
  {
    DevConsole.print(`🎨 Rendering settings UI for mode: ${this.mode}`);
    if (this.mode === 'local') return this.renderLocalSettings();
    if (this.mode === 'remote') return this.renderRemoteSettings();
    if (this.mode === 'tournament') return this.renderTournamentSettings();
    return '';
  }

  bindEvents(): void 
  {
    DevConsole.print('🖱️ Binding settings UI buttons...');
    document.getElementById('start-local-game')?.addEventListener('click', this.gameCallbacks.onStartLocal);
    document.getElementById('start-remote-game')?.addEventListener('click', this.gameCallbacks.onStartRemote);
    document.getElementById('create-tournament')?.addEventListener('click', this.gameCallbacks.onCreateTournament);

    document.querySelectorAll('#back-to-modes').forEach(button => {
      button.addEventListener('click', this.gameCallbacks.onBackToModes);
    });

    document.getElementById('back-to-menu-from-forfeit')?.addEventListener('click', () => {
      DevConsole.print('🧹 Cleaning sessionStorage before returning to menu...');
      sessionStorage.removeItem('remote_game_active');
      sessionStorage.removeItem('remote_game_data');
      window.dispatchEvent(new CustomEvent('navigate', { detail: '/' }));
    });
  }

  getGameSettings(): PongArenaSettings 
  {
    DevConsole.print('🔍 Collecting game settings from UI...');
    const isAuth = userAuthenticationService.isAuthenticated();
    const currentUser = userAuthenticationService.getCurrentUser();

    let player1Name: string = '';
    let player2Name: string = '';

    if (this.mode === 'remote' || this.mode === 'tournament') 
    {
      player1Name = currentUser?.username || 'Player';
      player2Name = 'Opponent';
    } 
    else 
    {
      player1Name = isAuth && currentUser
        ? currentUser.username
        : (document.getElementById('player1-name-input') as HTMLInputElement)?.value || 'Player 1';
      player2Name = (document.getElementById('player2-name-input') as HTMLInputElement)?.value || 'Player 2';
    }

    const prefix = this.mode === 'remote' ? 'remote-' : this.mode === 'tournament' ? 'tournament-' : '';
    const ballSpeedEl = document.getElementById(`${prefix}ball-speed`) as HTMLSelectElement;
    const winScoreEl = document.getElementById(`${prefix}win-score`) as HTMLSelectElement;

    DevConsole.print('🎯 Final settings:', {
      player1Name,
      player2Name,
      ballSpeed: ballSpeedEl?.value || 'medium',
      winScore: winScoreEl?.value || '5',
    });

    return {
      player1Name,
      player2Name,
      ballSpeed: ballSpeedEl?.value as 'slow' | 'medium' | 'fast' || 'medium',
      winScore: parseInt(winScoreEl?.value || '5'),
      enableEffects: false,
    };
  }


  private renderLocalSettings(): string 
  {
    const isAuth = userAuthenticationService.isAuthenticated();
    const currentUser = userAuthenticationService.getCurrentUser();
    return `
      <div class="bg-gradient-to-br from-purple-900/40 to-blue-900/40 p-6 rounded-lg border border-purple-500/30 shadow-xl">
        <h3 class="text-xl mb-4">Local Game Settings</h3>
        <div class="grid grid-cols-1 md:grid-cols-2 gap-4 mb-6">
          <div>
            <label class="block mb-2">Player 1:</label>
            ${isAuth && currentUser ? `
              <input type="text" id="player1-name-input" value="${currentUser.username}" readonly
                     class="bg-gray-800/60 rounded px-3 py-2 w-full cursor-not-allowed opacity-75 border border-blue-500/50">
              <div class="text-xs text-blue-400 mt-1">✓ Authenticated</div>
            ` : `
              <input type="text" id="player1-name-input" value="Player 1"
                     class="bg-gray-800/60 rounded px-3 py-2 w-full focus:ring-2 focus:ring-blue-500 border border-purple-500/30">
            `}
          </div>
          <div>
            <label class="block mb-2">Player 2:</label>
            <input type="text" id="player2-name-input" value="Player 2"
                   class="bg-gray-800/60 rounded px-3 py-2 w-full focus:ring-2 focus:ring-blue-500 border border-purple-500/30">
          </div>
          <div>
            <label class="block mb-2">Ball Speed:</label>
            <select id="ball-speed" class="bg-gray-800/60 rounded px-3 py-2 w-full border border-purple-500/30">
              <option value="slow">Slow</option>
              <option value="medium" selected>Medium</option>
              <option value="fast">Fast</option>
            </select>
          </div>
          <div>
            <label class="block mb-2">Win Score:</label>
            <select id="win-score" class="bg-gray-800/60 rounded px-3 py-2 w-full border border-purple-500/30">
              <option value="3">3 Points</option>
              <option value="5" selected>5 Points</option>
              <option value="10">10 Points</option>
            </select>
          </div>
        </div>
        <div class="flex flex-col sm:flex-row gap-3">
          <button id="start-local-game" class="bg-blue-600 hover:bg-blue-700 px-6 py-3 rounded-lg flex-1">Start Game</button>
          <button id="back-to-modes" class="bg-gray-600 hover:bg-gray-700 px-6 py-3 rounded-lg">Back to Modes</button>
        </div>
      </div>
    `;
  }

  private renderRemoteSettings(): string 
  {
    const isAuth = userAuthenticationService.isAuthenticated();
    const currentUser = userAuthenticationService.getCurrentUser();

    const wasInGame = sessionStorage.getItem('remote_game_active');
    DevConsole.print('🔍 Remote settings render check:', { isAuth, wasInGame });

    if (!isAuth) 
    {
      return `
        <div class="bg-purple-900/40 p-6 rounded-lg border border-purple-500/30 text-center">
          <h3 class="text-xl mb-4 text-yellow-400">Login Required</h3>
          <button onclick="window.dispatchEvent(new CustomEvent('navigate', { detail: '/login?redirect=/game?mode=remote' }))"
                  class="bg-blue-600 hover:bg-blue-700 px-6 py-3 rounded-lg mb-3">Login</button>
          <button id="back-to-modes" class="bg-gray-600 hover:bg-gray-700 px-6 py-3 rounded-lg">Back to Modes</button>
        </div>
      `;
    }

    if (wasInGame === 'true') 
    {
      return `
        <div class="bg-purple-900/40 p-6 rounded-lg border border-purple-500/30 text-center">
          <h3 class="text-xl mb-4 text-red-400">Game Interrupted</h3>
          <div class="text-6xl mb-4">😔</div>
          <p class="text-gray-300 mb-2">Your previous game was interrupted</p>
          <button id="back-to-menu-from-forfeit" class="bg-blue-600 hover:bg-blue-700 px-6 py-3 rounded-lg">Back to Menu</button>
        </div>
      `;
    }

    return `
      <div class="bg-purple-900/40 p-6 rounded-lg border border-purple-500/30">
        <h3 class="text-xl mb-4">Online Match Settings</h3>
        <p class="text-blue-400 mb-4">Player: ${currentUser?.username}</p>
        <div class="grid grid-cols-1 md:grid-cols-2 gap-4 mb-6">
          <div>
            <label class="block mb-2">Ball Speed:</label>
            <select id="remote-ball-speed" class="bg-gray-800/60 rounded px-3 py-2 w-full border border-purple-500/30">
              <option value="slow">Slow</option>
              <option value="medium" selected>Medium</option>
              <option value="fast">Fast</option>
            </select>
          </div>
          <div>
            <label class="block mb-2">Win Score:</label>
            <select id="remote-win-score" class="bg-gray-800/60 rounded px-3 py-2 w-full border border-purple-500/30">
              <option value="3">3 Points</option>
              <option value="5" selected>5 Points</option>
              <option value="10">10 Points</option>
            </select>
          </div>
        </div>
        <div class="flex gap-3">
          <button id="start-remote-game" class="bg-green-600 hover:bg-green-700 px-6 py-3 rounded-lg flex-1">Find Match</button>
          <button id="back-to-modes" class="bg-gray-600 hover:bg-gray-700 px-6 py-3 rounded-lg">Back</button>
        </div>
      </div>
    `;
  }

  private renderTournamentSettings(): string 
  {
    const isAuth = userAuthenticationService.isAuthenticated();
    const currentUser = userAuthenticationService.getCurrentUser();

    return `
      <div class="bg-purple-900/40 p-6 rounded-lg border border-purple-500/30">
        <h3 class="text-xl mb-4">Tournament Settings</h3>
        ${isAuth && currentUser ? `<p>Participant: ${currentUser.username}</p>` : `<p>Guest user - login to participate</p>`}
        <div class="grid grid-cols-1 md:grid-cols-2 gap-4 mb-6">
          <div>
            <label class="block mb-2">Ball Speed:</label>
            <select id="tournament-ball-speed" class="bg-gray-800/60 rounded px-3 py-2 w-full border border-purple-500/30">
              <option value="slow">Slow</option>
              <option value="medium" selected>Medium</option>
              <option value="fast">Fast</option>
            </select>
          </div>
          <div>
            <label class="block mb-2">Win Score:</label>
            <select id="tournament-win-score" class="bg-gray-800/60 rounded px-3 py-2 w-full border border-purple-500/30">
              <option value="3">3 Points</option>
              <option value="5" selected>5 Points</option>
              <option value="10">10 Points</option>
            </select>
          </div>
        </div>
        <div class="flex gap-3">
          <button id="create-tournament" class="bg-purple-600 hover:bg-purple-700 px-6 py-3 rounded-lg flex-1">Create Tournament</button>
          <button id="back-to-modes" class="bg-gray-600 hover:bg-gray-700 px-6 py-3 rounded-lg">Back</button>
        </div>
      </div>
    `;
  }
}
