import * as BABYLON from '@babylonjs/core';
import type { GameEntityMap, EntityPositions } from '@/types/index.js';
import { DevConsole } from '@/utils/devConsole.js';

export class GameRenderer {
  private scene: BABYLON.Scene;
  private camera: BABYLON.ArcRotateCamera;
  private canvas: HTMLCanvasElement;
  private gameObjects: GameEntityMap;
  private meshes: Record<string, BABYLON.Mesh> = {};
  private paddleSizeMultipliers = { player1: 1, player2: 1 };
  private basePaddleScales = {
    player1: { x: 1, y: 1, z: 1 },
    player2: { x: 1, y: 1, z: 1 }
  };

  constructor(scene: BABYLON.Scene, canvas: HTMLCanvasElement) {
    this.scene = scene;
    this.canvas = canvas;

    this.setupCamera();
    this.setupLighting();
    this.createGameObjects();
    this.createFieldBorders();
    this.adjustCameraForScreen();
  }

  public isInitialized(): boolean {
    return !!(
      this.gameObjects &&
      this.gameObjects.player1Paddle &&
      this.gameObjects.player2Paddle &&
      this.gameObjects.ball &&
      this.gameObjects.field
    );
  }

  public applyPaddleSizeModifier(player: 'player1' | 'player2', multiplier: number): void {
    this.paddleSizeMultipliers[player] = multiplier;
    const paddle = this.gameObjects?.[`${player}Paddle`];
    if (paddle) {
      const base = this.basePaddleScales[player];
      paddle.scaling = new BABYLON.Vector3(base.x, base.y * multiplier, base.z * multiplier);
      DevConsole.print(`📏 ${player} paddle size multiplier: ${multiplier}`);
    } else {
      DevConsole.reportError(`🚨 ${player}Paddle not found`);
    }
  }

  public resetPaddleSize(player?: 'player1' | 'player2'): void {
    if (player) {
      this.paddleSizeMultipliers[player] = 1;
      const paddle = this.gameObjects?.[`${player}Paddle`];
      if (paddle) {
        const base = this.basePaddleScales[player];
        paddle.scaling = new BABYLON.Vector3(base.x, base.y, base.z);
      }
    } else {
      this.resetPaddleSize('player1');
      this.resetPaddleSize('player2');
    }
  }

  public updatePositions(positions: EntityPositions): void {
    if (!this.gameObjects) return DevConsole.reportError('🚨 GameObjects not initialized');

    if (this.gameObjects.player1Paddle) this.gameObjects.player1Paddle.position.z = positions.player1Paddle.z;
    if (this.gameObjects.player2Paddle) this.gameObjects.player2Paddle.position.z = positions.player2Paddle.z;

    if (this.gameObjects.ball) {
      Object.assign(this.gameObjects.ball.position, positions.ball);
    }
  }

  public adjustCameraForScreen(): void {
    const width = window.innerWidth;
    if (width <= 768) {
      this.camera.radius = 18;
      this.camera.beta = Math.PI / 2.5;
    } else if (width <= 1024) {
      this.camera.radius = 16;
      this.camera.beta = Math.PI / 2.8;
    } else {
      this.camera.radius = 15;
      this.camera.beta = Math.PI / 3;
    }
  }

  public getGameObjects(): GameEntityMap {
    return this.gameObjects;
  }

  public destroy(): void {
    this.disposeGameObjects();
  }

  /** Internal helpers **/
  private setupCamera(): void {
    this.camera = new BABYLON.ArcRotateCamera(
      'camera',
      -Math.PI / 2,
      Math.PI / 3,
      15,
      BABYLON.Vector3.Zero(),
      this.scene
    );
    this.adjustCameraForScreen();
  }

  private setupLighting(): void {
    this.scene.lights.forEach(light => light.dispose());

    const hemiLight = new BABYLON.HemisphericLight('hemiLight', new BABYLON.Vector3(0, 1, 0), this.scene);
    hemiLight.intensity = 0.6;

    const dirLight = new BABYLON.DirectionalLight('dirLight', new BABYLON.Vector3(-1, -1, -1), this.scene);
    dirLight.intensity = 0.8;
    dirLight.position = new BABYLON.Vector3(5, 10, 5);

    this.scene.clearColor = new BABYLON.Color4(0.125, 0.125, 0.125, 1);
  }

