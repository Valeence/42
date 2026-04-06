import { FastifyRequest, FastifyReply } from "fastify";
import { RegisterData, LoginData } from "../types/userAuthenticationTypes.js";
import { AuthenticationService } from "../services/userAuthenticationService.js";
import { CookieManager } from "../services/sessionCookieService.js";
import { UserProfileService } from "../../user/services/userProfileService.js";
import { AppLogger } from "../../../utils/logger.js";

export class UserAuthController {
  static async registerUser(
    request: FastifyRequest,
    response: FastifyReply,
  ) {
    try {
      AppLogger.log("Register controller called");
      const userData = request.body as RegisterData;

      const result = await AuthenticationService.registerUser(userData);
      if (!result.success) {
        return response.status(400).send({ error: result.error });
      }

      CookieManager.setAuthCookies(
        response,
        result.accessToken!,
        result.refreshToken!,
      );

      response.status(201).send({
        message: "✅ User created successfully",
        user: result.user,
      });
    } catch (error) {
      AppLogger.error("Register controller error:", error);
      response.status(500).send({ error: "Registration failed" });
    }
  }

  static async loginUser(request: FastifyRequest, response: FastifyReply) {
    try {
      const loginPayload = request.body as LoginData;

      const result = await AuthenticationService.loginUser(loginPayload);
      if (!result.success && result.error === "2FA_REQUIRED") {
        return response.status(202).send({
          message: "2FA code sent to email",
          requiresTwoFactor: true,
          userId: result.user?.id,
        });
      }

      if (!result.success)
        return response.status(401).send({ error: result.error });

      CookieManager.setAuthCookies(
        response,
        result.accessToken!,
        result.refreshToken!,
      );

      const completeUserProfile = await UserProfileService.getUserDataFromDb(
        result.user!.id,
      );

      response.send({
        message: "✅ Login successful",
        user: completeUserProfile,
      });
    } catch (error) {
      AppLogger.error("Login controller error:", error);
      response.status(500).send({ error: "Login failed" });
    }
  }

  static async loginWithTwoFactor(
    request: FastifyRequest,
    response: FastifyReply,
  ) {
    try {
      const { userId, code } = request.body as { userId: number; code: string };

      if (!userId || !code) {
        return response
          .status(400)
          .send({ error: "User ID and code are required" });
      }

      const result = await AuthenticationService.loginWithTwoFactor(userId, code);

      if (!result.success) {
        return response.status(401).send({ error: result.error });
      }

      CookieManager.setAuthCookies(
        response,
        result.accessToken!,
        result.refreshToken!,
      );

      response.send({
        message: "✅ 2FA Login successful",
        user: result.user,
      });
    } catch (error) {
      AppLogger.error("2FA Login controller error:", error);
      const errorMessage =
        error instanceof Error ? error.message : "2FA login failed";
      response.status(500).send({ error: errorMessage });
    }
  }

  static async logoutUser(request: FastifyRequest, response: FastifyReply) {
    try {
      const refreshToken = request.cookies.refreshToken;
      if (refreshToken) await AuthenticationService.logoutUserSession(refreshToken);

      CookieManager.removeAuthCookies(response);
      response.send({ message: "✅ Logout successful" });
    } catch (error) {
      AppLogger.error("Logout controller error:", error);
      response.status(500).send({ error: "Logout failed" });
    }
  }
}
