import { FastifyInstance } from "fastify";
import { ServerStatsController } from "../controllers/serverStatsController.js";

export default async function homeRoutes(app: FastifyInstance) {
  app.get("/stats", ServerStatsController.handleGetServerStats);
}
