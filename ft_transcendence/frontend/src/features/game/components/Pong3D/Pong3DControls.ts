import type { PaddleInputs } from './Pong3DPhysics.js';

export class GameControls {
  private keys: Record<string, boolean> = {};

  private readonly gameKeys = new Set([
    'keyw', 'keys', 'keyi', 'keyk',
    'arrowup', 'arrowdown', 'arrowleft', 'arrowright',
    'space'
  ]);

  private keydownHandler = (e: KeyboardEvent) => {
    const key = e.code.toLowerCase();
    if (this.gameKeys.has(key)) e.preventDefault();
    this.keys[key] = true;
  };

  private keyupHandler = (e: KeyboardEvent) => {
    const key = e.code.toLowerCase();
    if (this.gameKeys.has(key)) e.preventDefault();
    this.keys[key] = false;
  };

  public bindKeyboardEvents(): void {
    document.addEventListener('keydown', this.keydownHandler);
    document.addEventListener('keyup', this.keyupHandler);
  }


  public getInputs(): PaddleInputs {

    return {
      player1: {
        up: this.keys['keyw'] || this.keys['arrowup'] || false,
        down: this.keys['keys'] || this.keys['arrowdown'] || false
      },
      player2: {
        up: this.keys['keyi'] || false,
        down: this.keys['keyk'] || false
      }
    };
  }

  public destroy(): void {
    document.removeEventListener('keydown', this.keydownHandler);
    document.removeEventListener('keyup', this.keyupHandler);
  }
}
