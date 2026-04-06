import { FastifyRequest, FastifyReply } from "fastify";
import { TwoFactorService } from "../services/securityCodeService.js";
import { AppLogger } from "../../../utils/logger.js";

export class SecurityCodeController {
  static async sendSecurityCode(request: FastifyRequest, response: FastifyReply) {
    try {
      const { userId } = request.user as { userId: number };

      const result = await TwoFactorService.sendVerificationCode(userId);
      return response
        .status(200)
        .send({ success: true, message: result.message });
    } catch (error) {
      if (error instanceof Error) AppLogger.error(error.message);
      return response
        .status(500)
        .send({ error: "Internal error sending 2FA code" });
    }
  }

  static async verifySecurityCode(
    request: FastifyRequest,
    response: FastifyReply,
  ) {
    try {
      const { userId } = request.user as { userId: number };
      const { code, disabled } = request.body as {
        code: string;
        disabled: boolean;
      };

      AppLogger.log("Verification code received:", code, "Disabled:", disabled);
      const result = await TwoFactorService.validateSecurityCode(
        userId,
        code,
        disabled,
      );
      if (!result.success)
        return response.status(400).send({ error: result.message });
      return response
        .status(200)
        .send({ success: true, message: result.message });
    } catch (error) {
      if (error instanceof Error) {
        AppLogger.error(error.message);
        const errorMessage = error.message;
        if (errorMessage === "Too many failed attempts") {
          return response
            .status(400)
            .send({ error: "Too many failed attempts" });
        }
      }
      return response
        .status(500)
        .send({ error: "Internal error verifying 2FA code" });
    }
  }
}
