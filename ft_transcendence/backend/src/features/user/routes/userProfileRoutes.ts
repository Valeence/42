import { FastifyInstance } from "fastify";
import { UserProfileController } from "../controllers/userProfileController.js";

export default async function registerUserProfileRoutes(server: FastifyInstance) {
  server.get("/me", UserProfileController.getAuthenticatedProfile);
  server.put("/updateProfile", UserProfileController.updateProfile);
  server.get("/users", UserProfileController.listAllUsers);
  server.get("/users/search", UserProfileController.searchProfiles);
  server.get("/profile/:id", UserProfileController.getProfileById);
  server.put("/change-password", UserProfileController.changePassword);
  server.get("/me/matches", UserProfileController.getMatchHistory);
}
