import type { AccountProfile, FriendshipState } from '@/types/index.js';
import { userProfileService } from '../services/userProfileService.js';
import { DevConsole } from '@/utils/devConsole.js';

export class ProfileHeader {
  constructor(
    private userData: AccountProfile,
    private ownProfileFlag: boolean,
    private friendStatus?: FriendshipState | null
  ) {}

  render(): string {
    const avatar = userProfileService.getAvatarUrl(this.userData.avatarUrl);
    return `
      <div class="bg-gray-800 rounded-lg p-6 md:p-8 mb-8">
        <div class="flex flex-col lg:flex-row items-center lg:items-start space-y-6 lg:space-y-0 lg:space-x-8">
          ${this.renderAvatar(avatar)}
          ${this.renderInfoSection()}
        </div>
      </div>
    `;
  }

  private renderAvatar(avatarUrl: string): string {
    const onlineClass = this.userData.isOnline ? 'bg-green-500' : 'bg-gray-500';
    return `
      <div class="relative flex-shrink-0">
        <img src="${avatarUrl}" alt="${this.userData.username}" class="w-24 h-24 md:w-32 md:h-32 rounded-full bg-gray-600 object-cover border-4 border-primary-500" onerror="this.src='/default.jpg'" />
        <div class="absolute bottom-1 right-1 md:bottom-2 md:right-2 w-5 h-5 md:w-6 md:h-6 ${onlineClass} rounded-full border-2 border-gray-800"></div>
      </div>
    `;
  }

  private renderInfoSection(): string {
    return `
      <div class="flex-1 w-full text-center lg:text-left">
        <div class="flex flex-col space-y-4">
          ${this.renderBasicInfo()}
          <div class="w-full">${this.ownProfileFlag ? this.renderOwnActions() : this.renderOtherActions()}</div>
        </div>
      </div>
    `;
  }

  private renderBasicInfo(): string {
    const onlineText = this.userData.isOnline ? "Online" : "Offline";
    const lastLoginText = this.userData.lastLogin
      ? `<span class="hidden sm:inline">Last Login: ${new Date(this.userData.lastLogin).toLocaleDateString()}</span>`
      : '';
    const statusDot = this.userData.isOnline ? 'bg-green-500' : 'bg-gray-500';
    return `
      <div>
        <h1 class="text-2xl md:text-3xl font-bold text-white mb-2">${this.userData.username}</h1>
        <div class="flex items-center justify-center lg:justify-start space-x-4 text-sm text-gray-400 flex-wrap gap-2">
          <span class="flex items-center">
            <div class="w-2 h-2 ${statusDot} rounded-full mr-2"></div>${onlineText}
          </span>
          ${lastLoginText}
        </div>
      </div>
    `;
  }

  private renderOwnActions(): string {
    const toggle2FA = !this.userData.googleId
      ? `
        <div class="flex items-center justify-between p-4 bg-gray-700/50 rounded-lg border border-gray-600/30">
          <div class="flex flex-col">
            <span class="text-white font-medium text-sm md:text-base">Two-Factor Authentication</span>
            <span class="text-gray-400 text-xs mt-1">Add an extra layer of security</span>
          </div>
          <label class="relative inline-flex items-center cursor-pointer">
            <input type="checkbox" id="toggle-2fa" class="sr-only peer" ${this.userData.twoFactorEnabled ? 'checked' : ''}>
            <div class="w-11 h-6 bg-gray-200 peer-focus:outline-none peer-focus:ring-4 peer-focus:ring-blue-300/20 rounded-full peer dark:bg-gray-600 peer-checked:after:translate-x-full peer-checked:after:border-white after:content-[''] after:absolute after:top-[2px] after:left-[2px] after:bg-white after:border-gray-300 after:border after:rounded-full after:h-5 after:w-5 after:transition-all dark:border-gray-600 peer-checked:bg-blue-600"></div>
          </label>
        </div>
      ` : '';

    const changePasswordBtn = !this.userData.googleId
      ? `<button id="change-password" class="action-secondary w-full py-3 px-4 text-sm font-medium flex items-center justify-center"><i class="fas fa-key mr-2"></i>Change Password</button>`
      : '';

    const googleSignIn = this.userData.googleId
      ? `<div class="mt-3 p-3 bg-blue-900/20 border border-blue-700/30 rounded-lg">
          <div class="flex items-center text-blue-400 text-sm">
            <i class="fab fa-google mr-2"></i>
            <span>Signed in with Google</span>
          </div>
        </div>`
      : '';

    return `
      <div class="space-y-4">
        ${toggle2FA}
        <div class="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-3">
          <button id="edit-profile" class="action-primary w-full py-3 px-4 text-sm font-medium flex items-center justify-center"><i class="fas fa-edit mr-2"></i>Edit Profile</button>
          ${changePasswordBtn}
        </div>
        ${googleSignIn}
      </div>
    `;
  }

