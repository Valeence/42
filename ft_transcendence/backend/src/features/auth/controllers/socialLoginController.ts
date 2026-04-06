import { FastifyRequest, FastifyReply } from "fastify";
import { AuthenticationService } from "../services/userAuthenticationService.js";
import { CookieManager } from "../services/sessionCookieService.js";
import { UserFromDB } from "../types/userAuthenticationTypes.js";
import { AppLogger } from "../../../utils/logger.js";

export class GoogleAuthController {
  private static readonly exchangeTokenEndpoint =
    "https://oauth2.googleapis.com/token";
  private static readonly authorizationEndpoint =
    "https://accounts.google.com/o/oauth2/v2/auth";
  private static readonly googleUserEndpoint =
    "https://www.googleapis.com/oauth2/v3/userinfo";

  static {
    if (
      !process.env.GOOGLE_CLIENT_ID ||
      !process.env.GOOGLE_CLIENT_SECRET ||
      !process.env.GOOGLE_REDIRECT_URI ||
      !process.env.API_URL_FRONT
    ) {
      AppLogger.error("Missing environnement variable for oauthController Class");
      throw new Error("Missing required Google OAuth environment variables");
    }
  }

  static async startGoogleLoginFlow(
    request: FastifyRequest,
    response: FastifyReply,
  ) {
    try {
      const authUrl = new URL(GoogleAuthController.authorizationEndpoint);

      authUrl.searchParams.set("client_id", process.env.GOOGLE_CLIENT_ID!);
      const redirectUri =
        process.env.NODE_ENV === "production"
          ? process.env.GOOGLE_REDIRECT_URI!
          : `http://localhost:${process.env.PORT}/api/auth/oauth/google/callback`;
      authUrl.searchParams.set("redirect_uri", redirectUri);
      authUrl.searchParams.set("response_type", "code");
      authUrl.searchParams.set("scope", "profile email");
      authUrl.searchParams.set("access_type", "offline");
      authUrl.searchParams.set("prompt", "select_account");

      AppLogger.log("Redirecting to:", authUrl.toString());

      return response.redirect(authUrl.toString());
    } catch (error) {
      AppLogger.error("Google OAuth redirect error:", error);
      return response
        .status(500)
        .send({ error: "Google OAuth redirect failed" });
    }
  }

  static async completeGoogleLogin(
    request: FastifyRequest,
    response: FastifyReply,
  ) {
    const { code, error } = request.query as { code?: string; error?: string };
    try {
      if (error) {
        AppLogger.log("OAuth error received: ", error);
        return response.redirect(
          `${process.env.API_URL_FRONT}login?error=oauth_failed`,
        );
      }

      if (!code)
        return response.status(400).send("Code required for Google OAuth2");

      const exchangeResult =
        await GoogleAuthController.exchangeAuthCodeForToken(code);
      AppLogger.log("data received from exchange code: ", exchangeResult);

      const userData = await GoogleAuthController.fetchGoogleProfile(
        exchangeResult.token.access_token,
      );
      AppLogger.log("userData: ", userData);

      const username = userData.returnUser.email.split("@")[0];

      const oauth2Data: UserFromDB = {
        username,
        email: userData.returnUser.email,
        googleId: userData.returnUser.sub,
      } as UserFromDB;

      const authResult = await AuthenticationService.processOAuthUser(oauth2Data);

      CookieManager.setAuthCookies(
        response,
        authResult.accessToken!,
        authResult.refreshToken!,
      );
      return response.redirect(`${process.env.API_URL_FRONT}`);
    } catch (error) {
      if (error instanceof Error) AppLogger.error(error.message);
      AppLogger.error("Google generate error:", error);
      return response.redirect(
        `${process.env.API_URL_FRONT}login?error=oauth_failed`,
      );
    }
  }

  static async exchangeAuthCodeForToken(code: string) {
    const redirectUri =
      process.env.NODE_ENV === "production"
        ? process.env.GOOGLE_REDIRECT_URI!
        : `http://localhost:${process.env.PORT}/api/auth/oauth/google/callback`;

    const params = new URLSearchParams({
      code,
      client_id: process.env.GOOGLE_CLIENT_ID!,
      client_secret: process.env.GOOGLE_CLIENT_SECRET!,
      redirect_uri: redirectUri,
      grant_type: "authorization_code",
    });

    const token = await fetch(GoogleAuthController.exchangeTokenEndpoint, {
      method: "POST",
      headers: {
        "Content-type": "application/x-www-form-urlencoded",
      },
      body: params.toString(),
    });
    if (!token.ok) throw new Error("Error generate token failed");
    const tokenSuccess = await token.json();
    return {
      success: true,
      message: "token generate successfully",
      token: tokenSuccess,
    };
  }

  static async fetchGoogleProfile(accessToken: string) {
    const userData = await fetch(GoogleAuthController.googleUserEndpoint, {
      headers: {
        Authorization: `Bearer ${accessToken}`,
      },
    });
    if (!userData.ok) throw new Error("Get user profile OAuth failed");
    const returnUser = await userData.json();
    return {
      success: true,
      returnUser: returnUser,
    };
  }
}
