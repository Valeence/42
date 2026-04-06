import { FastifyInstance } from "fastify";
import { CompetitionController } from "../controllers/competitionController.js";
import { createTournamentSchema } from "../../game/schemas/pongGameSchema.js";

export default async function tournamentRoutes(app: FastifyInstance) {
  app.post("/create", CompetitionController.handleTournamentCreation);
  app.post(
    "/:tournamentId/matches/:matchId/finish",
    CompetitionController.handleTournamentMatchCompletion,
  );
}
