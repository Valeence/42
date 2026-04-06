import { socialConnectionsService } from '../services/socialConnectionsService';
import { userProfileService } from '../services/userProfileService';
import type { AccountProfile, FriendProfile } from '@/types/index.js';
import { DevConsole } from '@/utils/devConsole.js';

export class FriendsManagementModal {
  private container: HTMLElement | null = null;
  private activeTab: 'friends' | 'search' = 'friends';
  private myFriends: FriendProfile[] = [];
  private usersFound: AccountProfile[] = [];

  public async show(): Promise<void> {
    await this.fetchFriends();
    this.renderModal();
    this.attachEventHandlers();
    requestAnimationFrame(() => this.animateOpen());
  }

  public close(): void {
    if (!this.container) return;
    this.animateClose();
    window.dispatchEvent(new CustomEvent('friendsUpdated'));
    setTimeout(() => {
      this.container?.remove();
      this.container = null;
    }, 300);
  }

  private async fetchFriends(): Promise<void> {
    try {
      this.myFriends = await socialConnectionsService.getFriends();
    } catch (err) {
      DevConsole.reportError('Failed to load friends:', err);
      this.myFriends = [];
    }
  }

  private renderModal(): void {
    this.close();
    const container = document.createElement('div');
    container.className = 'fixed inset-0 z-50 overflow-y-auto bg-black bg-opacity-50 flex items-center justify-center p-4 opacity-0 transition-opacity duration-300';
    container.innerHTML = `
      <div class="modal-content bg-gray-800 rounded-lg max-w-2xl w-full max-h-[90vh] overflow-hidden transform scale-95 transition-transform duration-300">
        <div class="p-6">
          ${this.buildHeader()}
          ${this.buildTabs()}
          <div id="tab-content" class="min-h-[400px] max-h-[500px] overflow-y-auto">
            ${this.renderCurrentTab()}
          </div>
        </div>
      </div>
    `;
    document.body.appendChild(container);
    this.container = container;
  }

  private buildHeader(): string {
    return `
      <div class="flex justify-between items-center mb-6">
        <h2 class="text-2xl font-bold text-white">Manage Friends</h2>
        <button id="close-modal" class="text-gray-400 hover:text-white p-2 rounded-full hover:bg-gray-700 transition-colors">
          <svg class="w-6 h-6" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M6 18L18 6M6 6l12 12"></path>
          </svg>
        </button>
      </div>
    `;
  }

  private buildTabs(): string {
    return `
      <div class="flex space-x-1 mb-6 bg-gray-700 rounded-lg p-1">
        <button id="tab-friends" class="tab-action-trigger flex-1 py-2 px-4 rounded-md transition-colors ${this.activeTab === 'friends' ? 'bg-blue-600 text-white' : 'text-gray-300 hover:text-white'}">
          My Friends (${this.myFriends.length})
        </button>
        <button id="tab-search" class="tab-action-trigger flex-1 py-2 px-4 rounded-md transition-colors ${this.activeTab === 'search' ? 'bg-blue-600 text-white' : 'text-gray-300 hover:text-white'}">
          Search Users
        </button>
      </div>
    `;
  }

  private renderCurrentTab(): string {
    return this.activeTab === 'friends' ? this.renderFriendsList() : this.renderSearchList();
  }

  private renderFriendsList(): string {
    if (!this.myFriends.length) {
      return `
        <div class="text-center py-12">
          <div class="text-gray-400 text-4xl mb-4">👥</div>
          <p class="text-gray-400 mb-4">Search for users to add as friends</p>
          <button class="action-primary" onclick="document.querySelector('#tab-search')?.click()">Search Users</button>
        </div>
      `;
    }

    return `<div class="space-y-3">
      ${this.myFriends.map(friend => `
        <div class="flex items-center justify-between p-4 bg-gray-700 rounded-lg">
          <div class="flex items-center space-x-3">
            <img src="${userProfileService.getAvatarUrl(friend.avatarUrl)}" alt="${friend.username}" class="w-12 h-12 rounded-full object-cover" onerror="this.src='/default.jpg'" />
            <div>
              <h3 class="font-semibold text-white">${friend.username}</h3>
              <p class="text-sm ${friend.isOnline ? 'text-green-400' : 'text-gray-400'}">${friend.isOnline ? 'Online' : 'Offline'}</p>
            </div>
          </div>
          <div class="flex space-x-2">
            <button class="action-secondary text-sm" data-action="view-profile" data-userid="${friend.id}">View</button>
            <button class="btn-danger text-sm" data-action="remove-friend" data-userid="${friend.id}">Remove</button>
          </div>
        </div>
      `).join('')}
    </div>`;
  }

