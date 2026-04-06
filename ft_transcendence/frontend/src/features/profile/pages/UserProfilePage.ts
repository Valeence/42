import { userProfileService } from '../services/userProfileService';
import { userAuthenticationService } from '@/features/auth/services/userAuthenticationService';
import { socialConnectionsService } from '../services/socialConnectionsService';
import { securityCodeService } from '@/features/auth/services/securityCodeService';
import { DevConsole } from '@/utils/devConsole.js'; 
import { ProfileHeader } from '../components/UserProfileHeader';
import { StatsCard } from '../components/PlayerStatsCard';
import { FriendsSection } from '../components/SocialConnectionsSection';
import { MatchHistoryCard } from '../components/GameHistoryCard';
import { EditProfileModal } from '../components/ProfileEditModal';
import { ChangePasswordModal } from '../components/PasswordUpdateModal';
import { TwoFactorAuthModal } from '@/features/auth/components/TwoFactorAuthModal';
import { ProfileLayout } from '../components/UserProfileLayout';
import type {
  AccountProfile,
  CompletedMatchRecord,
  FriendProfile,
  FriendshipState,
  ProfileRenderSections
} from '@/types/index.js';

export class ProfilePage {
  private currentUser: AccountProfile | null = null;
  private matchHistory: CompletedMatchRecord[] = [];
  private friends: FriendProfile[] = [];
  private currentUserId: string | null = null;
  private friendshipStatus: FriendshipState | null = null;
  private onLanguageChange: (() => void) | null = null;
  private onFriendsUpdate: (() => void) | null = null;

  mount(containerSelector: string): void {
    const container = document.querySelector(containerSelector);
    if (!container) return;

    this.currentUserId = window.location.pathname.split('/profile/')[1] || null;

    this.cleanupListeners();
    this.fetchUserData(container);

    this.onLanguageChange = () => {
      const target = document.querySelector('#page-content');
      target && this.render(target);
    };
    window.addEventListener('languageChanged', this.onLanguageChange);

    this.onFriendsUpdate = async () => await this.refreshFriendsData();
    window.addEventListener('friendsUpdated', this.onFriendsUpdate);
  }

  destroy(): void {
    this.cleanupListeners();
  }

  private cleanupListeners(): void {
    if (this.onLanguageChange) {
      window.removeEventListener('languageChanged', this.onLanguageChange);
      this.onLanguageChange = null;
    }
    if (this.onFriendsUpdate) {
      window.removeEventListener('friendsUpdated', this.onFriendsUpdate);
      this.onFriendsUpdate = null;
    }
  }

  private async fetchUserData(container: Element): Promise<void> {
    this.renderLoading(container);
    try {
      this.currentUser = await userProfileService.getUserProfile(this.currentUserId);
      if (!this.currentUser) {
        this.renderError(container, 'User not found');
        return;
      }

      this.friends = await socialConnectionsService.getFriends();
      if (this.currentUserId) {
        this.friendshipStatus = this.determineFriendshipStatus(parseInt(this.currentUserId));
      }
      if (!this.currentUserId) {
        this.matchHistory = await userProfileService.getMatchHistory(this.currentUserId);
      }

      this.render(container);
    } catch (err) {
      DevConsole.reportError('Error fetching profile data:', err);
      this.renderError(container, 'Failed to load profile');
    }
  }

  private async refreshFriendsData(): Promise<void> {
    try {
      this.friends = await socialConnectionsService.getFriends();
      if (this.currentUserId) {
        this.friendshipStatus = this.determineFriendshipStatus(parseInt(this.currentUserId));
      }
      const container = document.querySelector('#page-content');
      container && this.render(container);
    } catch (err) {
      DevConsole.reportError('Error refreshing friends:', err);
    }
  }

  private determineFriendshipStatus(userId: number): FriendshipState {
    const isFriend = this.friends.some(f => f.id === userId);
    DevConsole.print('Friendship check:', { userId, isFriend, friendsCount: this.friends.length });
    return { isFriend };
  }

