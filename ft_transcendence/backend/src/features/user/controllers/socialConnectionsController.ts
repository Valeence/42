import { FastifyRequest, FastifyReply } from "fastify";
import { FriendConnectionsService } from "../services/socialConnectionsService.js";
import { AppLogger } from "../../../utils/logger.js";

export class FriendConnectionsController {
  static async addConnection(request: FastifyRequest, response: FastifyReply) {
    try {
      const user = request.user!;
      const { userId } = request.body as { userId: number };

      if (!userId) {
        return response.status(400).send({ error: "Friend ID required" });
      }

      const result = await FriendConnectionsService.createFriendship(user.userId, userId);

      if (!result.success) {
        return response.status(400).send({ error: result.error });
      }

      response.send({
        message: "Friend added successfully",
        data: result.data,
      });
    } catch (error) {
      AppLogger.error("Add friend error:", error);
      response.status(500).send({ error: "Failed to add friend" });
    }
  }

  static async listConnections(
    request: FastifyRequest,
    response: FastifyReply,
  ) {
    try {
      const user = request.user!;
      const friends = await FriendConnectionsService.listFriendships(user.userId);
      response.send(friends);
    } catch (error) {
      AppLogger.error("Get friends list error:", error);
      response.status(500).send({ error: "Failed to get friends list" });
    }
  }

  static async removeConnection(
    request: FastifyRequest,
    response: FastifyReply,
  ) {
    try {
      const user = request.user!;
      const { friendId } = request.params as { friendId: string };

      const result = await FriendConnectionsService.deleteFriendship(
        user.userId,
        parseInt(friendId),
      );

      if (!result.success) {
        return response.status(400).send({ error: result.error });
      }

      response.send({ message: "Friend removed successfully" });
    } catch (error) {
      AppLogger.error("Remove friend error:", error);
      response.status(500).send({ error: "Failed to remove friend" });
    }
  }
}