  private renderSearchList(): string {
    if (!this.usersFound.length) {
      return `
        <div>
          <div class="mb-6 relative">
            <input type="text" id="search-input" placeholder="Search users" class="w-full px-4 py-3 bg-gray-700 border border-gray-600 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent text-white placeholder-gray-400" />
            <button id="search-action-trigger" class="absolute right-3 top-1/2 transform -translate-y-1/2 text-gray-400 hover:text-white">
              <svg class="w-5 h-5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M21 21l-6-6m2-5a7 7 0 11-14 0 7 7 0 0114 0z"></path>
              </svg>
            </button>
          </div>
          <div id="search-results">
            <div class="text-center py-12">
              <div class="text-gray-400 text-4xl mb-4">🔍</div>
              <p class="text-gray-400">No results found</p>
            </div>
          </div>
        </div>
      `;
    }

    return `<div class="space-y-3">
      ${this.usersFound.map(user => {
        const isFriend = this.myFriends.some(f => f.id === user.id);
        return `
          <div class="flex items-center justify-between p-4 bg-gray-700 rounded-lg">
            <div class="flex items-center space-x-3">
              <img src="${userProfileService.getAvatarUrl(user.avatarUrl)}" alt="${user.username}" class="w-12 h-12 rounded-full object-cover" onerror="this.src='/default.jpg'" />
              <div>
                <h3 class="font-semibold text-white">${user.username}</h3>
                <p class="text-sm ${user.isOnline ? 'text-green-400' : 'text-gray-400'}">${user.isOnline ? 'Online' : 'Offline'}</p>
                ${isFriend ? `<span class="text-xs bg-green-600 text-white px-2 py-1 rounded-full">Friend</span>` : ''}
              </div>
            </div>
            <div class="flex space-x-2">
              <button class="action-secondary text-sm" data-action="view-profile" data-userid="${user.id}">View</button>
              ${isFriend
                ? `<button class="btn-danger text-sm" data-action="remove-friend" data-userid="${user.id}">Remove</button>`
                : `<button class="action-primary text-sm" data-action="add-friend" data-userid="${user.id}">Add</button>`}
            </div>
          </div>
        `;
      }).join('')}
    </div>`;
  }

  private attachEventHandlers(): void {
    if (!this.container) return;

    const closeBtn = this.container.querySelector('#close-modal');
    closeBtn?.addEventListener('click', () => this.close());

    this.container.addEventListener('click', (e) => {
      if (e.target === this.container) this.close();
    });

    const tabButtons = this.container.querySelectorAll('.tab-action-trigger');
    tabButtons.forEach(button => {
      button.addEventListener('click', (e) => {
        const tab = (e.currentTarget as HTMLElement).id.replace('tab-', '') as 'friends' | 'search';
        this.switchTab(tab);
      });
    });

    this.container.addEventListener('click', (e) => this.handleActions(e));
    this.bindSearchInput();
  }

  private bindSearchInput(): void {
    if (!this.container) return;
    const input = this.container.querySelector('#search-input') as HTMLInputElement;
    const button = this.container.querySelector('#search-action-trigger');
    if (!input || !button) return;

    let timeout: number;

    const performSearch = async () => {
      const query = input.value.trim();
      if (!query || query.length < 2) {
        this.usersFound = [];
        this.updateSearchContent();
        return;
      }
      try {
        this.usersFound = await socialConnectionsService.searchUsers(query);
        this.updateSearchContent();
      } catch (err) {
        DevConsole.reportError('Search failed:', err);
        this.showMessage('Search failed', 'error');
      }
    };

    input.addEventListener('input', () => {
      clearTimeout(timeout);
      timeout = window.setTimeout(performSearch, 500);
    });
    input.addEventListener('keyup', (e) => e.key === 'Enter' && performSearch());
    button?.addEventListener('click', (e) => { e.preventDefault(); performSearch(); });
  }

