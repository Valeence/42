import { DevConsole } from '@/utils/devConsole.js';

export class TwoFactorService {
  private static instance: TwoFactorService;
  private baseURL = process.env.NODE_ENV === 'production'
    ? '/api'
    : `http://${location.hostname}:8000/api`;

  public static getInstance(): TwoFactorService {
    if (!TwoFactorService.instance) {
      TwoFactorService.instance = new TwoFactorService();
    }
    return TwoFactorService.instance;
  }

  public async disable2FA(): Promise<{ success: boolean; message: string }> {
    try {
      const response = await fetch(`${this.baseURL}/2fa/disabled`, {
        method: 'POST',
        credentials: 'include',
        body: JSON.stringify({ disabled: true })
      });

      const data = await response.json();
      if (!response.ok) {
        throw new Error(data.error || 'Failed to disable 2FA');
      }
      return data;
    } catch (err) {
      DevConsole.reportError('Failed to disable 2FA:', err);
      throw err;
    }
  }

  public async enable2FA(): Promise<{ success: boolean; message: string }> {
    try {
      const response = await fetch(`${this.baseURL}/2fa/enabled`, {
        method: 'POST',
        credentials: 'include',
        body: JSON.stringify({ disabled: false })
      });

      const data = await response.json();
      if (!response.ok) {
        throw new Error(data.error || 'Failed to enable 2FA');
      }
      return data;
    } catch (err) {
      DevConsole.reportError('Failed to enable 2FA:', err);
      throw err;
    }
  }

  public async verify2FA(code: string, disabled: boolean): Promise<{ success: boolean; message: string }> {
    try {
      const response = await fetch(`${this.baseURL}/2fa/verify`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        credentials: 'include',
        body: JSON.stringify({ code, disabled })
      });

      const data = await response.json();
      if (!response.ok) {
        throw new Error(data.error || 'Failed to verify 2FA code');
      }
      return data;
    } catch (err) {
      DevConsole.reportError('Failed to verify 2FA:', err);
      throw err;
    }
  }
}

export const securityCodeService = TwoFactorService.getInstance();