  private render(container: Element): void {
    if (!this.currentUser) return;

    const isOwnProfile = !this.currentUserId;

    const header = new ProfileHeader(this.currentUser, isOwnProfile, this.friendshipStatus);
    const stats = new StatsCard(this.currentUser);

    const components: ProfileRenderSections = { header, stats };
    if (isOwnProfile) {
      components.history = new MatchHistoryCard(this.matchHistory, isOwnProfile);
      components.friends = new FriendsSection(this.friends, isOwnProfile);
    }

    container.innerHTML = new ProfileLayout(isOwnProfile, components).render();
    components.history?.mountFilters(container);

    this.setupEvents(components, isOwnProfile);
  }

  private renderLoading(container: Element): void {
    container.innerHTML = `
      <div class="flex justify-center items-center h-64">
        <div class="animate-spin rounded-full h-12 w-12 border-b-2 border-primary-500"></div>
        <span class="ml-4 text-gray-300">Loading...</span>
      </div>
    `;
  }

  private renderError(container: Element, msg: string): void {
    container.innerHTML = `
      <div class="text-center py-16">
        <div class="text-red-500 text-6xl mb-4">⚠️</div>
        <h2 class="text-2xl font-bold mb-4 text-red-400">Error!</h2>
        <p class="text-gray-300 mb-6">${msg}</p>
        <button id="back-home" class="action-primary">Back</button>
      </div>
    `;
    document.getElementById('back-home')?.addEventListener('click', () => {
      window.dispatchEvent(new CustomEvent('navigate', { detail: '/' }));
    });
  }

  private setupEvents(components: any, isOwnProfile: boolean): void {
    if (isOwnProfile) {
      components.header.bindEvents({
        onEditProfile: () => this.showEditModal(),
        onChangePassword: () => this.showChangePasswordModal(),
        onToggle2FA: enabled => this.toggleTwoFactorAuth(enabled)
      });
      components.friends?.bindEvents();
    } else {
      components.header.bindEvents({
        onFriendAction: async action => await this.executeFriendAction(action)
      });
    }
  }

  private async executeFriendAction(action: string): Promise<void> {
    if (!this.currentUserId) return;

    try {
      let success = false;
      const uid = parseInt(this.currentUserId);

      if (action === 'add-friend') {
        success = await socialConnectionsService.sendFriendRequest(uid);
      } else if (action === 'remove-friend' && confirm('Are you sure you want to remove this friend?')) {
        success = await socialConnectionsService.removeFriend(uid);
      }

      if (success) {
        this.friends = await socialConnectionsService.getFriends();
        this.friendshipStatus = this.determineFriendshipStatus(uid);
        const container = document.querySelector('#page-content');
        container && this.render(container);
      }
    } catch (err) {
      DevConsole.reportError('Friend action failed:', err);
    }
  }

  private showEditModal(): void {
    if (!this.currentUser) return;
    const modal = new EditProfileModal(this.currentUser, async updated => {
      this.currentUser = updated;
      document.querySelector('#page-content') && this.render(document.querySelector('#page-content')!);
      await userAuthenticationService.loadCurrentUser();
      window.dispatchEvent(new CustomEvent('authStateChanged'));
    });
    modal.show();
  }

  private showChangePasswordModal(): void {
    if (!this.currentUser) return;
    const modal = new ChangePasswordModal(this.currentUser, () => {
      alert('Password changed successfully');
      const container = document.querySelector('#page-content');
      container && this.render(container);
    });
    modal.show();
  }

  private async toggleTwoFactorAuth(enabled: boolean): Promise<void> {
    try {
      const result = enabled
        ? await securityCodeService.enable2FA()
        : await securityCodeService.disable2FA();

      if (!result.success) throw new Error(result.message);

      const modal = new TwoFactorAuthModal(
        enabled ? 'enable' : 'disable',
        () => {
          if (this.currentUser) this.currentUser.twoFactorEnabled = enabled;
          const container = document.querySelector('#page-content');
          container && this.render(container);
          alert(`Two-Factor Authentication ${enabled ? 'enabled' : 'disabled'} successfully`);
        },
        () => {
          const toggle = document.getElementById('toggle-2fa') as HTMLInputElement;
          if (toggle) toggle.checked = !enabled;
        }
      );
      modal.show();
    } catch (err) {
      DevConsole.reportError('2FA error:', err);
      alert((err as Error).message);
      throw err;
    }
  }
}
