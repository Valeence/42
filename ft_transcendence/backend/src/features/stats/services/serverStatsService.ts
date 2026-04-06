import databaseClient from "../../../db/index.js";
import { HomeStats } from "../types/serverStatsTypes.js";
import { AppLogger } from "../../../utils/logger.js";

export class HomeService {
  static getHomeStats(): HomeStats {
    try {
      const totalUsersStmt = databaseClient.prepare("SELECT COUNT(*) as count FROM users");
      const totalPlayers = (totalUsersStmt.get() as any).count;

      const totalMatchesStmt = databaseClient.prepare(
        "SELECT COUNT(*) as count FROM matches WHERE ended_at IS NOT NULL",
      );
      const totalGames = (totalMatchesStmt.get() as any).count;

      const onlineUsersStmt = databaseClient.prepare(
        "SELECT COUNT(*) as count FROM users WHERE is_online = 1",
      );
      const onlinePlayers = (onlineUsersStmt.get() as any).count;

      return {
        totalPlayers,
        totalGames,
        onlinePlayers,
      };
    } catch (error) {
      AppLogger.error("Error getting home stats:", error);
      return {
        totalPlayers: 0,
        totalGames: 0,
        onlinePlayers: 0,
      };
    }
  }
}