  private switchTab(tab: 'friends' | 'search'): void {
    if (!this.container) return;
    this.activeTab = tab;
    this.container.querySelectorAll('.tab-action-trigger').forEach(button => button.classList.remove('bg-blue-600', 'text-white'));
    this.container.querySelector(`#tab-${tab}`)?.classList.add('bg-blue-600', 'text-white');
    this.updateTabContent();
  }

  private updateTabContent(): void {
    const content = this.container?.querySelector('#tab-content');
    if (content) content.innerHTML = this.renderCurrentTab();

    const friendsTab = this.container?.querySelector('#tab-friends');
    if (friendsTab) friendsTab.textContent = `My Friends (${this.myFriends.length})`;
  }

  private updateSearchContent(): void {
    const results = this.container?.querySelector('#search-results');
    if (results) results.innerHTML = this.renderSearchList();
  }

  private async handleActions(e: Event): Promise<void> {
    e.preventDefault();
    e.stopPropagation();
    const target = e.target as HTMLElement;
    const action = target.dataset.action;
    if (!action) return;

    try {
      switch (action) {
        case 'view-profile': {
          const userId = target.dataset.userid;
          if (!userId) return;
          this.close();
          setTimeout(() => window.dispatchEvent(new CustomEvent('navigate', { detail: `/profile/${userId}` })), 100);
          return;
        }
        case 'add-friend': {
          const id = parseInt(target.dataset.userid || '0');
          if (!id) return;
          const success = await socialConnectionsService.sendFriendRequest(id);
          if (success) {
            await this.fetchFriends();
            this.updateTabContent();
            this.updateSearchContent();
            this.showMessage('Friend request sent', 'success');
            window.dispatchEvent(new CustomEvent('friendsUpdated'));
          }
          break;
        }
        case 'remove-friend': {
          const id = parseInt(target.dataset.userid || '0');
          if (!id || !confirm('Are you sure you want to remove this friend?')) return;
          const success = await socialConnectionsService.removeFriend(id);
          if (success) {
            await this.fetchFriends();
            this.updateTabContent();
            this.updateSearchContent();
            this.showMessage('Friend removed', 'success');
            window.dispatchEvent(new CustomEvent('friendsUpdated'));
          }
          break;
        }
      }
    } catch (err) {
      DevConsole.reportError('Action failed:', err);
      this.showMessage('Action failed', 'error');
    }
  }

  private animateOpen(): void {
    if (!this.container) return;
    this.container.classList.remove('opacity-0');
    this.container.classList.add('opacity-100');
    const content = this.container.querySelector('.modal-content');
    content?.classList.remove('scale-95');
    content?.classList.add('scale-100');
  }

  private animateClose(): void {
    if (!this.container) return;
    this.container.classList.remove('opacity-100');
    this.container.classList.add('opacity-0');
    const content = this.container.querySelector('.modal-content');
    content?.classList.remove('scale-100');
    content?.classList.add('scale-95');
  }

  private showMessage(msg: string, type: 'success' | 'error'): void {
    const notif = document.createElement('div');
    notif.className = `fixed top-4 right-4 z-[60] px-4 py-2 rounded-lg text-white font-medium ${
      type === 'success' ? 'bg-green-600' : 'bg-red-600'
    } transform translate-x-full transition-transform duration-300`;
    notif.textContent = msg;
    document.body.appendChild(notif);
    requestAnimationFrame(() => notif.classList.remove('translate-x-full'));
    setTimeout(() => {
      notif.classList.add('translate-x-full');
      setTimeout(() => notif.remove(), 300);
    }, 3000);
  }
}
