import cron from "node-cron";
import databaseClient from "../db/index.js";
import { TokenService } from "../features/auth/services/tokenManagementService.js";
import { AppLogger } from "../utils/logger.js";

interface TokenRow {
  user_id: number;
  expires_at: string;
}

function cleanupExpiredTokens(): void {
  const tokens = databaseClient
    .prepare("SELECT user_id, expires_at FROM security_codes")
    .all() as TokenRow[];
  const now = new Date(Date.now()).toISOString();

  tokens.forEach((token) => {
    if (token.expires_at < now) {
      databaseClient.prepare("DELETE FROM security_codes WHERE user_id = ?").run(
        token.user_id,
      );
      AppLogger.log(`Token expiré supprimé pour user_id: ${token.user_id}`);
    }
  });
}

export function startTokenCleanup(): void {
  cron.schedule("0 0 * * *", cleanupExpiredTokens);
  cron.schedule("0 0 * * *", TokenService.purgeExpiredSessions);
  AppLogger.log("✅ Token cleanup cron job started");
}

export { cleanupExpiredTokens };
