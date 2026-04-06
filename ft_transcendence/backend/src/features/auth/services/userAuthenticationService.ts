import {
  RegisterData,
  AuthResult,
  LoginData,
  UserFromDB,
} from "../types/userAuthenticationTypes.js";
import { TokenService } from "./tokenManagementService.js";
import { TwoFactorService } from "./securityCodeService.js";
import { serialize } from "../../../utils/serialize.js";
import databaseClient from "../../../db/index.js";
import bcrypt from "bcrypt";
import crypto from "crypto";
import { AppLogger } from "../../../utils/logger.js";

export function emailAlreadyRegistered(email: string): boolean {
  const stmt = databaseClient.prepare("SELECT id FROM users WHERE email = ?");
  const user = stmt.get(email);
  return user !== undefined;
}

export function usernameAlreadyRegistered(username: string): boolean {
  const stmt = databaseClient.prepare("SELECT id FROM users WHERE username = ?");
  const user = stmt.get(username);
  return user !== undefined;
}

function fetchUserByEmail(email: string): UserFromDB | null {
  const stmt = databaseClient.prepare("SELECT * FROM users WHERE email = ?");
  const userRaw = stmt.get(email) as any | undefined;
  return userRaw ? serialize<UserFromDB>(userRaw) : null;
}

function fetchUserByUsername(username: string): UserFromDB | null {
  const stmt = databaseClient.prepare("SELECT * FROM users WHERE username = ?");
  const userRaw = stmt.get(username) as any | undefined;
  return userRaw ? serialize<UserFromDB>(userRaw) : null;
}

export class AuthenticationService {
  static async loginWithTwoFactor(userId: number, code: string): Promise<AuthResult> {
    await TwoFactorService.validateSecurityCode(userId, code, false);

    const stmt = databaseClient.prepare("SELECT * FROM users WHERE id = ?");
    const user = stmt.get(userId) as UserFromDB | undefined;

    if (!user) throw new Error("User not found after 2FA");

    const updateStmt = databaseClient.prepare(
      "UPDATE users SET last_login = CURRENT_TIMESTAMP, is_online = 1 WHERE id = ?",
    );
    updateStmt.run(user.id);

    const tokenBundle = TokenService.issueTokenPair(user.id, user.username);

    TokenService.storeSession(user.id, tokenBundle.refreshToken);

    const userReturn = {
      id: user.id,
      username: user.username,
      email: user.email,
      lastLogin: new Date().toISOString(),
    };

    return {
      success: true,
      user: userReturn,
      accessToken: tokenBundle.accessToken,
      refreshToken: tokenBundle.refreshToken,
    };
  }

  static async registerUser(userData: RegisterData): Promise<AuthResult> {
    try {
      if (emailAlreadyRegistered(userData.email))
        return {
          success: false,
          error: "Email already use",
        };

      if (usernameAlreadyRegistered(userData.username))
        return {
          success: false,
          error: "Username already use",
        };

      const hashedPassword = await bcrypt.hash(userData.password, 10);

      const stmt = databaseClient.prepare(
        "INSERT INTO USERS (username, email, password, is_online, last_login) VALUES (?, ?, ?, 1, CURRENT_TIMESTAMP)",
      );
      const result = stmt.run(
        userData.username,
        userData.email,
        hashedPassword,
      );

      const userId = result.lastInsertRowid as number;

      const tokenBundle = TokenService.issueTokenPair(userId, userData.username);

      TokenService.storeSession(userId, tokenBundle.refreshToken);

      const user = {
        id: userId,
        username: userData.username,
        email: userData.email,
        avatar_url: null,
        isOnline: true,
        twoFactorEnabled: false,
        createdAt: new Date().toISOString(),
        stats: {
          wins: 0,
          losses: 0,
          totalGames: 0,
          winRate: 0,
        },
      };

      return {
        success: true,
        user: user,
        accessToken: tokenBundle.accessToken,
        refreshToken: tokenBundle.refreshToken,
      };
    } catch (error) {
      AppLogger.error("Register error: ", error);
      return {
        success: false,
        error: "Registration failed",
      };
    }
  }

