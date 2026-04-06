import databaseClient from "../../../db/index.js";
import bcrypt from "bcrypt";
import {
  UserData,
  UpdateProfileData,
  UpdateResult,
} from "../../auth/types/userAuthenticationTypes.js";
import { StatsService } from "../../stats/services/playerStatsService.js";
import { serialize } from "../../../utils/serialize.js";
import { ChangePassword } from "../../auth/types/userAuthenticationTypes.js";
import { AppLogger } from "../../../utils/logger.js";

export class UserProfileService {
  static async getUserDataFromDb(userId: number): Promise<UserData | null> {
    const stmt = databaseClient.prepare(`
                SELECT id, username, email, avatar_url, created_at, last_login, is_online, google_id, two_factor_enabled
                FROM users WHERE id = ?
            `);
    const userDataRaw = stmt.get(userId) as any | undefined;
    if (!userDataRaw) return null;

    const userData = serialize(userDataRaw);
    const stats = StatsService.getUserStats(userId);

    const userProfile: UserData = {
      id: userData.id,
      username: userData.username,
      email: userData.email,
      avatarUrl: userData.avatarUrl,
      isOnline: userData.isOnline,
      twoFactorEnabled: userData.twoFactorEnabled,
      createdAt: userData.createdAt,
      lastLogin: userData.lastLogin,
      googleId: userData.googleId,
      stats: stats,
    };
    AppLogger.log("User profile retrieved:", userProfile);
    return userProfile;
  }

  static async updateUserProfile(
    userId: number,
    updateData: UpdateProfileData,
  ): Promise<UpdateResult> {
    const transaction = databaseClient.transaction(() => {
      try {
        if (updateData.username) {
          const stmt = databaseClient.prepare(
            "SELECT id FROM users WHERE username = ? AND id != ?",
          );
          const existingUser = stmt.get(updateData.username, userId);
          if (existingUser) throw new Error("Username already taken");
        }
        if (updateData.email) {
          const stmt = databaseClient.prepare(
            "SELECT id FROM users WHERE email = ? AND id != ?",
          );
          const existingUser = stmt.get(updateData.email, userId);
          if (existingUser) throw new Error("Email already taken");
        }

        const fieldsToUpdate: string[] = [];
        const values: any[] = [];

        if (updateData.username) {
          fieldsToUpdate.push("username = ?");
          values.push(updateData.username);
        }
        if (updateData.email) {
          fieldsToUpdate.push("email = ?");
          values.push(updateData.email);
        }
        if (updateData.avatarUrl !== undefined) {
          // set null/empty
          fieldsToUpdate.push("avatar_url = ?");
          values.push(updateData.avatarUrl);
        }
        if (fieldsToUpdate.length === 0) throw new Error("No fields to update");
        values.push(userId);

        const updateQuery = `UPDATE users SET ${fieldsToUpdate.join(", ")} WHERE id = ?`;
        const updateStmt = databaseClient.prepare(updateQuery);
        const result = updateStmt.run(...values);
        if (result.changes === 0) throw "User not found";

        const selectStmt = databaseClient.prepare(`
                    SELECT id, username, email, avatar_url, created_at, last_login, is_online, google_id, two_factor_enabled
                    FROM users WHERE id = ?
                `);

        const updatedUserRaw = selectStmt.get(userId) as any;
        if (!updatedUserRaw)
          throw new Error("Failed to retrieve updated user data");

        const updatedUser = serialize(updatedUserRaw);
        const stats = StatsService.getUserStats(userId);

        const formattedUser: UserData = {
          id: updatedUser.id,
          username: updatedUser.username,
          email: updatedUser.email,
          avatarUrl: updatedUser.avatarUrl,
          isOnline: updatedUser.isOnline,
          twoFactorEnabled: updatedUser.twoFactorEnabled,
          createdAt: updatedUser.createdAt,
          lastLogin: updatedUser.lastLogin,
          googleId: updatedUser.googleId,
          stats: stats,
        };

        return {
          success: true,
          user: formattedUser,
        };
      } catch (error) {
        AppLogger.error("Transaction error:", error);
        throw error;
      }
    });
    try {
      return transaction() as UpdateResult;
    } catch (error) {
      AppLogger.error("Update profile error:", error);
      return {
        success: false,
        error: (error as Error).message,
      };
    }
  }

  static async getAllUsernames(userId: number): Promise<UserData[]> {
    try {
      const stmt = databaseClient.prepare(`
                SELECT id, username, avatar_url, is_online
                FROM users
                WHERE id != ?
                ORDER BY username ASC
            `);

      const usersRaw = stmt.all(userId) as any[];

      const users: UserData[] = usersRaw.map((userRaw) => {
        const userData = serialize(userRaw);
        const stats = StatsService.getUserStats(userData.id);

        return {
          id: userData.id,
          username: userData.username,
          email: userData.email,
          avatarUrl: userData.avatarUrl,
          isOnline: userData.isOnline,
          twoFactorEnabled: false,
          createdAt: userData.createdAt,
          lastLogin: userData.lastLogin,
          googleId: userData.googleId,
          stats: stats,
        };
      });

      return users;
    } catch (error) {
      AppLogger.error("Get all users error:", error);
      return [];
    }
  }

