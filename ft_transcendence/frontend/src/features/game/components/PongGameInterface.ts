export class GameInterface
{
  constructor(
    private gameMode: 'local' | 'remote' | 'tournament',
    private gameCallbacks: {
      onPause: () => void;
      onQuit: () => void;
    }
  ) {}

  bindEvents(): void
  {
    const pauseBtn = document.getElementById('pause-game');
    const quitBtn = document.getElementById('quit-game');

    if (pauseBtn) {
      pauseBtn.addEventListener('click', () => {
        console.log('Pause button clicked');
        this.gameCallbacks.onPause();
      });
    }

    if (quitBtn) {
      quitBtn.addEventListener('click', () => {
        if (confirm('Are you sure you want to quit the game?')) {
          this.gameCallbacks.onQuit();
        }
      });
    }
  }

  render(): string
  {
    const header = `
      <div class="bg-gradient-to-r from-purple-900/40 to-blue-900/40 backdrop-blur-sm rounded-t-lg p-3 md:p-4 flex justify-between items-center border-b border-purple-500/30">
        <h2 class="text-lg md:text-xl font-bold">${this.getGameModeTitle()}</h2>
        <div class="flex gap-2 md:gap-3">
          ${this.gameMode !== 'remote' ? this.renderGameButtons() : ''}
        </div>
      </div>
    `;

    const gameArea = `
      <div class="relative bg-gradient-to-br from-purple-900/40 to-blue-900/40 rounded-b-lg overflow-hidden border border-purple-500/30 border-t-0 shadow-xl">
        <div class="relative w-full aspect-video bg-gradient-to-br from-gray-900 to-gray-800">
          <canvas id="game-canvas" 
                  class="absolute top-0 left-0 w-full h-full"
                  style="background: linear-gradient(45deg, #1f2937, #374151); border-radius: 0 0 0.5rem 0.5rem;">
            Canvas not supported
          </canvas>
          ${this.renderGameOverlay()}
        </div>
        ${this.renderGameControls()}
      </div>
    `;

    return header + gameArea;
  }

  private renderGameButtons(): string
  {
    const pauseBtn = `<button id="pause-game" class="bg-yellow-600 hover:bg-yellow-700 px-3 py-2 md:px-4 md:py-2 rounded-lg text-xs md:text-sm transition-colors">⏸️ <span class="hidden sm:inline">Pause</span></button>`;
    const quitBtn = `<button id="quit-game" class="bg-red-600 hover:bg-red-700 px-3 py-2 md:px-4 md:py-2 rounded-lg text-xs md:text-sm transition-colors"><span class="hidden sm:inline">Leave Game</span><span class="sm:hidden">✕</span></button>`;
    return pauseBtn + quitBtn;
  }

  updatePauseButton(isPaused: boolean): void
  {
    const pauseBtn = document.getElementById('pause-game');
    if (!pauseBtn) return;

    if (isPaused) {
      pauseBtn.innerHTML = `▶️ Resume`;
      pauseBtn.className = 'bg-green-600 hover:bg-green-700 px-4 py-2 rounded-lg text-sm transition-colors';
    } else {
      pauseBtn.innerHTML = `⏸️ Pause`;
      pauseBtn.className = 'bg-yellow-600 hover:bg-yellow-700 px-4 py-2 rounded-lg text-sm transition-colors';
    }
  }

  updateGameStatus(status: string, scores: string, timer: string): void
  {
    const elements = [
      { id: 'game-status', value: status },
      { id: 'game-scores', value: scores },
      { id: 'game-timer-display', value: timer },
    ];

    elements.forEach(el => {
      const dom = document.getElementById(el.id);
      if (dom) dom.textContent = el.value;
    });
  }

  updatePlayerNames(player1Name: string, player2Name: string): void
  {
    const p1 = document.getElementById('player1-name');
    const p2 = document.getElementById('player2-name');
    if (p1) p1.textContent = player1Name;
    if (p2) p2.textContent = player2Name;
  }

  updateScores(player1Score: number, player2Score: number): void
  {
    const p1 = document.getElementById('player1-score');
    const p2 = document.getElementById('player2-score');
    if (p1) p1.textContent = player1Score.toString();
    if (p2) p2.textContent = player2Score.toString();
  }

  updateTimer(timeString: string): void
  {
    const timerEl = document.getElementById('game-timer');
    if (timerEl) {
      const divs = timerEl.getElementsByTagName('div');
      if (divs.length > 1) divs[1].textContent = timeString;
    }
  }

  private renderGameOverlay(): string
  {
    return `
      <div id="game-overlay" class="absolute inset-0 pointer-events-none">
        <div class="absolute top-2 left-2 right-2 flex justify-between items-start">
          <div id="player1-info" class="text-white">
            <div id="player1-name">Player 1</div>
            <div id="player1-score">0</div>
          </div>
          <div id="game-timer" class="text-white text-center">
            <div>Time</div>
            <div>00:00</div>
          </div>
          <div id="player2-info" class="text-white text-right">
            <div id="player2-name">Player 2</div>
            <div id="player2-score">0</div>
          </div>
        </div>
      </div>
    `;
  }

  private renderGameControls(): string
  {
    return `
      <div class="p-3 grid grid-cols-1 lg:grid-cols-2 gap-3">
        <div id="game-status" class="text-green-400 text-sm hidden md:block">Waiting...</div>
        <div id="game-scores" class="text-lg hidden md:block">0 - 0</div>
        <div id="game-timer-display" class="text-sm hidden md:block">00:00</div>
      </div>
    `;
  }


  private getGameModeTitle(): string
  {
    if (this.gameMode === 'local') return 'Local';
    if (this.gameMode === 'remote') return 'Online';
    if (this.gameMode === 'tournament') return 'Tournament';
    return 'Mode Selection';
  }
}
