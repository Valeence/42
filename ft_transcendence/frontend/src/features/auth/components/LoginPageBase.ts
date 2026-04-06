import { ErrorMessage } from './AuthErrorMessage';
import { OAuthButtons } from './SocialLoginButtons';
import { userAuthenticationService } from '../services/userAuthenticationService';
import { DevConsole } from '@/utils/devConsole.js';

export abstract class LoginPageBase {
  protected errorMessageComponent: ErrorMessage;
  protected oauthButtonsComponent: OAuthButtons;
  protected languageListener: (() => void) | null = null;

  constructor() {
    // initialize UI components
    this.oauthButtonsComponent = new OAuthButtons();
    this.errorMessageComponent = new ErrorMessage();
  }

  protected abstract getTitle(): string;
  protected abstract renderForm(): string;
  protected abstract renderFooterLinks(): string;
  protected abstract handleFormSubmit(formData: FormData): Promise<void>;

  mount(selector: string): void {
    const element = document.querySelector(selector);
    if (!element) return;

    // draw the initial layout
    this.render(element);
    this.bindEvents();

    // reset listener before adding a new one
    this.destroy();

    this.languageListener = () => {
      this.render(element);
      this.bindEvents();
    };

    window.addEventListener('languageChanged', this.languageListener);
  }

  private render(element: Element): void {
    const title = this.getTitle();

    element.innerHTML = `
      <div class="flex items-center justify-center min-h-screen px-4 py-10 sm:px-6 lg:px-8">
        <div class="card bg-gray-900 max-w-md w-full p-6 rounded-lg shadow-md space-y-6">
          <h2 class="text-center text-2xl font-semibold text-white">${title}</h2>
          ${this.errorMessageComponent.render()}
          <form id="auth-form" class="mt-6 space-y-5">
            ${this.renderForm()}
            ${this.oauthButtonsComponent.render()}
            ${this.renderFooterLinks()}
          </form>
        </div>
      </div>
    `;
  }

  protected bindEvents(): void {
    const form = document.getElementById('auth-form') as HTMLFormElement | null;
    if (!form) return;

    form.addEventListener('submit', async (event) => {
      event.preventDefault();
      const formData = new FormData(form);
      this.errorMessageComponent.hide();

      try {
        await this.handleFormSubmit(formData);
        window.dispatchEvent(new CustomEvent('navigate', { detail: '/' }));
      } catch (err) {
        const message = (err as Error).message || 'Something went wrong';
        this.errorMessageComponent.show(message);
      }
    });

    // hook up social login buttons
    this.oauthButtonsComponent.bindEvents(this.handleOAuth.bind(this));
  }

  protected handleOAuth(provider: string): void {
    if (provider === 'google') {
      userAuthenticationService.initiateGoogleLogin();
    } else {
      DevConsole.print('⚠️ Unknown OAuth provider:', provider);
    }
  }

  destroy(): void {
    if (this.languageListener) {
      window.removeEventListener('languageChanged', this.languageListener);
      this.languageListener = null;
    }
  }
}