  static async searchUsers(query: string): Promise<UserData[]> {
    try {
      const stmt = databaseClient.prepare(`
                SELECT id, username, email, avatar_url, created_at, last_login, is_online
                FROM users
                WHERE username LIKE ? OR email LIKE ?
                ORDER BY username ASC
                LIMIT 20
            `);

      const searchPattern = `${query}%`;
      const usersRaw = stmt.all(searchPattern, searchPattern) as any[];

      const users: UserData[] = usersRaw.map((userRaw) => {
        const userData = serialize(userRaw);
        const stats = StatsService.getUserStats(userData.id);

        return {
          id: userData.id,
          username: userData.username,
          email: userData.email,
          avatarUrl: userData.avatarUrl,
          isOnline: userData.isOnline,
          twoFactorEnabled: false,
          createdAt: userData.createdAt,
          lastLogin: userData.lastLogin,
          googleId: userData.googleId,
          stats: stats,
        };
      });

      return users;
    } catch (error) {
      AppLogger.error("Search users error:", error);
      return [];
    }
  }

  static async changePassword(
    userId: number,
    changePassword: ChangePassword,
  ): Promise<{ success: boolean; message?: string; error?: string }> {
    try {
      if (changePassword.currentPassword === changePassword.newPassword) {
        return {
          success: false,
          error: "New password need to be different from old password",
        };
      }

      if (changePassword.newPassword.length < 8) {
        return { success: false, error: "Password must be 8 character long" };
      }

      const passwordRegex =
        /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$/;
      if (!passwordRegex.test(changePassword.newPassword)) {
        return {
          success: false,
          error:
            "Password must contain 1 lower case, 1 upper case, 1 number, 1 symbole",
        };
      }

      const stmt = databaseClient.prepare("SELECT password FROM users WHERE id = ?");
      const dbPassword = stmt.get(userId) as { password: string } | undefined;
      if (!dbPassword) {
        return { success: false, error: "User not found" };
      }

      const isCurrentPasswordValid = await bcrypt.compare(
        changePassword.currentPassword,
        dbPassword.password,
      );
      if (!isCurrentPasswordValid) {
        return { success: false, error: "Current password incorrect" };
      }

      const hashedNewPassword = await bcrypt.hash(
        changePassword.newPassword,
        10,
      );
      const updateStmt = databaseClient.prepare(
        "UPDATE users SET password = ?, last_login = CURRENT_TIMESTAMP WHERE id = ?",
      );
      const result = updateStmt.run(hashedNewPassword, userId);
      if (result.changes === 0) {
        return { success: false, error: "Failed update password" };
      }

      return { success: true, message: "Password update success" };
    } catch (error) {
      AppLogger.error("Change password service error:", error);
      return { success: false, error: "Internal error" };
    }
  }

  static async saveAvatarFile(part: any, userId: number): Promise<string> {
    const fs = await import("fs/promises");
    const path = await import("path");

    if (!part.mimetype?.startsWith("image/")) {
      throw new Error("Invalid file type. Only images are allowed.");
    }

    const maxSize = 5 * 1024 * 1024;
    let fileSize = 0;

    try {
      const stmt = databaseClient.prepare("SELECT avatar_url FROM users WHERE id = ?");
      const currentUser = stmt.get(userId) as any;

      if (currentUser?.avatar_url) {
        const oldAvatarPath = path.join(
          process.cwd(),
          currentUser.avatar_url.replace(/^\//, ""),
        );

        try {
          await fs.access(oldAvatarPath);
          await fs.unlink(oldAvatarPath);
          AppLogger.log(`Ancien avatar supprimé: ${oldAvatarPath}`);
        } catch (error) {
          AppLogger.log(
            `Ancien avatar non trouvé ou déjà supprimé: ${oldAvatarPath}`,
          );
        }
      }
    } catch (error) {
      AppLogger.error("Erreur lors de la suppression de l'ancien avatar:", error);
    }

    const uploadsDir = path.join(process.cwd(), "uploads", "avatars");
    await fs.mkdir(uploadsDir, { recursive: true });

    const fileExtension = part.mimetype.split("/")[1];
    const fileName = `avatar_${userId}_${Date.now()}.${fileExtension}`;
    const filePath = path.join(uploadsDir, fileName);

    const writeStream = await fs.open(filePath, "w");

    try {
      for await (const chunk of part.file) {
        fileSize += chunk.length;
        if (fileSize > maxSize) {
          await writeStream.close();
          await fs.unlink(filePath);
          throw new Error("File too large. Maximum size is 5MB.");
        }
        await writeStream.write(chunk);
      }
    } finally {
      await writeStream.close();
    }

    return `/uploads/avatars/${fileName}`;
  }
}
