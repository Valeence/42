import databaseClient from "../../../db/index.js";
import {
  TournamentMatch,
  TournamentResponse,
  TournamentParticipant,
  TournamentBracket,
} from "../types/competitionTypes.js";
import { AppLogger } from "../../../utils/logger.js";

export class TournamentService {
  private static shuffleArray<T>(array: T[]): T[] {
    const shuffled = [...array];
    for (let i = shuffled.length - 1; i > 0; i--) {
      const j = Math.floor(Math.random() * (i + 1));
      [shuffled[i], shuffled[j]] = [shuffled[j], shuffled[i]];
    }
    return shuffled;
  }

  private static createBracket(
    player_list: TournamentParticipant[],
  ): TournamentBracket {
    const quarterFinals: TournamentMatch[] = [];
    const semiFinals: TournamentMatch[] = [];

    for (let i = 0; i < player_list.length; i += 2) {
      if (i + 1 < player_list.length) {
        quarterFinals.push({
          id: i / 2 + 1,
          round: 1,
          position: i / 2 + 1,
          player1: player_list[i],
          player2: player_list[i + 1],
          winner: null,
          status: "pending",
        });
      }
    }

    const final: TournamentMatch = {
      id: 1,
      round: 3,
      position: 1,
      player1: null,
      player2: null,
      winner: null,
      status: "pending",
    };

    return { quarterFinals, semiFinals, final };
  }

  private static getMatchParticipants(match: TournamentMatch): {
    player1: string;
    player2: string;
  } {
    return {
      player1: match.player1?.name || "",
      player2: match.player2?.name || "",
    };
  }

  private static getMatchRoundName(round: number): string {
    if (round === 1) return "Quarter-Final";
    if (round === 2) return "Semi-Final";
    if (round === 3) return "Final";
    return `Round ${round}`;
  }
  static async createTournament(
    player_list: string[],
    userId?: number,
    gameSettings?: {
      ballSpeed: string;
      winScore: number;
      powerUps: boolean;
    },
  ): Promise<TournamentResponse> {
    try {
      let finalParticipants = [...player_list];
      const shuffledParticipants = this.shuffleArray(finalParticipants);

      const defaultSettings = {
        ballSpeed: "medium",
        winScore: 5,
        powerUps: false,
      };

      const tournamentSettings = gameSettings || defaultSettings;

      const stmt = databaseClient.prepare(`
                INSERT INTO competitions (status, player_list, game_config, created_at)
                VALUES ('waiting', ?, ?, datetime('now'))
            `);

      const result = stmt.run(
        JSON.stringify(shuffledParticipants),
        JSON.stringify(tournamentSettings),
      );
      const tournamentId = result.lastInsertRowid as number;

      const tournamentParticipants: TournamentParticipant[] =
        shuffledParticipants.map((name: string) => {
          if (userId) {
            const userStmt = databaseClient.prepare(
              "SELECT username FROM users WHERE id = ?",
            );
            const user = userStmt.get(userId) as any;
            if (user && user.username === name)
              return {
                name,
                isUser: true,
                userId,
              };
          }
          return {
            name,
            isUser: false,
          };
        });

      const bracket = this.createBracket(tournamentParticipants);

      const updateStmt = databaseClient.prepare(
        "UPDATE competitions SET status = ? WHERE id = ?",
      );
      updateStmt.run("in_progress", tournamentId);
      return {
        success: true,
        message: "Tournament created successfully",
        tournament: {
          id: tournamentId,
          status: "in_progress",
          player_list: tournamentParticipants,
          bracket,
          gameSettings: tournamentSettings,
          nextMatch: {
            id: 1,
            matchNumber: 1,
            round: "Quart de finale 1",
            player1: bracket.quarterFinals[0].player1!.name,
            player2: bracket.quarterFinals[0].player2!.name,
          },
        },
      };
    } catch (error) {
      AppLogger.error("Error creating tournament:", error);
      throw error;
    }
  }

