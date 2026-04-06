import { FastifyInstance } from "fastify";
import { FriendConnectionsController } from "../controllers/socialConnectionsController.js";

export default async function registerFriendRoutes(server: FastifyInstance) {
  server.get("/list", FriendConnectionsController.listConnections);
  server.post("/add", FriendConnectionsController.addConnection);
  server.delete(
    "/remove/:friendId",
    FriendConnectionsController.removeConnection,
  ); // '/:friendId
}
