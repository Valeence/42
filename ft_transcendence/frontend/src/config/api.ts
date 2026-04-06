import { DevConsole } from '@/utils/devConsole.js';

export class ApiConfig {
  private static isBrowser(): boolean {
    return typeof window !== 'undefined' && typeof window.location !== 'undefined';
  }

  private static isProduction(): boolean {
    if (!ApiConfig.isBrowser()) return false;
    const { protocol, hostname } = window.location;
    return protocol === 'https:' || !['localhost', '127.0.0.1'].includes(hostname);
  }

  private static getBaseUrl(): string {
    if (!ApiConfig.isBrowser()) {
      return '/api';
    }

    const { hostname, protocol } = window.location;
    const prod = ApiConfig.isProduction();

    if (prod) {
      // In production, backend runs on port 8000
      return 'http://localhost:8000/api';
    }

    const targetHost = hostname && hostname !== '' ? hostname : 'localhost';
    const port = 8000;
    return `http://${targetHost}:${port}/api`;
  }

  private static getWsUrl(): string {
    if (!ApiConfig.isBrowser()) {
      return 'ws://localhost:8001/ws';
    }

    const { hostname, protocol } = window.location;
    const prod = ApiConfig.isProduction();

    if (prod) {
      // In production, WebSocket server runs on port 8001
      return 'ws://localhost:8001/ws';
    }

    const devHost = hostname && hostname !== '' ? hostname : 'localhost';
    return `ws://${devHost}:8001/ws`;
  }

  public static readonly API_URL = ApiConfig.getBaseUrl();
  public static readonly WS_URL = ApiConfig.getWsUrl();

  public static logUrls(): void {
    const prod = ApiConfig.isProduction();

    if (!ApiConfig.isBrowser()) {
      DevConsole.print('🔗 API Configuration (non-browser mode)');
      DevConsole.print('  - API URL:', ApiConfig.API_URL);
      DevConsole.print('  - WebSocket URL:', ApiConfig.WS_URL);
      return;
    }

    const { hostname, port, protocol } = window.location;

    DevConsole.print('🔗 API Configuration Details');
    DevConsole.print(`  - Host: ${hostname}`);
    DevConsole.print(`  - Port: ${port || '(default)'}`);
    DevConsole.print(`  - Protocol: ${protocol}`);
    DevConsole.print(`  - API URL: ${ApiConfig.API_URL}`);
    DevConsole.print(`  - WS URL: ${ApiConfig.WS_URL}`);
    DevConsole.print(`  - Environment: ${prod ? 'production' : 'development'}`);
  }
}
