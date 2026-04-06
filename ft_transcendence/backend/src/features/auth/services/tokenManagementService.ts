import jwt from "jsonwebtoken";
import databaseClient from "../../../db/index.js";
import { SessionResult, TokenPayload } from "../types/tokenManagementTypes.js";
import { AppLogger } from "../../../utils/logger.js";

const ACCESS_SECRET_KEY =
  process.env.ACCESS_TOKEN_SECRET || "fallback-access-secret";
const REFRESH_SECRET_KEY =
  process.env.REFRESH_TOKEN_SECRET || "fallback-refresh-secret";

export class TokenService {
  static createAccessToken(payload: { userId: number; username: string }): string {
    return jwt.sign(payload, ACCESS_SECRET_KEY, { expiresIn: "15m" });
  }

  static createRefreshToken(payload: { userId: number }): string {
    return jwt.sign(payload, REFRESH_SECRET_KEY, { expiresIn: "30d" });
  }

  static issueTokenPair(userId: number, username: string) {
    const accessToken = this.createAccessToken({ userId, username });
    const refreshToken = this.createRefreshToken({ userId });

    return { accessToken, refreshToken };
  }

  static validateAccessToken(token: string): TokenPayload | null {
    try {
      return jwt.verify(token, ACCESS_SECRET_KEY) as TokenPayload;
    } catch (error) {
      AppLogger.error("Access token verification failed:", error);
      return null;
    }
  }

  static validateRefreshToken(token: string): TokenPayload | null {
    try {
      return jwt.verify(token, REFRESH_SECRET_KEY) as TokenPayload;
    } catch (error) {
      AppLogger.error("Refresh token verification failed:", error);
      return null;
    }
  }

  static storeSession(userId: number, refreshToken: string): number {
    const expiryDate = new Date(Date.now() + 30 * 24 * 60 * 60 * 1000);

    const statement = databaseClient.prepare(`
                INSERT INTO sessions (user_id, refresh_token, expires_at)
                VALUES (?, ?, ?)
            `);

    const result = statement.run(userId, refreshToken, expiryDate.toISOString());

    return result.lastInsertRowid as number;
  }

  static validateSession(refreshToken: string): SessionResult {
    const statement = databaseClient.prepare(`
            SELECT user_id FROM sessions 
            WHERE refresh_token = ? AND expires_at > CURRENT_TIMESTAMP
        `);

    const storedSession = statement.get(refreshToken) as { user_id: number } | undefined;
    if (storedSession) return { valid: true, userId: storedSession.user_id };
    return { valid: false };
  }

  static removeSession(refreshToken: string): void {
    const statement = databaseClient.prepare(
      "DELETE FROM sessions WHERE refresh_token = ?",
    );
    statement.run(refreshToken);
  }

  static purgeUserSessions(userId: number): void {
    const statement = databaseClient.prepare(
      "DELETE FROM sessions WHERE user_id = ?",
    );
    statement.run(userId);
  }

  static purgeExpiredSessions(): void {
    const statement = databaseClient.prepare(
      "DELETE FROM sessions WHERE expires_at <= CURRENT_TIMESTAMP",
    );
    const result = statement.run();
    AppLogger.log(`Cleaned ${result.changes} expired sessions`);
  }
}
