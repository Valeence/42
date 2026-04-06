import { FastifyRequest, FastifyReply } from "fastify";
import { UserProfileService } from "../services/userProfileService.js";
import {
  UpdateProfileData,
  ChangePassword,
} from "../../auth/types/userAuthenticationTypes.js";
import { StatsService } from "../../stats/services/playerStatsService.js";
import { AppLogger } from "../../../utils/logger.js";

export class UserProfileController {
  static async getAuthenticatedProfile(request: FastifyRequest, response: FastifyReply) {
    try {
      const user = request.user!;

      const profile = await UserProfileService.getUserDataFromDb(user.userId);
      if (!profile) return response.status(404).send({ error: "User not found" });

      AppLogger.log("Profile data:", profile);
      response.send(profile);
    } catch (error) {
      AppLogger.error("Get profile error:", error);
      response.status(500).send({ error: "Failed to get profile" });
    }
  }

  static async changePassword(request: FastifyRequest, response: FastifyReply) {
    try {
      const user = request.user!;
      const changePassword = request.body as ChangePassword;

      AppLogger.log("Change password request:", changePassword);

      const result = await UserProfileService.changePassword(
        user.userId,
        changePassword,
      );
      if (!result.success)
        return response.status(404).send({ error: "update password error" });

      response.send({ message: result.message });
    } catch (error) {
      AppLogger.error("Change password error:", error);
      response.status(500).send({ error: "Failed to change password" });
    }
  }

  static async updateProfile(request: FastifyRequest, response: FastifyReply) {
    try {
      const user = request.user!;

      let updateData: UpdateProfileData = {};

      if (request.isMultipart()) {
        const parts = request.parts();

        for await (const part of parts) {
          if (part.type === "file" && part.fieldname === "avatar") {
            try {
              const avatarPath = await UserProfileService.saveAvatarFile(
                part,
                user.userId,
              );
              updateData.avatarUrl = avatarPath;
            } catch (avatarError) {
              throw avatarError;
            }
          } else if (part.type === "field") {
            const value = part.value as string;

            if (part.fieldname === "username" && value.trim()) {
              const username = value.trim();
              if (username.length < 3) {
                return response
                  .status(400)
                  .send({
                    error: "Username must be at least 3 characters long",
                  });
              }
              if (username.length > 20) {
                return response
                  .status(400)
                  .send({
                    error: "Username must be at most 20 characters long",
                  });
              }
              if (!/^[a-zA-Z0-9_]+$/.test(username)) {
                return response
                  .status(400)
                  .send({
                    error:
                      "Username can only contain letters, numbers and underscores",
                  });
              }
              updateData.username = username;
            } else if (part.fieldname === "email" && value.trim()) {
              const email = value.trim();
              if (email.length > 255) {
                return response.status(400).send({ error: "Email is too long" });
              }
              if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email)) {
                return response
                  .status(400)
                  .send({ error: "Invalid email format" });
              }
              updateData.email = email;
            }
          }
        }
      }

      if (!updateData.username && !updateData.email && !updateData.avatarUrl) {
        return response.status(400).send({ error: "No update data provided" });
      }

      const result = await UserProfileService.updateUserProfile(
        user.userId,
        updateData,
      );

      if (!result.success) {
        return response.status(400).send({ error: result.error });
      }

      response.send({
        message: "User profile updated successfully",
        user: result.user,
      });
    } catch (error) {
      AppLogger.error("Update profile controller error:", error);
      response.status(500).send({ error: "Failed to update profile" });
    }
  }

  static async listAllUsers(request: FastifyRequest, response: FastifyReply) {
    try {
      const user = request.user!;
      const users = await UserProfileService.getAllUsernames(user.userId);
      response.send(users);
    } catch (error) {
      AppLogger.error("Get all users controller error:", error);
      response.status(500).send({ error: "Failed to get users" });
    }
  }

  static async searchProfiles(request: FastifyRequest, response: FastifyReply) {
    try {
      const query = (request.query as any).q;

      if (!query || query.length < 2) {
        return response
          .status(400)
          .send({ error: "Query must be at least 2 characters long" });
      }

      const users = await UserProfileService.searchUsers(query);
      response.send(users);
    } catch (error) {
      AppLogger.error("Search users controller error:", error);
      response.status(500).send({ error: "Failed to search users" });
    }
  }

  static async getProfileById(request: FastifyRequest, response: FastifyReply) {
    try {
      const { id } = request.params as { id: string };
      const userId = parseInt(id);

      const user = await UserProfileService.getUserDataFromDb(userId);

      if (!user) {
        return response.status(404).send({ error: "User not found" });
      }

      response.send(user);
    } catch (error) {
      AppLogger.error("Get user by ID error:", error);
      response.status(500).send({ error: "Failed to get user" });
    }
  }

  static async getMatchHistory(request: FastifyRequest, response: FastifyReply) {
    try {
      const user = request.user!;
      const limit = 10 as number;

      const history = StatsService.getUserMatchHistory(user.userId, limit);

      response.send(history);
    } catch (error) {
      AppLogger.error("Get match history error:", error);
      response.status(500).send({ error: "Failed to get match history" });
    }
  }
}
