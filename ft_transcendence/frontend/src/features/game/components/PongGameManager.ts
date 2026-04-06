import { Pong3D } from './Pong3D/Pong3DEngine';
import type { GameManagerOptions } from '@/types/index.js';
import { DevConsole } from '@/utils/devConsole.js';

export class GameManager
{
  private game: Pong3D | null = null;
  private config: GameManagerOptions;
  private startTime: number = 0;

  constructor(config: GameManagerOptions)
  {
    this.config = config;
    DevConsole.print(`🎮 GameManager created for mode: ${config.mode}`);
  }

  public async startGame(): Promise<void>
  {
    DevConsole.print(`🚀 Starting ${this.config.mode} game...`);

    try
    {
      this.game = new Pong3D(
        this.config.canvasId,
        this.config.settings,
        this.config.mode === 'remote',
        this.config.mode
      );

      this.setupGameCallbacks();

      if (this.config.onGameStart)
      {
        DevConsole.print('🟢 onGameStart callback detected, calling it...');
        this.config.onGameStart();
      }

      this.startTime = Date.now();

      DevConsole.print('🎯 Calling game.startGame()');
      this.game.startGame();
    }
    catch (error)
    {
      DevConsole.reportError(`❌ Failed to start ${this.config.mode} game:`, error);
      throw error;
    }
  }

  public pauseGame(): void
  {
    if (!this.game)
    {
      DevConsole.reportError('⚠️ pauseGame called but game is null');
      return;
    }
    DevConsole.print('⏸️ Toggling pause');
    this.game.togglePause();
  }

  public getGameStatus(): string
  {
    if (!this.game)
    {
      DevConsole.reportError('⚠️ getGameStatus called but game is null');
      return 'unknown';
    }
    return this.game.getGameStatus();
  }

  public destroy(): void
  {
    if (!this.game)
    {
      DevConsole.reportError('⚠️ destroy called but game is already null');
      return;
    }
    DevConsole.print('🗑️ Destroying game instance');
    this.game.destroy();
    this.game = null;
  }

  public handleResize(): void
  {
    if (!this.game) return;
    this.game.handleResize();
  }


  private setupGameCallbacks(): void
  {
    if (!this.game) return;

    this.game.onGameEnd = (winner: string, scores: any, duration: number) =>
    {
      DevConsole.print(`🏁 ${this.config.mode} game ended`);
      DevConsole.print({ winner, scores, duration });

      if (this.config.onGameEnd)
      {
        DevConsole.print('🟢 onGameEnd callback detected, calling it...');
        this.config.onGameEnd(winner, scores, duration);
      }
    };
  }
}
