import {
  UserTwoFactor,
  TwoFactorToken,
} from "../types/userAuthenticationTypes.js";
import nodemailer from "nodemailer";
import databaseClient from "../../../db/index.js";
import crypto from "crypto";
import bcrypt from "bcrypt";
import "dotenv/config";
import { AppLogger } from "../../../utils/logger.js";

export class TwoFactorService {
  static async fetchUserRecord(userId: number): Promise<UserTwoFactor> {
    const stmt = databaseClient.prepare(
      "SELECT id, email, two_factor_enabled, google_id FROM users where id = ?",
    );
    const user = stmt.get(userId) as any | undefined;
    if (!user) throw new Error("User infos 2FA not found");
    return {
      id: user.id,
      email: user.email,
      twoFactorEnabled: user.two_factor_enabled,
      googleId: user.google_id,
    };
  }

  static generateVerificationCode(): string {
    const randomBytes = crypto.randomBytes(3);
    const randomNumber = randomBytes.readUIntBE(0, 3);
    return (100000 + (randomNumber % 900000)).toString();
  }

  static async dispatchEmail(email: string, code: string): Promise<void> {
    const transporter = nodemailer.createTransport({
      host: "smtp.gmail.com",
      port: 587,
      secure: false,
      auth: {
        user: process.env.MAIL_2FA,
        pass: process.env.PASS_2FA,
      },
    });
    await transporter.sendMail({
      from: `Transcendence <${process.env.MAIL_2FA}>`,
      to: email,
      subject: "2FA code",
      text: `Hello,\n\nYour verification code is: ${code}\n\nThis code will expire in 10 minutes.\n\nPlease do not share this code with anyone.\n`,
    });
  }

  static async persistTwoFactorToken(userId: number, code: string): Promise<void> {
    const codeHash = await bcrypt.hash(code, 10);
    const expiresAt = new Date(Date.now() + 10 * 60 * 1000);
    const stmt = databaseClient.prepare(`
            INSERT OR REPLACE INTO security_codes 
            (user_id, verification_code, expires_at, attempt_count)
            VALUES (?, ?, ?, 0)`);
    const res = stmt.run(userId, codeHash, expiresAt.toISOString());
    if (!res) throw new Error("Create Token failed storeTwoFactor");
    AppLogger.log("GET userinfo Two Factor: ", res);
  }

  static async sendVerificationCode(
    userId: number,
  ): Promise<{ success: boolean; message: string }> {
    const user = await this.fetchUserRecord(userId);
    const code = this.generateVerificationCode();
    if (!code) throw new Error("Generate random pass 2FA failed");
    await this.persistTwoFactorToken(user.id, code);
    await this.dispatchEmail(user.email, code);

    return { success: true, message: "2FA code sent by email" };
  }

  static async fetchSecurityEntry(userId: number): Promise<TwoFactorToken> {
    const stmt = databaseClient.prepare("SELECT * FROM security_codes WHERE user_id = ? ");
    const verification_codeData = stmt.get(userId) as any;
    if (!verification_codeData)
      throw new Error("Error getUSerInfo query databaseClient 2FA");
    return {
      id: verification_codeData.user_id,
      verification_code: verification_codeData.verification_code,
      expiresAt: verification_codeData.expires_at,
      attempt_count: verification_codeData.attempt_count,
    } as TwoFactorToken;
  }

  static async validateSecurityCode(
    userId: number,
    code: string,
    disabled: boolean,
  ): Promise<{ success: boolean; message: string }> {
    const stored = await this.fetchSecurityEntry(userId);

    if (stored.expiresAt < new Date(Date.now())) {
      throw new Error("Code expired for 2FA");
    }

    if (stored.attempt_count >= 2) {
      console.error("ERROR TWOFA", stored.attempt_count);
      throw new Error("Too many failed attempts");
    }

    const isValidCode = await bcrypt.compare(code, stored.verification_code);
    if (!isValidCode) {
      const stmtTry = databaseClient.prepare(
        "UPDATE security_codes SET attempt_count = attempt_count + 1 WHERE user_id = ?",
      );
      stmtTry.run(stored.id);
      throw new Error("Incorrect code");
    }

    const user = await this.fetchUserRecord(userId);
    if (!user.twoFactorEnabled) {
      const stmt = databaseClient.prepare(
        "UPDATE users SET two_factor_enabled = 1 WHERE id = ?",
      );
      stmt.run(user.id);
    } else if (user.twoFactorEnabled && disabled) {
      const stmt = databaseClient.prepare(
        "UPDATE users SET two_factor_enabled = 0 WHERE id = ?",
      );
      stmt.run(user.id);
    }

    const deleteStmt = databaseClient.prepare(
      "DELETE FROM security_codes WHERE user_id = ?",
    );
    deleteStmt.run(userId);

    AppLogger.log(`2FA called for user: ${user.email}`);
    return {
      success: true,
      message: disabled
        ? "2FA disabled successfully"
        : "2FA validate successfully",
    };
  }
}
