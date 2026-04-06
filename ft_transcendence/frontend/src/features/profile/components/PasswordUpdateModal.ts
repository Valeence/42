import { userProfileService } from '../services/userProfileService';
import type { AccountProfile } from '@/types/index.js';

export class ChangePasswordModal {
  private modalElement: HTMLElement | null = null;
  private currentUser: AccountProfile;
  private onSaveCallback: () => void;

  constructor(user: AccountProfile, onSave: () => void) {
    this.currentUser = user;
    this.onSaveCallback = onSave;
  }

  show(): void {
    this.buildModal();
    this.attachEventHandlers();
    setTimeout(() => {
      this.modalElement?.classList.replace('opacity-0', 'opacity-100');
      const content = this.modalElement?.querySelector('.modal-content');
      content?.classList.replace('scale-95', 'scale-100');
    }, 10);
  }

  close(): void {
    if (!this.modalElement) return;
    this.modalElement.classList.replace('opacity-100', 'opacity-0');
    const content = this.modalElement.querySelector('.modal-content');
    content?.classList.replace('scale-100', 'scale-95');

    setTimeout(() => {
      document.removeEventListener('keydown', this.handleKeydown);
      this.modalElement?.remove();
      this.modalElement = null;
    }, 300);
  }

  private buildModal(): void {
    this.close();
    this.modalElement = document.createElement('div');
    this.modalElement.id = 'change-password-modal';
    this.modalElement.className =
      'fixed inset-0 z-50 overflow-y-auto bg-black bg-opacity-50 flex items-center justify-center p-4 opacity-0 transition-opacity duration-300';

    this.modalElement.innerHTML = `
      <div class="modal-content bg-gray-800 rounded-lg max-w-md w-full transform scale-95 transition-transform duration-300">
        <div class="p-6">
          <div class="flex justify-between items-center mb-6">
            <h2 class="text-2xl font-bold text-white">Change Password</h2>
            <button id="close-modal" class="text-gray-400 hover:text-white p-2 rounded-full hover:bg-gray-700 transition-colors">
              <svg class="w-6 h-6" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M6 18L18 6M6 6l12 12"></path>
              </svg>
            </button>
          </div>
          <form id="change-password-form" class="space-y-6">
            <div>
              <label for="current-password" class="block text-sm font-medium text-gray-300 mb-2">Current Password</label>
              <input type="password" id="current-password" class="w-full px-3 py-2 bg-gray-700 border border-gray-600 rounded-md text-white placeholder-gray-400 focus:outline-none focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-colors" required />
            </div>
            <div>
              <label for="new-password" class="block text-sm font-medium text-gray-300 mb-2">New Password</label>
              <input type="password" id="new-password" class="w-full px-3 py-2 bg-gray-700 border border-gray-600 rounded-md text-white placeholder-gray-400 focus:outline-none focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-colors" required minlength="8" />
            </div>
            <div>
              <label for="confirm-password" class="block text-sm font-medium text-gray-300 mb-2">Confirm New Password</label>
              <input type="password" id="confirm-password" class="w-full px-3 py-2 bg-gray-700 border border-gray-600 rounded-md text-white placeholder-gray-400 focus:outline-none focus:ring-2 focus:ring-primary-500 focus:border-transparent transition-colors" required minlength="8" />
            </div>
            <div id="password-error-message" class="hidden bg-red-900 bg-opacity-50 border border-red-700 text-red-300 px-4 py-3 rounded-md">
              <span id="password-error-description"></span>
            </div>
            <div class="flex justify-end space-x-3 pt-4 border-t border-gray-700">
              <button type="button" id="cancel-change" class="px-6 py-2 bg-gray-600 hover:bg-gray-700 text-white rounded-lg transition-colors font-medium">Cancel</button>
              <button type="submit" id="save-password" class="px-6 py-2 bg-primary-600 hover:bg-primary-700 text-white rounded-lg transition-colors font-medium flex items-center disabled:opacity-50 disabled:cursor-not-allowed">
                <span id="save-spinner" class="hidden mr-2">
                  <div class="animate-spin rounded-full h-4 w-4 border-b-2 border-white"></div>
                </span>
                <span id="save-text">Change Password</span>
              </button>
            </div>
          </form>
        </div>
      </div>
    `;
    document.body.appendChild(this.modalElement);
  }

  private attachEventHandlers(): void {
    if (!this.modalElement) return;

    const closeBtn = this.modalElement.querySelector('#close-modal');
    const cancelBtn = this.modalElement.querySelector('#cancel-change');

    [closeBtn, cancelBtn].forEach(element => element?.addEventListener('click', () => this.close()));

    this.modalElement.addEventListener('click', e => {
      if (e.target === this.modalElement) this.close();
    });

    const form = this.modalElement.querySelector('#change-password-form') as HTMLFormElement;
    form?.addEventListener('submit', e => this.handleSubmit(e));

    document.addEventListener('keydown', this.handleKeydown);
  }

  private handleKeydown = (e: KeyboardEvent) => {
    if (e.key === 'Escape') this.close();
  };

  private async handleSubmit(e: Event): Promise<void> {
    e.preventDefault();
    if (!this.modalElement) return;

    const form = e.target as HTMLFormElement;
    const saveBtn = form.querySelector('#save-password') as HTMLButtonElement;
    const saveText = form.querySelector('#save-text') as HTMLElement;
    const saveSpinner = form.querySelector('#save-spinner') as HTMLElement;
    const errorMessage = form.querySelector('#password-error-message') as HTMLElement;

    saveBtn.disabled = true;
    saveText.textContent = "Changing Password...";
    saveSpinner.classList.remove('hidden');
    errorMessage.classList.add('hidden');

    try {
      const currentPassword = (form.querySelector('#current-password') as HTMLInputElement).value;
      const newPassword = (form.querySelector('#new-password') as HTMLInputElement).value;
      const confirmPassword = (form.querySelector('#confirm-password') as HTMLInputElement).value;

      if (newPassword !== confirmPassword) {
        throw new Error("New passwords do not match");
      }

      if (newPassword.length < 8) {
        throw new Error("New password must be at least 8 characters long");
      }

      await userProfileService.changePassword(currentPassword, newPassword);
      this.onSaveCallback();
      this.close();
    } catch (err) {
      this.showError((err as Error).message);
    } finally {
      saveBtn.disabled = false;
      saveSpinner.classList.add('hidden');
      saveText.textContent = "Change Password";
    }
  }

  private showError(message: string): void {
    if (!this.modalElement) return;

    const errorContainer = this.modalElement.querySelector('#password-error-message') as HTMLElement;
    const errorDesc = this.modalElement.querySelector('#password-error-description') as HTMLElement;

    if (errorContainer && errorDesc) {
      errorDesc.textContent = message;
      errorContainer.classList.remove('hidden');

      setTimeout(() => errorContainer.classList.add('hidden'), 5000);
    }
  }
}
