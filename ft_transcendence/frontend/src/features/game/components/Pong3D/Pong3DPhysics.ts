import type { ArenaSettings, EntityPositions } from '@/types/index.js';
import { DevConsole } from '@/utils/devConsole.js';

export interface PaddleInputs {
  player1: { up: boolean; down: boolean };
  player2: { up: boolean; down: boolean };
}

export interface PhysicsUpdate {
  positions: EntityPositions;
  events: {
    goal?: { scorer: 'player1' | 'player2' };
    collision?: boolean;
  };
}

export class GamePhysics {
  private settings: ArenaSettings;
  private positions: EntityPositions = {
    player1Paddle: { x: -4.5, z: 0 },
    player2Paddle: { x: 4.5, z: 0 },
    ball: { x: 0, y: 0.15, z: 0 }
  };
  private ballVelocity = { x: 0, z: 0 };
  private ballSpeed = 0.05;
  private basePaddleSpeed = 0.1;
  private paddleSpeed = 0.1;
  private paddleSpeedMultipliers = { player1: 1, player2: 1 };
  private paddleSizeMultipliers = { player1: 1, player2: 1 };

  constructor(settings: ArenaSettings) {
    this.settings = settings;
    this.setBallSpeed(settings.ballSpeed);
    this.basePaddleSpeed = this.paddleSpeed;
  }

  /** Main Update Loop **/
  public update(inputs: PaddleInputs): PhysicsUpdate {
    const events: PhysicsUpdate['events'] = {};

    this.updatePaddles(inputs);
    this.updateBall();

    if (this.checkCollisions()) events.collision = true;

    const goalScorer = this.checkGoals();
    if (goalScorer) events.goal = { scorer: goalScorer };

    return { positions: { ...this.positions }, events };
  }

  /** Getters **/
  public getBallVelocity(): { x: number; z: number } {
    return { ...this.ballVelocity };
  }

  public getPositions(): EntityPositions {
    return { ...this.positions };
  }

  public getPaddleSpeed(): number {
    return this.paddleSpeed;
  }

  /** Paddle Speed & Size Modifiers **/
  public applyPaddleSpeedModifier(player: 'player1' | 'player2', multiplier: number): void {
    this.paddleSpeedMultipliers[player] = multiplier;
    DevConsole.print(`🏓 ${player} paddle speed multiplier: ${multiplier}`);
  }

  public resetSpeed(): void {
    this.setBallSpeed(this.settings.ballSpeed);
  }

  public setPaddleSpeed(speed: number): void {
    this.paddleSpeed = speed;
  }

  public applySpeedModifier(multiplier: number): void {
    this.ballSpeed *= multiplier;
  }

  public resetPaddleSpeed(player?: 'player1' | 'player2'): void {
    if (player) this.paddleSpeedMultipliers[player] = 1;
    else this.paddleSpeedMultipliers = { player1: 1, player2: 1 };
  }

  public setPaddleSizeMultipliers(multipliers: { player1: number; player2: number }): void {
    this.paddleSizeMultipliers = { ...multipliers };
  }

  /** Reset positions **/
  public reset(): void {
    this.positions = {
      player1Paddle: { x: -4.5, z: 0 },
      player2Paddle: { x: 4.5, z: 0 },
      ball: { x: 0, y: 0.15, z: 0 }
    };
    this.ballVelocity = { x: 0, z: 0 };
  }

  public launchBall(): void {
    const direction = Math.random() > 0.5 ? 1 : -1;
    const angle = (Math.random() - 0.5) * 0.5;
    this.ballVelocity.x = direction * this.ballSpeed;
    this.ballVelocity.z = angle * this.ballSpeed;
  }

  /** Internal Helpers **/
  private setBallSpeed(speed: 'slow' | 'medium' | 'fast'): void {
    this.ballSpeed = speed === 'slow' ? 0.03 : speed === 'medium' ? 0.05 : 0.08;
  }

  private updatePaddles(inputs: PaddleInputs): void {
    const maxZ = 2.2, minZ = -2.2;
    const speeds = {
      player1: this.basePaddleSpeed * this.paddleSpeedMultipliers.player1,
      player2: this.basePaddleSpeed * this.paddleSpeedMultipliers.player2
    };

    if (inputs.player1.up) this.positions.player1Paddle.z = Math.min(maxZ, this.positions.player1Paddle.z + speeds.player1);
    if (inputs.player1.down) this.positions.player1Paddle.z = Math.max(minZ, this.positions.player1Paddle.z - speeds.player1);

    if (inputs.player2.up) this.positions.player2Paddle.z = Math.min(maxZ, this.positions.player2Paddle.z + speeds.player2);
    if (inputs.player2.down) this.positions.player2Paddle.z = Math.max(minZ, this.positions.player2Paddle.z - speeds.player2);
  }

  private updateBall(): void {
    const ball = this.positions.ball;
    ball.x += this.ballVelocity.x;
    ball.z += this.ballVelocity.z;

    if (ball.z > 2.8) { ball.z = 2.8; this.ballVelocity.z *= -1; }
    else if (ball.z < -2.8) { ball.z = -2.8; this.ballVelocity.z *= -1; }
  }

  private checkCollisions(): boolean {
    const ball = this.positions.ball;
    const p1 = this.positions.player1Paddle;
    const p2 = this.positions.player2Paddle;
    const baseHeight = 0.8;

    const heights = {
      player1: baseHeight * this.paddleSizeMultipliers.player1,
      player2: baseHeight * this.paddleSizeMultipliers.player2
    };

    if (ball.x <= -4.2 && ball.x >= -4.8 && Math.abs(ball.z - p1.z) < heights.player1) {
      this.ballVelocity.x *= -1.1;
      this.ballVelocity.z += (ball.z - p1.z) * 0.1;
      return true;
    }

    if (ball.x >= 4.2 && ball.x <= 4.8 && Math.abs(ball.z - p2.z) < heights.player2) {
      this.ballVelocity.x *= -1.1;
      this.ballVelocity.z += (ball.z - p2.z) * 0.1;
      return true;
    }

    return false;
  }

  private checkGoals(): 'player1' | 'player2' | null {
    const x = this.positions.ball.x;
    if (x > 5) return 'player1';
    if (x < -5) return 'player2';
    return null;
  }
}