  private renderOtherActions(): string {
    if (!this.friendStatus) return this.renderAddFriendOnly();
    const buttonHtml = this.friendStatus.isFriend
      ? `<button id="header-remove-friend" class="bg-red-600 hover:bg-red-700 text-white font-medium py-3 px-4 rounded-lg transition-colors w-full flex items-center justify-center text-sm"><i class="fas fa-user-minus mr-2"></i>Remove Friend</button>`
      : `<button id="header-add-friend" class="action-primary w-full py-3 px-4 text-sm font-medium flex items-center justify-center"><i class="fas fa-user-plus mr-2"></i>Add Friend</button>`;
    return `<div class="grid grid-cols-1 sm:grid-cols-1 gap-3 max-w-md mx-auto lg:mx-0">${buttonHtml}</div>`;
  }

  private renderAddFriendOnly(): string {
    return `<div class="grid grid-cols-1 sm:grid-cols-2 gap-3 max-w-md mx-auto lg:mx-0">
      <button id="header-add-friend" class="action-primary w-full py-3 px-4 text-sm font-medium flex items-center justify-center">
        <i class="fas fa-user-plus mr-2"></i>Add Friend
      </button>
    </div>`;
  }

  public bindEvents(callbacks?: {
    onEditProfile?: () => void;
    onChangePassword?: () => void;
    onFriendAction?: (action: string) => Promise<void>;
    onToggle2FA?: (enabled: boolean) => Promise<void>;
  }): void {
    if (!callbacks) return;
    if (this.ownProfileFlag) this.bindOwnProfileEvents(callbacks);
    else this.bindOtherProfileEvents(callbacks);
  }

  private bindOwnProfileEvents(callbacks: { onEditProfile?: () => void; onChangePassword?: () => void; onToggle2FA?: (enabled: boolean) => Promise<void> }) {
    document.getElementById('edit-profile')?.addEventListener('click', () => callbacks.onEditProfile?.());
    document.getElementById('change-password')?.addEventListener('click', () => callbacks.onChangePassword?.());
    if (!callbacks.onToggle2FA) return;
    const toggle = document.getElementById('toggle-2fa') as HTMLInputElement;
    toggle?.addEventListener('change', async () => {
      try { await callbacks.onToggle2FA!(toggle.checked); } 
      catch { toggle.checked = !toggle.checked; }
    });
  }

  private bindOtherProfileEvents(callbacks: { onFriendAction?: (action: string) => Promise<void> }) {
    if (callbacks.onFriendAction) {
      document.getElementById('header-add-friend')?.addEventListener('click', () => callbacks.onFriendAction!('add-friend'));
      document.getElementById('header-remove-friend')?.addEventListener('click', () => callbacks.onFriendAction!('remove-friend'));
    }
    document.getElementById('header-challenge-user')?.addEventListener('click', () => DevConsole.print('Challenge user from header - TODO: Implement'));
  }

  public bind2FAEvents(onToggle2FA?: (enabled: boolean) => Promise<void>): void {
    this.bindEvents({ onToggle2FA });
  }
}
