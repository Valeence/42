import { FastifyInstance } from "fastify";
import { PongMatchController } from "../controllers/pongGameController.js";

export default async function registerMatchRoutes(server: FastifyInstance) {
  server.post("/local", PongMatchController.registerLocalMatch);
  server.post("/remote", PongMatchController.registerRemoteMatch);
}