  static async finishTournamentMatch(
    tournamentId: number,
    matchNumber: number,
    player1: string,
    player2: string,
    score1: number,
    score2: number,
    duration: number,
    userId?: number,
  ): Promise<TournamentResponse> {
    try {
      const winner = score1 > score2 ? player1 : player2;
      let userWinner: number | null = null;
      if (userId) {
        const userStmtVerif = databaseClient.prepare(
          "SELECT username FROM users WHERE id = ?",
        );
        const userVerif = userStmtVerif.get(userId) as any;
        userWinner =
          userId && winner === player1 && userVerif.username === player1
            ? userId
            : null;
      }

      const matchStmt = databaseClient.prepare(`
                INSERT INTO matches (mode, tournament_id, tournament_match_number, started_at, ended_at, winner_id)
                VALUES ('tournament', ?, ?, datetime('now', '-' || ? || ' seconds'), datetime('now'), ?)
            `);

      const matchResult = matchStmt.run(
        tournamentId,
        matchNumber,
        duration,
        userWinner,
      );
      const matchId = matchResult.lastInsertRowid as number;

      const player_listStmt = databaseClient.prepare(`
                INSERT INTO match_player_list (match_id, user_id, alias, score, is_winner)
                VALUES (?, ?, ?, ?, ?)    
            `);

      if (userId) {
        const userStmt = databaseClient.prepare("SELECT username FROM users WHERE id = ?");
        const user = userStmt.get(userId) as any;

        if (user && user.username === player1) {
          player_listStmt.run(
            matchId,
            userId,
            null,
            score1,
            score1 > score2 ? 1 : 0,
          );
        } else {
          player_listStmt.run(
            matchId,
            null,
            player1,
            score1,
            score1 > score2 ? 1 : 0,
          );
        }
      } else {
        player_listStmt.run(
          matchId,
          null,
          player1,
          score1,
          score1 > score2 ? 1 : 0,
        );
      }

      if (userId) {
        const userStmt = databaseClient.prepare("SELECT username FROM users WHERE id = ?");
        const user = userStmt.get(userId) as any;

        if (user && user.username === player2) {
          player_listStmt.run(
            matchId,
            userId,
            null,
            score2,
            score2 > score1 ? 1 : 0,
          );
        } else {
          player_listStmt.run(
            matchId,
            null,
            player2,
            score2,
            score2 > score1 ? 1 : 0,
          );
        }
      } else {
        player_listStmt.run(
          matchId,
          null,
          player2,
          score2,
          score2 > score1 ? 1 : 0,
        );
      }

      const tournamentStmt = databaseClient.prepare(
        "SELECT player_list FROM competitions WHERE id = ?",
      );
      const tournament = tournamentStmt.get(tournamentId) as any;

      if (!tournament) {
        throw new Error("Tournament not found");
      }

      const gameSettingsStmt = databaseClient.prepare(
        "SELECT game_config FROM competitions WHERE id = ?",
      );
      const gameSettingsRow = gameSettingsStmt.get(tournamentId) as any;
      const gameSettings = gameSettingsRow
        ? JSON.parse(gameSettingsRow.game_config)
        : null;

      const player_list = JSON.parse(tournament.player_list) as string[];
      const tournamentParticipants: TournamentParticipant[] = player_list.map(
        (name) => ({
          name,
          isUser: false,
        }),
      );

      const bracket = this.createBracket(tournamentParticipants);

      if (matchNumber === 7) {
        const updateTournamentStmt = databaseClient.prepare(`
                    UPDATE competitions SET status = 'completed', completed_at = datetime('now') WHERE id = ?
                `);
        updateTournamentStmt.run(tournamentId);

        return {
          success: true,
          message: "Tournament completed!",
          tournament: {
            id: tournamentId,
            status: "completed",
            player_list: tournamentParticipants,
            bracket,
            gameSettings: gameSettings,
            nextMatch: null,
            winner: winner,
          },
        };
      }

      const nextMatch = this.getNextAvailableMatch(tournamentId);

      return {
        success: true,
        message: "Match completed successfully",
        tournament: {
          id: tournamentId,
          status: "in_progress",
          player_list: tournamentParticipants,
          bracket,
          gameSettings: gameSettings,
          nextMatch,
        },
      };
    } catch (error) {
      AppLogger.error("Error finishing tournament match:", error);
      throw error;
    }
  }

