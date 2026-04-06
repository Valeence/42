import { userProfileService } from '../services/userProfileService.js';
import { socialConnectionsService } from '../services/socialConnectionsService.js';
import type { FriendProfile } from '@/types/index.js';
import { FriendsManagementModal } from './SocialConnectionsModal.js';
import { DevConsole } from '@/utils/devConsole.js';

export class FriendsSection {
  private onFriendsUpdate: (() => void) | null = null;

  constructor(private friendsList: FriendProfile[], private ownProfile: boolean) {}

  render(): string {
    return `
      <div class="bg-gray-800 rounded-lg p-6 friends-section">
        ${this.buildHeader()}
        ${this.buildFriendsContent()}
      </div>
    `;
  }

  private buildHeader(): string {
    const manageBtn = this.ownProfile
      ? `<button id="manage-friends" class="action-secondary text-sm">Manage</button>`
      : '';
    return `
      <div class="flex justify-between items-center mb-6">
        <h2 class="text-xl font-bold text-primary-400 flex items-center">
          <svg class="w-6 h-6 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 4.354a4 4 0 110 5.292M15 21H3v-1a6 6 0 0112 0v1zm0 0h6v-1a6 6 0 00-9-5.197m13.5-9a2.5 2.5 0 11-5 0 2.5 2.5 0 015 0z"></path>
          </svg>
          Friends (${this.friendsList.length})
        </h2>
        ${manageBtn}
      </div>
    `;
  }

  private buildFriendsContent(): string {
    if (!this.friendsList.length) return this.buildEmptyState();
    const itemsHtml = this.friendsList.map(f => this.buildFriendCard(f)).join('');
    const viewAllBtn = this.friendsList.length > 5
      ? `<button id="view-all-friends" class="w-full mt-4 action-secondary text-sm">Friends (${this.friendsList.length})</button>`
      : '';
    return `<div class="space-y-3 max-h-64 overflow-y-auto">${itemsHtml}</div>${viewAllBtn}`;
  }

  private buildEmptyState(): string {
    const findBtn = this.ownProfile
      ? `<button class="mt-4 action-primary text-sm" data-action="find-friends">Find Friends</button>`
      : '';
    return `
      <div class="text-center py-8">
        <div class="text-gray-400 text-4xl mb-4">👥</div>
        <p class="text-gray-400">No friends yet</p>
        ${findBtn}
      </div>
    `;
  }

  private buildFriendCard(friend: FriendProfile): string {
    const avatar = userProfileService.getAvatarUrl(friend.avatarUrl);
    const status = friend.isOnline ? "Online" : this.formatLastSeen(friend.lastSeen);
    return `
      <div class="flex items-center justify-between p-3 bg-gray-700 rounded-lg hover:bg-gray-600 transition-colors group">
        <div class="flex items-center space-x-3">
          <div class="relative">
            <img src="${avatar}" alt="${friend.username}" class="w-10 h-10 rounded-full bg-gray-600 object-cover" onerror="this.src='/default.jpg'">
            <div class="absolute -bottom-1 -right-1 w-4 h-4 ${friend.isOnline ? 'bg-green-500' : 'bg-gray-500'} rounded-full border-2 border-gray-700"></div>
          </div>
          <div>
            <div class="text-white font-medium">${friend.username}</div>
            <div class="text-gray-400 text-sm">${status}</div>
          </div>
        </div>
        <div class="flex space-x-2 opacity-0 group-hover:opacity-100 transition-opacity">
          <button class="text-blue-400 hover:text-blue-300 p-1" title="View Profile" data-friend-id="${friend.id}" data-action="view-profile">
            <svg class="w-5 h-5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M15 12a3 3 0 11-6 0 3 3 0 016 0z"></path>
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M2.458 12C3.732 7.943 7.523 5 12 5c4.478 0 8.268 2.943 9.542 7-1.274 4.057-5.064 7-9.542 7-4.477 0-8.268-2.943-9.542-7z"></path>
            </svg>
          </button>
        </div>
      </div>
    `;
  }

  public bindEvents(): void {
    if (this.ownProfile) {
      document.getElementById('manage-friends')?.addEventListener('click', () => this.openModal());
    }
    document.querySelector('[data-action="find-friends"]')?.addEventListener('click', () => this.openModal('search'));
    document.getElementById('view-all-friends')?.addEventListener('click', () => this.openModal('friends'));

    document.addEventListener('click', (e) => {
      const actionable = (e.target as HTMLElement).closest('[data-action]') as HTMLElement;
      if (!actionable) return;
      const action = actionable.dataset.action;
      const id = parseInt(actionable.dataset.friendId || '0');
      action && this.handleFriendAction(action, id);
    });

    this.onFriendsUpdate = async () => await this.refreshList();
    window.addEventListener('friendsUpdated', this.onFriendsUpdate);
  }

  destroy(): void {
    if (!this.onFriendsUpdate) return;
    window.removeEventListener('friendsUpdated', this.onFriendsUpdate);
    this.onFriendsUpdate = null;
  }

  private async refreshList(): Promise<void> {
    try {
      this.friendsList = await socialConnectionsService.getFriends();
      const container = document.querySelector('.friends-section');
      if (container) {
        container.innerHTML = this.render();
        this.bindEvents();
      }
    } catch (err) {
      DevConsole.reportError('Refreshing friends failed:', err);
    }
  }

  private handleFriendAction(action: string, friendId: number): void {
    if (!friendId) return;
    switch (action) {
      case 'view-profile': this.navigateToProfile(friendId); break;
      case 'challenge': this.sendChallenge(friendId); break;
      case 'message': this.openChat(friendId); break;
    }
  }

  private navigateToProfile(friendId: number) {
    window.dispatchEvent(new CustomEvent('navigate', { detail: `/profile/${friendId}` }));
  }

  private sendChallenge(friendId: number) {
    window.dispatchEvent(new CustomEvent('createGameInvitation', { detail: { friendId } }));
  }

  private openChat(friendId: number) {
    window.dispatchEvent(new CustomEvent('openChat', { detail: { friendId } }));
  }

  private async openModal(tab: 'friends' | 'requests' | 'search' = 'friends'): Promise<void> {
    try {
      const modal = new FriendsManagementModal();
      if (tab !== 'friends') (modal as any).activeTab = tab;
      await modal.show();
      window.addEventListener('friendsListUpdated', () => this.refreshList(), { once: true });
    } catch (err) {
      DevConsole.reportError('Failed to open modal:', err);
    }
  }

  private formatLastSeen(lastSeen?: string): string {
    if (!lastSeen) return 'Offline';
    const diffMs = new Date().getTime() - new Date(lastSeen).getTime();
    const mins = Math.floor(diffMs / 60000);
    if (mins < 5) return 'Just now';
    if (mins < 60) return `${mins}m ago`;
    const hours = Math.floor(mins / 60);
    if (hours < 24) return `${hours}h ago`;
    return `${Math.floor(hours / 24)}d ago`;
  }
}
