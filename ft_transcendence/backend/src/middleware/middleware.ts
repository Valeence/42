import { FastifyRequest, FastifyReply } from "fastify";
import { TokenService } from "../features/auth/services/tokenManagementService.js";
import databaseClient from "../db/index.js";
import { serialize } from "../utils/serialize.js";
import { AppLogger } from "../utils/logger.js";

declare module "fastify" {
  interface FastifyRequest {
    user?: {
      userId: number;
      username: string;
    };
  }
}

const PUBLIC_ROUTE_WHITELIST = [
  "/api/auth/test",
  "/api/auth/register",
  "/api/auth/login",
  "/api/auth/users",
  "/api/auth/oauth/google",
  "/api/auth/oauth/google/callback",
  "/api/home/stats",
  "/api/auth/loginWith2FA",
  "/api/tournament/create",
  "api/tournament",
];

export async function authenticationGuard(
  request: FastifyRequest,
  response: FastifyReply,
) {
  const normalizedPath = request.url.split("?")[0];
  AppLogger.log("Checking route:", normalizedPath);
  try {
    if (
      PUBLIC_ROUTE_WHITELIST.includes(request.url) ||
      PUBLIC_ROUTE_WHITELIST.includes(normalizedPath)
    )
      return;

    if (normalizedPath.startsWith("/api/tournament")) {
      const accessToken = request.cookies.accessToken;
      const refreshToken = request.cookies.refreshToken;

      if (accessToken) {
        const accessPayload = TokenService.validateAccessToken(accessToken);
        if (accessPayload) {
          request.user = {
            userId: accessPayload.userId,
            username: accessPayload.username,
          };
          return;
        }
      }

      if (refreshToken) {
        try {
          const refreshPayload = TokenService.validateRefreshToken(refreshToken);
          if (refreshPayload) {
            const sessionCheck = TokenService.validateSession(refreshToken);
            if (sessionCheck.valid) {
              const userQuery = databaseClient.prepare(
                "SELECT username FROM users WHERE id = ?",
              );
              const userRaw = userQuery.get(sessionCheck.userId!) as
                | { username: string }
                | undefined;

              if (userRaw) {
                const serializedUser = serialize(userRaw);
                const renewedToken = TokenService.createAccessToken({
                  userId: sessionCheck.userId!,
                  username: serializedUser.username,
                });

                response.setCookie("accessToken", renewedToken, {
                  httpOnly: true,
                  secure: process.env.NODE_ENV === "production",
                  sameSite:
                    process.env.NODE_ENV === "production" ? "strict" : "lax",
                  maxAge: 15 * 60 * 1000,
                  path: "/",
                  domain: undefined,
                });

                request.user = {
                  userId: sessionCheck.userId!,
                  username: serializedUser.username,
                };
              }
            }
          }
        } catch (error) {
          AppLogger.log(
            "Optional auth failed for tournament route, continuing without user...",
          );
        }
      }
      return;
    }

    const accessToken = request.cookies.accessToken;

    if (accessToken) {
      const accessPayload = TokenService.validateAccessToken(accessToken);
      if (accessPayload) {
        request.user = {
          userId: accessPayload.userId,
          username: accessPayload.username,
        };
        return;
      }
    }

    const refreshToken = request.cookies.refreshToken;

    if (!refreshToken) {
      AppLogger.log("No refresh token found, user needs to login again");
      return response.status(401).send({ error: "Authentification required" });
    }

    const refreshPayload = TokenService.validateRefreshToken(refreshToken);

    if (!refreshPayload)
      return response.status(401).send({ error: "Invalid refresh Token" });

    const sessionCheck = TokenService.validateSession(refreshToken);

    if (!sessionCheck.valid)
      return response.status(401).send({ error: "Session expired" });

    const userQuery = databaseClient.prepare(
      "SELECT username FROM users WHERE id = ?",
    );
    const userRaw = userQuery.get(sessionCheck.userId!) as
      | { username: string }
      | undefined;

    if (!userRaw) return response.status(401).send({ error: "User not found" });

    const serializedUser = serialize(userRaw);

    const renewedToken = TokenService.createAccessToken({
      userId: sessionCheck.userId!,
      username: serializedUser.username,
    });

    response.setCookie("accessToken", renewedToken, {
      httpOnly: true,
      secure: process.env.NODE_ENV === "production",
      sameSite: process.env.NODE_ENV === "production" ? "strict" : "lax",
      maxAge: 15 * 60 * 1000,
      path: "/",
      domain: process.env.NODE_ENV === "production" ? undefined : undefined,
    });

    request.user = {
      userId: sessionCheck.userId!,
      username: serializedUser.username,
    };
  } catch (error) {
    AppLogger.error("Middleware error:", error);
    return response.status(500).send({ error: "Authentification error" });
  }
}
