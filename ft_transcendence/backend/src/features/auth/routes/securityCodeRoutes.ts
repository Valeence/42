import { FastifyInstance } from "fastify";
import { SecurityCodeController } from "../controllers/securityCodeController.js";

export default async function registerTwoFactorRoutes(
  server: FastifyInstance,
) {
  server.post("/enabled", SecurityCodeController.sendSecurityCode);
  server.post("/verify", SecurityCodeController.verifySecurityCode);
  server.post("/disabled", SecurityCodeController.sendSecurityCode);
}
