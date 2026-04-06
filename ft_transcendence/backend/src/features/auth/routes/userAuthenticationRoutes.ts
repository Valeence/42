import { FastifyInstance } from "fastify";
import {
  loginSchema,
  registerSchema,
} from "../schemas/userAuthenticationSchema.js";
import { UserAuthController } from "../controllers/userAuthenticationController.js";
import { GoogleAuthController } from "../controllers/socialLoginController.js";

export default async function registerAuthRoutes(server: FastifyInstance) {
  server.post(
    "/register",
    { schema: registerSchema },
    UserAuthController.registerUser,
  );
  server.post(
    "/login",
    { schema: loginSchema },
    UserAuthController.loginUser,
  );
  server.post("/loginWith2FA", UserAuthController.loginWithTwoFactor);
  server.get("/oauth/google", GoogleAuthController.startGoogleLoginFlow);
  server.get(
    "/oauth/google/callback",
    GoogleAuthController.completeGoogleLogin,
  );

  server.post("/logout", UserAuthController.logoutUser);
}
