import { FastifyRequest, FastifyReply } from "fastify";
import { TournamentService } from "../services/competitionService.js";
import { AppLogger } from "../../../utils/logger.js";

export class CompetitionController {
  static async handleTournamentCreation(
    request: FastifyRequest,
    response: FastifyReply,
  ) {
    try {
      const user = request.user;
      const { participants, gameSettings } = request.body as {
        participants: string[];
        gameSettings?: {
          ballSpeed: string;
          winScore: number;
          powerUps: boolean;
        };
      };

      const tournament = await TournamentService.createTournament(
        participants,
        user?.userId,
        gameSettings,
      );

      return response.status(201).send({
        success: true,
        message: "Tournament create successfully",
        tournament,
      });
    } catch (error) {
      AppLogger.error("Create tournament error:", error);
      return response.status(500).send({
        success: false,
        error: "Failed to create tournament",
      });
    }
  }

  static async handleTournamentMatchCompletion(
    request: FastifyRequest,
    response: FastifyReply,
  ) {
    AppLogger.log("🏆 Processing tournament match finish...");
    try {
      const user = request.user;
      const {
        tournamentId,
        matchNumber,
        player1,
        player2,
        score1,
        score2,
        duration,
      } = request.body as {
        tournamentId: number;
        matchNumber: number;
        player1: string;
        player2: string;
        score1: number;
        score2: number;
        duration: number;
      };

      if (
        !tournamentId ||
        !matchNumber ||
        !player1 ||
        !player2 ||
        score1 === undefined ||
        score2 === undefined ||
        !duration
      ) {
        return response.status(400).send({
          success: false,
          error: "Missing required parameters",
        });
      }

      const result = await TournamentService.finishTournamentMatch(
        tournamentId,
        matchNumber,
        player1,
        player2,
        score1,
        score2,
        duration,
        user?.userId,
      );

      AppLogger.log(
        "✅ Tournament service result:",
        JSON.stringify(result, null, 2),
      );

      return response.status(200).send(result);
    } catch (error) {
      AppLogger.error("Finish tournament match error:", error);
      return response.status(500).send({
        success: false,
        error: "Failed to finish tournament match",
      });
    }
  }
}
