import { userProfileService } from '../services/userProfileService';
import type { AccountProfile } from '@/types/index.js';

export class EditProfileModal {
  private modalElement: HTMLElement | null = null;
  private currentUser: AccountProfile;
  private saveCallback: (updatedUser: AccountProfile) => void;

  constructor(user: AccountProfile, onSave: (updatedUser: AccountProfile) => void) {
    this.currentUser = user;
    this.saveCallback = onSave;
  }

  show(): void {
    this.renderModal();
    this.attachEventHandlers();
    requestAnimationFrame(() => this.animateOpen());
  }

  close(): void {
    if (!this.modalElement) return;
    this.animateClose();
    setTimeout(() => {
      document.removeEventListener('keydown', this.onEscapePress);
      this.modalElement?.remove();
      this.modalElement = null;
    }, 300);
  }

  private renderModal(): void {
    this.close();
    const avatarUrl = this.currentUser.avatarUrl || '/default.jpg';
    const isGoogleUser = !!this.currentUser.googleId;
    this.modalElement = document.createElement('div');
    this.modalElement.id = 'edit-profile-modal';
    this.modalElement.className = 'fixed inset-0 z-50 overflow-y-auto bg-black bg-opacity-50 flex items-center justify-center p-4 opacity-0 transition-opacity duration-300';
    this.modalElement.innerHTML = `
      <div class="modal-content bg-gray-800 rounded-lg max-w-md w-full transform scale-95 transition-transform duration-300">
        <div class="p-6">
          ${this.renderHeader()}
          ${this.renderForm(avatarUrl, isGoogleUser)}
        </div>
      </div>
    `;
    document.body.appendChild(this.modalElement);
  }

  private renderHeader(): string {
    return `
      <div class="flex justify-between items-center mb-6">
        <h2 class="text-2xl font-bold text-white">Edit Profile</h2>
        <button id="close-modal" class="text-gray-400 hover:text-white p-2 rounded-full hover:bg-gray-700 transition-colors">
          <svg class="w-6 h-6" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M6 18L18 6M6 6l12 12"></path>
          </svg>
        </button>
      </div>
    `;
  }

  private renderForm(avatarUrl: string, isGoogleUser: boolean): string {
    return `
      <form id="edit-profile-form" class="space-y-6">
        ${this.renderAvatarSection(avatarUrl)}
        ${this.renderUsernameField()}
        ${this.renderEmailField(isGoogleUser)}
        <div id="edit-error-message" class="hidden bg-red-900 bg-opacity-50 border border-red-700 text-red-300 px-4 py-3 rounded-md">
          <span id="edit-error-description"></span>
        </div>
        ${this.renderFormActions()}
      </form>
    `;
  }

  private renderAvatarSection(avatarUrl: string): string {
    return `
      <div class="text-center">
        <div class="relative inline-block group">
          <img id="preview-avatar" src="${avatarUrl}" alt="${this.currentUser.username}" class="w-24 h-24 rounded-full object-cover border-4 border-primary-500 transition-transform group-hover:scale-105"/>
          <button type="button" id="change-avatar-action-trigger" class="absolute inset-0 bg-black bg-opacity-50 rounded-full opacity-0 group-hover:opacity-100 transition-opacity flex items-center justify-center">
            <svg class="w-6 h-6 text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M3 9a2 2 0 012-2h.93a2 2 0 001.664-.89l.812-1.22A2 2 0 0110.07 4h3.86a2 2 0 011.664.89l.812 1.22A2 2 0 0018.07 7H19a2 2 0 012 2v9a2 2 0 01-2 2H5a2 2 0 01-2-2V9z"/>
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M15 13a3 3 0 11-6 0 3 3 0 016 0z"/>
            </svg>
          </button>
        </div>
        <input type="file" id="avatar-upload" accept="image/*" class="hidden"/>
        <p class="text-gray-400 text-sm mt-2">Click to change your avatar</p>
      </div>
    `;
  }

  private renderUsernameField(): string {
    return `
      <div>
        <label for="edit-username" class="block text-sm font-medium text-gray-300 mb-2">Username</label>
        <input type="text" id="edit-username" value="${this.currentUser.username}" class="w-full px-3 py-2 bg-gray-700 border border-gray-600 rounded-md text-white placeholder-gray-400 focus:outline-none focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-colors" required minlength="3" maxlength="20"/>
      </div>
    `;
  }

  private renderEmailField(isGoogleUser: boolean): string {
    const readOnlyAttr = isGoogleUser ? 'readonly' : 'required';
    const className = isGoogleUser ? 'cursor-not-allowed opacity-50' : '';
    const googleNotice = isGoogleUser ? `<p class="text-xs text-gray-400 mt-1">Email cannot be changed for Google accounts</p>` : '';
    return `
      <div>
        <label for="edit-email" class="block text-sm font-medium text-gray-300 mb-2">Email</label>
        <input type="email" id="edit-email" value="${this.currentUser.email || ''}" class="w-full px-3 py-2 bg-gray-700 border border-gray-600 rounded-md text-white placeholder-gray-400 focus:outline-none focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-colors ${className}" ${readOnlyAttr}/>
        ${googleNotice}
      </div>
    `;
  }

