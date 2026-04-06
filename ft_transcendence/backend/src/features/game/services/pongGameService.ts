import databaseClient from "../../../db/index.js";
import { MatchResponse } from "../types/pongGameTypes.js";

export class PongMatchService {
  static async recordLocalMatch(
    player1: string,
    player2: string,
    final_score1: number,
    final_score2: number,
    duration: number,
    userId?: number,
  ): Promise<MatchResponse> {
    const winner = final_score1 > final_score2 ? player1 : player2;
    const userWinner = userId && winner === player1 ? userId : null;

    const matchStmt = databaseClient.prepare(`
            INSERT INTO matches (mode, started_at, ended_at, winner_id)
            VALUES ('local', datetime('now', '-' || ? || ' seconds'), datetime('now'), ?)
        `);

    const matchResult = matchStmt.run(duration, userWinner);
    const matchId = matchResult.lastInsertRowid as number;

    const participantsStmt = databaseClient.prepare(`
            INSERT INTO session_players (session_id, user_id, player_name, final_score, is_winner)
            VALUES (?, ?, ?, ?, ?)    
        `);

    if (userId)
      participantsStmt.run(
        matchId,
        userId,
        null,
        final_score1,
        final_score1 > final_score2 ? 1 : 0,
      );
    else
      participantsStmt.run(
        matchId,
        null,
        player1,
        final_score1,
        final_score1 > final_score2 ? 1 : 0,
      );

    participantsStmt.run(
      matchId,
      null,
      player2,
      final_score2,
      final_score2 > final_score1 ? 1 : 0,
    );

    return {
      success: true,
      message: "Local match register success",
    };
  }

  static async recordRemoteMatch(
    player1UserId: number,
    player2UserId: number,
    final_score1: number,
    final_score2: number,
    duration: number,
  ): Promise<MatchResponse> {
    const winnerId =
      final_score1 > final_score2 ? player1UserId : player2UserId;

    const matchStmt = databaseClient.prepare(`
            INSERT INTO game_sessions (game_mode, session_start, session_end, winner_user_id)
            VALUES ('remote', datetime('now', '-' || ? || ' seconds'), datetime('now'), ?)
        `);

    const matchResult = matchStmt.run(duration, winnerId);
    const matchId = matchResult.lastInsertRowid as number;

    const participantsStmt = databaseClient.prepare(`
            INSERT INTO session_players (session_id, user_id, player_name, final_score, is_winner)
            VALUES (?, ?, ?, ?, ?)    
        `);

    participantsStmt.run(
      matchId,
      player1UserId,
      null,
      final_score1,
      final_score1 > final_score2 ? 1 : 0,
    );

    participantsStmt.run(
      matchId,
      player2UserId,
      null,
      final_score2,
      final_score2 > final_score1 ? 1 : 0,
    );

    return {
      success: true,
      message: "Remote match register success",
    };
  }
}