  static async loginUser(loginData: LoginData): Promise<AuthResult> {
    try {
      const stmt = databaseClient.prepare(
        "SELECT * FROM users WHERE email = ? OR username = ?",
      );
      const userRaw = stmt.get(loginData.username, loginData.username) as
        | UserFromDB
        | undefined;

      if (!userRaw)
        return {
          success: false,
          error: "Invalid identifier",
        };

      const user = serialize<UserFromDB>(userRaw);

      const validPassword = await bcrypt.compare(
        loginData.password,
        user.password,
      );

      if (!validPassword)
        return {
          success: false,
          error: "Invalid password",
        };

      if (user.twoFactorEnabled) {
        const getCode = await TwoFactorService.sendVerificationCode(user.id);
        if (!getCode.success)
          return { success: getCode.success, error: getCode.message };
        return {
          success: false,
          error: "2FA_REQUIRED",
          user: {
            id: user.id,
            username: user.username,
            email: user.email,
            twoFactorEnabled: user.twoFactorEnabled,
          },
        };
      }

      const updateStmt = databaseClient.prepare(
        "UPDATE users SET last_login = CURRENT_TIMESTAMP, is_online = 1 WHERE id = ?",
      );
      updateStmt.run(user.id);

      const tokenBundle = TokenService.issueTokenPair(user.id, user.username);

      TokenService.storeSession(user.id, tokenBundle.refreshToken);

      const userReturn = {
        id: user.id,
        username: user.username,
        email: user.email,
        avatarUrl: user.avatar,
        isOnline: user.isOnline,
        lastLogin: new Date().toISOString(),
      };

      return {
        success: true,
        user: userReturn,
        accessToken: tokenBundle.accessToken,
        refreshToken: tokenBundle.refreshToken,
      };
    } catch (error) {
      AppLogger.error("Login error:", error);
      return {
        success: false,
        error: "Login failed",
      };
    }
  }

  static async logoutUserSession(refreshToken: string): Promise<void> {
    try {
      const sessionCheck = TokenService.validateSession(refreshToken);

      if (sessionCheck.valid && sessionCheck.userId) {
        const updateStmt = databaseClient.prepare(
          "UPDATE users SET is_online = 0 WHERE id = ?",
        );
        updateStmt.run(sessionCheck.userId);
      }

      const delete2FA = databaseClient.prepare(
        "DELETE FROM two_factor_tokens where user_id = ?",
      );
      const cleanToken = delete2FA.run(sessionCheck.userId);
      TokenService.removeSession(refreshToken);
    } catch (error) {
      AppLogger.error("Logout service error:", error);
      throw error;
    }
  }

  static async processOAuthUser(userData: UserFromDB): Promise<AuthResult> {
    const userExist = fetchUserByEmail(userData.email);

    if (userExist && userExist.googleId) {
      const serializedUser = serialize(userExist);
      const updateStmt = databaseClient.prepare(
        "UPDATE users SET last_login = CURRENT_TIMESTAMP, is_online = 1 WHERE id = ?",
      );
      updateStmt.run(userExist.id);
      const tokenBundle = TokenService.issueTokenPair(
        userExist.id,
        userExist.username,
      );
      TokenService.storeSession(userExist.id, tokenBundle.refreshToken);
      const userReturn = {
        id: userExist.id,
        username: userExist.username,
        email: userExist.email,
        lastLogin: new Date().toISOString(),
      };

      return {
        success: true,
        user: userReturn,
        accessToken: tokenBundle.accessToken,
        refreshToken: tokenBundle.refreshToken,
      };
    }
    const userName = fetchUserByUsername(userData.username);
    if (!userName && !userExist?.email) {
      const randomPassword = crypto.randomBytes(16).toString("hex");
      const hashedPassword = await bcrypt.hash(randomPassword, 10);
      const stmt = databaseClient.prepare(
        "INSERT INTO USERS (username, email, password, google_id, last_login, is_online) VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP, 1) ",
      );
      const res = stmt.run(
        userData.username,
        userData.email,
        hashedPassword,
        userData.googleId,
      );

      const userId = res.lastInsertRowid as number;
      const tokenBundle = TokenService.issueTokenPair(userId, userData.username);
      TokenService.storeSession(userId, tokenBundle.refreshToken);

      const userReturn = {
        id: userId,
        username: userData.username,
        email: userData.email,
        password: hashedPassword,
        lastLogin: new Date().toISOString(),
      };

      return {
        success: true,
        user: userReturn,
        accessToken: tokenBundle.accessToken,
        refreshToken: tokenBundle.refreshToken,
      };
    }
    throw new Error("Error Oauth login");
  }
}