  private createGameObjects(): void {
    this.gameObjects = {
      field: this.createField(),
      player1Paddle: this.createPaddle('player1', -4.5),
      player2Paddle: this.createPaddle('player2', 4.5),
      ball: this.createBall(),
      borders: []
    };

    this.meshes = {
      field: this.gameObjects.field,
      player1Paddle: this.gameObjects.player1Paddle,
      player2Paddle: this.gameObjects.player2Paddle,
      ball: this.gameObjects.ball
    };

    this.basePaddleScales.player1 = {
      x: this.gameObjects.player1Paddle.scaling.x,
      y: this.gameObjects.player1Paddle.scaling.y,
      z: this.gameObjects.player1Paddle.scaling.z
    };
    this.basePaddleScales.player2 = {
      x: this.gameObjects.player2Paddle.scaling.x,
      y: this.gameObjects.player2Paddle.scaling.y,
      z: this.gameObjects.player2Paddle.scaling.z
    };
  }

  private createField(): BABYLON.Mesh {
    const field = BABYLON.MeshBuilder.CreateGround('field', { width: 10, height: 6 }, this.scene);
    const mat = new BABYLON.StandardMaterial('fieldMaterial', this.scene);
    mat.diffuseColor = new BABYLON.Color3(0.2, 0.2, 0.2);
    mat.specularColor = new BABYLON.Color3(0.3, 0.3, 0.3);
    field.material = mat;

    const centerLine = BABYLON.MeshBuilder.CreateBox('centerLine', { width: 0.1, height: 0.02, depth: 6 }, this.scene);
    centerLine.position = new BABYLON.Vector3(0, 0.01, 0);
    const centerMat = new BABYLON.StandardMaterial('centerLineMaterial', this.scene);
    centerMat.emissiveColor = new BABYLON.Color3(0.6, 0.6, 0.6);
    centerLine.material = centerMat;

    return field;
  }

  private createFieldBorders(): void {
    const mat = new BABYLON.StandardMaterial('borderMaterial', this.scene);
    mat.emissiveColor = new BABYLON.Color3(0.5, 0.5, 0.5);

    const top = BABYLON.MeshBuilder.CreateBox('topBorder', { width: 10, height: 0.2, depth: 0.2 }, this.scene);
    top.position = new BABYLON.Vector3(0, 0.1, 3);
    top.material = mat;

    const bottom = BABYLON.MeshBuilder.CreateBox('bottomBorder', { width: 10, height: 0.2, depth: 0.2 }, this.scene);
    bottom.position = new BABYLON.Vector3(0, 0.1, -3);
    bottom.material = mat.clone('bottomBorderMaterial');

    if (this.gameObjects) this.gameObjects.borders = [top, bottom];
  }

  private createPaddle(player: 'player1' | 'player2', x: number): BABYLON.Mesh {
    const paddle = BABYLON.MeshBuilder.CreateBox(`${player}Paddle`, { width: 0.2, height: 0.4, depth: 1 }, this.scene);
    paddle.position = new BABYLON.Vector3(x, 0.15, 0);

    const mat = new BABYLON.StandardMaterial(`${player}PaddleMaterial`, this.scene);
    mat.specularColor = new BABYLON.Color3(0.8, 0.8, 0.8);
    mat.diffuseColor = player === 'player1' ? new BABYLON.Color3(0.4, 0.7, 1.0) : new BABYLON.Color3(1.0, 0.4, 0.4);
    paddle.material = mat;

    return paddle;
  }

  private createBall(): BABYLON.Mesh {
    const ball = BABYLON.MeshBuilder.CreateSphere('ball', { diameter: 0.3 }, this.scene);
    ball.position = new BABYLON.Vector3(0, 0.15, 0);
    const mat = new BABYLON.StandardMaterial('ballMaterial', this.scene);
    mat.diffuseColor = new BABYLON.Color3(0.9, 0.9, 0.9);
    mat.specularColor = new BABYLON.Color3(1, 1, 1);
    ball.material = mat;
    return ball;
  }

  private disposeGameObjects(): void {
    if (!this.gameObjects) return;
    Object.values(this.gameObjects).forEach(obj => {
      if (obj && obj.material) obj.material.dispose();
      if (obj && 'dispose' in obj) obj.dispose();
    });
  }
}
