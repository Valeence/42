import databaseClient from "../../../db/index.js";
import {
  FriendsResult,
  FriendProfile,
} from "../types/socialConnectionsTypes.js";
import { serialize } from "../../../utils/serialize.js";
import { AppLogger } from "../../../utils/logger.js";

export class FriendConnectionsService {
  static async createFriendship(
    userId: number,
    friendId: number,
  ): Promise<FriendsResult> {
    const transaction = databaseClient.transaction(() => {
      try {
        if (userId === friendId) throw { error: "Cant add yourself as friend" };

        const friendExists = databaseClient
          .prepare("SELECT id FROM users WHERE id = ?")
          .get(friendId);
        if (!friendExists) throw { error: "User not found" };

        const existingFriendship = databaseClient
          .prepare(
            `
                    SELECT * FROM friends 
                    WHERE (user_id = ? AND friend_id = ?)
                `,
          )
          .get(userId, friendId);
        if (existingFriendship) throw { error: "already friends" };

        const stmt = databaseClient.prepare(`
                    INSERT INTO friends (user_id, friend_id) 
                    VALUES (?, ?)
                `);

        const result = stmt.run(userId, friendId);

        return {
          success: true,
          data: { friendshipId: result.lastInsertRowid },
        };
      } catch (error) {
        throw error;
      }
    });

    try {
      return transaction();
    } catch (error) {
      AppLogger.error("Friend add:", error);
      return {
        success: false,
        error: "Fail add friend",
      };
    }
  }

  static async listFriendships(userId: number): Promise<FriendProfile[]> {
    try {
      const stmt = databaseClient.prepare(`
                SELECT DISTINCT u.id, u.username, u.avatar_url, u.is_online, u.last_login, f.created_at
                FROM users u
                JOIN friends f ON f.friend_id = u.id
                WHERE f.user_id = ?
                ORDER BY u.is_online DESC, u.username ASC
            `);

      const friendsRaw = stmt.all(userId) as any[];

      const friends: FriendProfile[] = friendsRaw.map((friendRaw) => {
        const friend = serialize(friendRaw);

        return {
          id: friend.id,
          username: friend.username,
          avatarUrl: friend.avatarUrl,
          isOnline: Boolean(friend.isOnline),
          lastSeen: friend.lastLogin,
          friendshipDate: friend.createdAt,
        };
      });

      return friends;
    } catch (error) {
      AppLogger.error("Error getting friends:", error);
      return [];
    }
  }

  static async deleteFriendship(
    userId: number,
    friendId: number,
  ): Promise<FriendsResult> {
    const transaction = databaseClient.transaction(() => {
      try {
        const stmt = databaseClient.prepare(`
                    DELETE FROM friends 
                    WHERE (user_id = ? AND friend_id = ?) OR (user_id = ? AND friend_id = ?)
                `);

        const result = stmt.run(userId, friendId, friendId, userId);
        if (result.changes === 0) throw { error: "Friendship not found" };

        return { success: true };
      } catch (error) {
        throw error;
      }
    });

    try {
      return transaction();
    } catch (error) {
      AppLogger.error("Friend remove:", error);
      return {
        success: false,
        error: "Fail remove friend",
      };
    }
  }
}