  private static getNextAvailableMatch(
    tournamentId: number,
  ): {
    id: number;
    matchNumber: number;
    round: string;
    player1: string;
    player2: string;
  } | null {
    const completedMatchesStmt = databaseClient.prepare(`
            SELECT tournament_match_number FROM matches 
            WHERE tournament_id = ? AND ended_at IS NOT NULL
            ORDER BY tournament_match_number
        `);

    const completedMatches = completedMatchesStmt.all(tournamentId) as any[];
    const completedNumbers = completedMatches.map(
      (m) => m.tournament_match_number,
    );

    AppLogger.log("✅ Completed matches:", completedNumbers);
    AppLogger.log("✅ Completed matches raw:", completedMatches);

    // Get tournament participants
    const tournamentStmt = databaseClient.prepare(
      "SELECT player_list FROM competitions WHERE id = ?",
    );
    const tournament = tournamentStmt.get(tournamentId) as any;
    
    if (!tournament) {
      AppLogger.error("Tournament not found for next match");
      return null;
    }

    const player_list = JSON.parse(tournament.player_list) as string[];

    for (let matchNumber = 1; matchNumber <= 7; matchNumber++) {
      AppLogger.log(`🔍 Checking match ${matchNumber}: completed=${completedNumbers.includes(matchNumber)}, canPlay=${this.canPlayMatch(tournamentId, matchNumber, completedNumbers)}`);
      
      if (!completedNumbers.includes(matchNumber)) {
        if (this.canPlayMatch(tournamentId, matchNumber, completedNumbers)) {
          const participants = this.getNextMatchParticipants(tournamentId, matchNumber, player_list, completedNumbers);
          AppLogger.log(`🎯 Match ${matchNumber} participants:`, participants);
          
          if (participants.player1 && participants.player2) {
            AppLogger.log(`✅ Returning match ${matchNumber} with participants:`, participants);
            return {
              id: matchNumber,
              matchNumber,
              round: this.getMatchRoundName(this.getMatchRound(matchNumber)),
              player1: participants.player1,
              player2: participants.player2,
            };
          }
        }
      }
    }

    return null;
  }

  private static canPlayMatch(
    tournamentId: number,
    matchNumber: number,
    completedMatches: number[],
  ): boolean {
    if (matchNumber <= 4) {
      return true;
    } else if (matchNumber === 5) {
      return completedMatches.includes(1) && completedMatches.includes(2);
    } else if (matchNumber === 6) {
      return completedMatches.includes(3) && completedMatches.includes(4);
    } else if (matchNumber === 7) {
      return completedMatches.includes(5) && completedMatches.includes(6);
    }

    return false;
  }

  private static getMatchRound(matchNumber: number): number {
    if (matchNumber <= 4) return 1; // Quarter-finals
    if (matchNumber <= 6) return 2; // Semi-finals
    return 3; // Final
  }

  private static getNextMatchParticipants(
    tournamentId: number,
    matchNumber: number,
    playerList: string[],
    completedMatches: number[],
  ): { player1: string; player2: string } {
    // For quarter-finals (matches 1-4), use the original bracket order
    if (matchNumber <= 4) {
      const playerIndex = (matchNumber - 1) * 2;
      return {
        player1: playerList[playerIndex] || '',
        player2: playerList[playerIndex + 1] || '',
      };
    }

    // For semi-finals and final, we need to determine winners from previous matches
    // This is a simplified implementation - in a real tournament system,
    // you'd track winners and advance them through the bracket
    if (matchNumber === 5) {
      // Semi-final 1: winners of matches 1 and 2
      return {
        player1: `Winner of Match 1`, // This should be the actual winner
        player2: `Winner of Match 2`, // This should be the actual winner
      };
    } else if (matchNumber === 6) {
      // Semi-final 2: winners of matches 3 and 4
      return {
        player1: `Winner of Match 3`, // This should be the actual winner
        player2: `Winner of Match 4`, // This should be the actual winner
      };
    } else if (matchNumber === 7) {
      // Final: winners of matches 5 and 6
      return {
        player1: `Winner of Match 5`, // This should be the actual winner
        player2: `Winner of Match 6`, // This should be the actual winner
      };
    }

    return { player1: '', player2: '' };
  }
}
