const isProduction = import.meta.env.PROD;

export class DevConsole {
  static print(message: unknown, ...metadata: unknown[]): void {
    if (isProduction) return;
    console.log('[DEV]', message, ...metadata);
  }

  static warn(message: unknown, ...metadata: unknown[]): void {
    if (isProduction) return;
    console.warn('[DEV]', message, ...metadata);
  }

  static reportError(message: unknown, ...metadata: unknown[]): void {
    if (isProduction) return;
    console.error('[DEV]', message, ...metadata);
  }
}