  private renderFormActions(): string {
    return `
      <div class="flex justify-end space-x-3 pt-4 border-t border-gray-700">
        <button type="button" id="cancel-edit" class="px-6 py-2 bg-gray-600 hover:bg-gray-700 text-white rounded-lg transition-colors font-medium">Cancel</button>
        <button type="submit" id="save-profile" class="px-6 py-2 bg-primary-600 hover:bg-primary-700 text-white rounded-lg transition-colors font-medium flex items-center disabled:opacity-50 disabled:cursor-not-allowed">
          <span id="save-spinner" class="hidden mr-2"><div class="animate-spin rounded-full h-4 w-4 border-b-2 border-white"></div></span>
          <span id="save-text">Save Changes</span>
        </button>
      </div>
    `;
  }

  private attachEventHandlers(): void {
    if (!this.modalElement) return;
    ['#close-modal', '#cancel-edit'].forEach(id => this.modalElement!.querySelector(id)?.addEventListener('click', () => this.close()));
    this.modalElement.addEventListener('click', e => { if (e.target === this.modalElement) this.close(); });

    const avatarBtn = this.modalElement.querySelector('#change-avatar-action-trigger');
    const avatarInput = this.modalElement.querySelector('#avatar-upload') as HTMLInputElement;
    const avatarPreview = this.modalElement.querySelector('#preview-avatar') as HTMLImageElement;

    avatarBtn?.addEventListener('click', () => avatarInput.click());
    avatarInput?.addEventListener('change', e => this.handleAvatarChange(e, avatarPreview));

    const form = this.modalElement.querySelector('#edit-profile-form') as HTMLFormElement;
    form?.addEventListener('submit', e => this.onSubmit(e));
    document.addEventListener('keydown', this.onEscapePress);
  }

  private handleAvatarChange(e: Event, preview: HTMLImageElement) {
    const file = (e.target as HTMLInputElement).files?.[0];
    if (!file) return;

    if (file.size > 5 * 1024 * 1024 || !file.type.startsWith('image/')) {
      this.showError("Please fill in all fields");
      return;
    }

    const reader = new FileReader();
    reader.onload = event => { if (event.target?.result) preview.src = event.target.result as string; };
    reader.readAsDataURL(file);
  }

  private onEscapePress = (e: KeyboardEvent) => { if (e.key === 'Escape') this.close(); };

  private async onSubmit(e: Event): Promise<void> {
    e.preventDefault();
    if (!this.modalElement) return;

    const form = e.target as HTMLFormElement;
    const saveBtn = form.querySelector('#save-profile') as HTMLButtonElement;
    const saveText = form.querySelector('#save-text') as HTMLElement;
    const saveSpinner = form.querySelector('#save-spinner') as HTMLElement;

    this.toggleSavingState(saveBtn, saveText, saveSpinner, true);
    this.hideError();

    try {
      const avatarFile = (form.querySelector('#avatar-upload') as HTMLInputElement).files?.[0];
      const username = (form.querySelector('#edit-username') as HTMLInputElement).value.trim();
      const email = (form.querySelector('#edit-email') as HTMLInputElement).value.trim();

      if (!username || username.length < 3 || username.length > 20) throw new Error("Username is required");
      if (!email.includes('@')) throw new Error("Username is required");

      const updatedUser = await userProfileService.updateProfile({ username, email }, avatarFile);
      this.saveCallback(updatedUser);
      this.close();
    } catch (error) {
      this.showError((error as Error).message);
    } finally {
      this.toggleSavingState(saveBtn, saveText, saveSpinner, false);
    }
  }

  private toggleSavingState(button: HTMLButtonElement, textElem: HTMLElement, spinner: HTMLElement, saving: boolean) {
    button.disabled = saving;
    textElem.textContent = "Save Changes";
    spinner.classList.toggle('hidden', !saving);
  }

  private showError(msg: string): void {
    if (!this.modalElement) return;
    const container = this.modalElement.querySelector('#edit-error-message');
    const desc = this.modalElement.querySelector('#edit-error-description');
    if (container && desc) {
      desc.textContent = msg;
      container.classList.remove('hidden');
      setTimeout(() => container.classList.add('hidden'), 5000);
    }
  }

  private hideError(): void {
    if (!this.modalElement) return;
    this.modalElement.querySelector('#edit-error-message')?.classList.add('hidden');
  }

  private animateOpen(): void {
    if (!this.modalElement) return;
    this.modalElement.classList.replace('opacity-0', 'opacity-100');
    const content = this.modalElement.querySelector('.modal-content');
    content?.classList.replace('scale-95', 'scale-100');
  }

  private animateClose(): void {
    if (!this.modalElement) return;
    this.modalElement.classList.replace('opacity-100', 'opacity-0');
    const content = this.modalElement.querySelector('.modal-content');
    content?.classList.replace('scale-100', 'scale-95');
  }
}
