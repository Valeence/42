import { FastifyRequest, FastifyReply } from "fastify";
import { PongMatchService } from "../services/pongGameService.js";
import { AppLogger } from "../../../utils/logger.js";

export class PongMatchController {
  static async registerLocalMatch(
    request: FastifyRequest,
    response: FastifyReply,
  ) {
    try {
      const authenticatedUser = request.user;

      const { player1, player2, score1, score2, duration } = request.body as {
        player1: string;
        player2: string;
        score1: number;
        score2: number;
        duration: number;
      };
      if (!player1 || !player2) {
        return response.status(400).send({
          success: false,
          error: "both player required",
        });
      }

      const match = await PongMatchService.recordLocalMatch(
        player1,
        player2,
        score1,
        score2,
        duration,
        authenticatedUser?.userId,
      );

      return response.status(200).send({
        success: true,
        message: "local match register",
        match,
      });
    } catch (error) {
      AppLogger.error("Register local match error:", error);
      return response.status(500).send({
        success: false,
        error: "Failed to register match",
      });
    }
  }

  static async registerRemoteMatch(
    request: FastifyRequest,
    response: FastifyReply,
  ) {
    try {
      const authenticatedUser = request.user;
      if (!authenticatedUser) {
        return response.status(401).send({
          success: false,
          error: "Authentication required",
        });
      }

      const { opponentUserId, score1, score2, duration } = request.body as {
        opponentUserId: number;
        score1: number;
        score2: number;
        duration: number;
      };
      if (!opponentUserId || score1 === undefined || score2 === undefined) {
        return response.status(400).send({
          success: false,
          error: "opponentUserId, score1, score2 required",
        });
      }

      const match = await PongMatchService.recordRemoteMatch(
        authenticatedUser.userId,
        opponentUserId,
        score1,
        score2,
        duration,
      );

      return response.status(200).send({
        success: true,
        message: "remote match register",
        match,
      });
    } catch (error) {
      AppLogger.error("Register remote match error:", error);
      return response.status(500).send({
        success: false,
        error: "Failed to register remote match",
      });
    }
  }
}
