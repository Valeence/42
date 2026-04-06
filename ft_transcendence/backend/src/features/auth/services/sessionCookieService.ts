import { FastifyReply } from "fastify";

export class CookieManager {
  static setAuthCookies(
    response: FastifyReply,
    accessToken: string,
    refreshToken: string,
  ) {
    response.setCookie("accessToken", accessToken, {
      httpOnly: true,
      secure: process.env.NODE_ENV === "production",
      sameSite: process.env.NODE_ENV === "production" ? "strict" : "lax",
      maxAge: 15 * 60 * 1000,
      path: "/",
      domain: undefined,
    });

    response.setCookie("refreshToken", refreshToken, {
      httpOnly: true,
      secure: process.env.NODE_ENV === "production",
      sameSite: process.env.NODE_ENV === "production" ? "strict" : "lax",
      maxAge: 30 * 24 * 60 * 60 * 1000,
      path: "/",
      domain: undefined,
    });
  }

  static removeAuthCookies(response: FastifyReply) {
    response.clearCookie("accessToken", { path: "/" });
    response.clearCookie("refreshToken", { path: "/" });
  }
}
