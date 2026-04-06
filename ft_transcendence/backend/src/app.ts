import Fastify from "fastify";
import cors from "@fastify/cors";
import cookie from "@fastify/cookie";
import multipart from "@fastify/multipart";
import fastifyStatic from "@fastify/static";
import path from "path";
import registerAuthRoutes from "./features/auth/routes/userAuthenticationRoutes.js";
import registerUserProfileRoutes from "./features/user/routes/userProfileRoutes.js";
import registerSocialRoutes from "./features/user/routes/socialConnectionsRoutes.js";
import registerStatsRoutes from "./features/stats/routes/serverStatsRoutes.js";
import registerTwoFactorRoutes from "./features/auth/routes/securityCodeRoutes.js";
import registerTournamentRoutes from "./features/tournament/routes/competitionRoutes.js";
import registerGameRoutes from "./features/game/routes/pongGameRoutes.js";
import { authenticationGuard } from "./middleware/middleware.js";
import { startTokenCleanup } from "./utils/cleanupTokens.js";
import { WebSocketService } from "./features/websocket/services/multiplayerWebSocketService.js";
import { AppLogger } from "./utils/logger.js";
import "dotenv/config";

const httpServer = Fastify({ logger: process.env.NODE_ENV !== "production" });

async function configureCors() {
  await httpServer.register(cors, {
    origin:
      process.env.NODE_ENV === "production"
        ? ["https://localhost:8443", "https://localhost", "http://localhost:8080"]
        : [
            "http://localhost:5173",
            "http://localhost:3000",
            "http://localhost:8080",
            "http://localhost:8000",
            /^http:\/\/10\.16\.\d+\.\d+:8080$/,
            /^http:\/\/192\.168\.\d+\.\d+:8080$/,
            /^http:\/\/172\.16\.\d+\.\d+:8080$/,
          ],
    credentials: true,
    methods: ["GET", "POST", "PUT", "DELETE", "OPTIONS"],
    allowedHeaders: ["Content-Type", "Authorization", "X-Requested-With"],
    optionsSuccessStatus: 200,
  });
}

async function configurePlugins() {
  await configureCors();

  await httpServer.register(cookie, {
    secret: process.env.COOKIE_SECRET || "fallback-cookie-secret",
  });

  await httpServer.register(multipart, {
    limits: {
      fileSize: 5 * 1024 * 1024,
    },
  });

  await httpServer.register(fastifyStatic, {
    root: path.join(process.cwd(), "uploads"),
    prefix: "/uploads/",
  });
}

async function registerRoutes() {
  httpServer.addHook("preHandler", authenticationGuard);

  await httpServer.register(registerAuthRoutes, { prefix: "/api/auth" });
  await httpServer.register(registerTwoFactorRoutes, { prefix: "/api/2fa" });
  await httpServer.register(registerUserProfileRoutes, { prefix: "/api/user" });
  await httpServer.register(registerSocialRoutes, { prefix: "/api/friends" });
  await httpServer.register(registerStatsRoutes, { prefix: "/api/home" });
  await httpServer.register(registerTournamentRoutes, { prefix: "/api/tournament" });
  await httpServer.register(registerGameRoutes, { prefix: "/api/match" });
}

async function launchServer() {
  try {
    startTokenCleanup();

    new WebSocketService(8001, "0.0.0.0");

    await configurePlugins();
    await registerRoutes();

    await httpServer.listen({ port: 8000, host: "0.0.0.0" });
    AppLogger.log("✅ Backend running on http://localhost:8000");
    AppLogger.log("✅ WebSocket signaling on ws://localhost:8001");
  } catch (error) {
    AppLogger.error("💥 Failed to start server:", error);
    httpServer.log.error(error);
    process.exit(1);
  }
}

void launchServer();
