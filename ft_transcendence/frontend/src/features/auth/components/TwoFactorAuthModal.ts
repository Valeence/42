import { securityCodeService } from '../services/securityCodeService.js';

export class TwoFactorAuthModal {
  private modal: HTMLElement | null = null;

  constructor(
    private mode: 'enable' | 'disable' | 'login',
    private onSuccess: (code?: string) => void | Promise<void>,
    private onCancel?: () => void
  ) {}

  show(): void {
    this.modal = this.buildModal();
    document.body.appendChild(this.modal);

    setTimeout(() => {
      this.modal?.classList.replace('opacity-0', 'opacity-100');
      const content = this.modal?.querySelector('.modal-content');
      content?.classList.replace('scale-95', 'scale-100');
    }, 10);

    this.bindEvents();

    setTimeout(() => {
      const input = this.modal?.querySelector('#verification-code') as HTMLInputElement;
      input?.focus();
    }, 100);
  }

  private buildModal(): HTMLElement {
    const modal = document.createElement('div');
    modal.className = 'fixed inset-0 flex items-center justify-center z-50 bg-black bg-opacity-50 opacity-0 transition-opacity duration-300';

    let title = '', description = '', buttonText = '';

    if (this.mode === 'enable') {
      title = 'Enable Two-Factor Authentication';
      description = 'Enter the verification code sent to your email to enable 2FA.';
      buttonText = 'Enable 2FA';
    } else if (this.mode === 'disable') {
      title = 'Disable Two-Factor Authentication';
      description = 'Enter the verification code to disable 2FA.';
      buttonText = 'Disable 2FA';
    } else {
      title = 'Two-Factor Authentication';
      description = 'Enter the verification code sent to your email.';
      buttonText = 'Verify Code';
    }

    modal.innerHTML = `
      <div class="modal-content transform scale-95 transition-transform duration-300 bg-gray-800 rounded-lg p-6 max-w-md w-full mx-4">
        <div class="flex items-center justify-between mb-6">
          <h2 class="text-white text-xl font-bold">${title}</h2>
          <button id="close-modal" class="text-gray-400 hover:text-white">
            <svg class="w-6 h-6" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M6 18L18 6M6 6l12 12"></path>
            </svg>
          </button>
        </div>
        <div class="mb-6">
          <p class="text-gray-300 mb-4">${description}</p>
          <form id="verification-form">
            <div class="mb-4">
              <label for="verification-code" class="block text-sm font-medium text-gray-300 mb-2">Verification Code</label>
              <input type="text" id="verification-code" maxlength="6" pattern="[0-9]{6}" required
                placeholder="000000"
                class="w-full px-3 py-2 rounded-lg bg-gray-700 text-white focus:outline-none focus:ring-2 focus:ring-blue-500"/>
            </div>
            <div id="error-message" class="hidden mb-4 p-3 bg-red-900 border border-red-700 rounded-lg">
              <p id="error-description" class="text-red-300 text-sm"></p>
            </div>
            <div class="flex gap-3">
              <button type="button" id="cancel-action-trigger" class="flex-1 px-4 py-2 bg-gray-600 rounded-lg text-white hover:bg-gray-700">Cancel</button>
              <button type="submit" id="verify-action-trigger" class="flex-1 px-4 py-2 bg-blue-600 text-white rounded-lg hover:bg-blue-700 disabled:opacity-50 disabled:cursor-not-allowed">
                <span id="verify-text">${buttonText}</span>
                <svg id="verify-spinner" class="hidden animate-spin h-4 w-4 ml-2 inline-block" fill="none" viewBox="0 0 24 24">
                  <circle cx="12" cy="12" r="10" stroke="currentColor" stroke-width="4" class="opacity-25"></circle>
                  <path fill="currentColor" class="opacity-75" d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"></path>
                </svg>
              </button>
            </div>
          </form>
        </div>
      </div>
    `;
    return modal;
  }

  private showError(message: string): void {
    if (!this.modal) return;

    const errorContainer = this.modal.querySelector('#error-message');
    const errorDesc = this.modal.querySelector('#error-description');

    if (errorContainer && errorDesc) {
      errorDesc.textContent = message;
      errorContainer.classList.remove('hidden');
    }
  }

  private hideError(): void {
    if (!this.modal) return;
    const errorContainer = this.modal.querySelector('#error-message');
    errorContainer?.classList.add('hidden');
  }

  private validateCode(): void {
    if (!this.modal) return;

    const codeInput = this.modal.querySelector('#verification-code') as HTMLInputElement;
    const verifyBtn = this.modal.querySelector('#verify-action-trigger') as HTMLButtonElement;
    const cleaned = codeInput.value.replace(/\D/g, '');
    codeInput.value = cleaned;
    verifyBtn.disabled = cleaned.length !== 6;
  }

  private bindEvents(): void {
    if (!this.modal) return;

    const closeBtn = this.modal.querySelector('#close-modal');
    const cancelBtn = this.modal.querySelector('#cancel-action-trigger');

    [closeBtn, cancelBtn].forEach(element => {
      element?.addEventListener('click', () => {
        this.onCancel?.();
        this.close();
      });
    });

    this.modal.addEventListener('click', (e) => {
      if (e.target === this.modal) {
        this.onCancel?.();
        this.close();
      }
    });

    const form = this.modal.querySelector('#verification-form') as HTMLFormElement;
    form?.addEventListener('submit', (e) => this.handleSubmit(e));

    const codeInput = this.modal.querySelector('#verification-code') as HTMLInputElement;
    codeInput?.addEventListener('input', () => this.validateCode());
  }

  private async handleSubmit(e: Event): Promise<void> {
    e.preventDefault();
    if (!this.modal) return;

    const form = e.target as HTMLFormElement;
    const codeInput = form.querySelector('#verification-code') as HTMLInputElement;
    const verifyBtn = form.querySelector('#verify-action-trigger') as HTMLButtonElement;
    const verifyText = form.querySelector('#verify-text') as HTMLElement;
    const verifySpinner = form.querySelector('#verify-spinner') as HTMLElement;

    verifyBtn.disabled = true;
    verifySpinner.classList.remove('hidden');
    verifyText.textContent = 'Loading...';
    this.hideError();

    try {
      const code = codeInput.value;
      if (this.mode === 'login') {
        await this.onSuccess(code);
        this.close();
      } else {
        const result = await securityCodeService.verify2FA(code, this.mode === 'disable');
        if (result.success) {
          await this.onSuccess();
          this.close();
        } else {
          throw new Error(result.message);
        }
      }
    } catch (err) {
      const errorMessage = (err as Error).message;
      this.showError(errorMessage);

      if (errorMessage === 'Too many failed attempts') {
        setTimeout(() => this.onCancel?.(), 2000);
        setTimeout(() => this.close(), 2000);
      }
    } finally {
      if (this.modal) {
        verifyBtn.disabled = false;
        verifyText.textContent =
          this.mode === 'enable'
            ? 'Enable 2FA'
            : this.mode === 'disable'
            ? 'Disable 2FA'
            : 'Verify Code';
        verifySpinner.classList.add('hidden');
      }
    }
  }

  public close(): void {
    if (!this.modal) return;

    this.modal.classList.replace('opacity-100', 'opacity-0');
    const content = this.modal.querySelector('.modal-content');
    content?.classList.replace('scale-100', 'scale-95');

    setTimeout(() => {
      this.modal?.remove();
      this.modal = null;
    }, 300);
  }
}
