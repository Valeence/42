import { FastifyRequest, FastifyReply } from "fastify";
import { HomeService } from "../services/serverStatsService.js";
import { AppLogger } from "../../../utils/logger.js";

export class ServerStatsController {
  static async handleGetServerStats(request: FastifyRequest, response: FastifyReply) {
    try {
      const stats = HomeService.getHomeStats();

      response.send(stats);
    } catch (error) {
      AppLogger.error("Get general stats error:", error);
      response.status(500).send({ error: "Failed to get general stats" });
    }
  }
}
