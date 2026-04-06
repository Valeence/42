import { userAuthenticationService } from '../services/userAuthenticationService';
import { LoginPageBase } from '../components/LoginPageBase';
import { AuthFormInput } from '../components/LoginFormInput';
import { AuthSubmitButton } from '../components/LoginSubmitButton';
import { TwoFactorAuthModal } from '../components/TwoFactorAuthModal.js';
import { TwoFactorRequiredProblem } from '@/types/index.js';
import { DevConsole } from '@/utils/devConsole.js';

export class UserLoginPage extends LoginPageBase {
  private submitButton: AuthSubmitButton;

  constructor() {
    super();
    this.submitButton = new AuthSubmitButton({
      id: 'login-submit',
      text: 'Log In',
      loadingText: 'Logging in...'
    });
  }

  protected getTitle(): string {
    return 'Login';
  }

  protected renderForm(): string {
    const userInput = new AuthFormInput({
      id: 'username',
      name: 'username',
      type: 'text',
      required: true,
      label: 'Username',
      placeholder: 'Enter your username'
    });

    const passInput = new AuthFormInput({
      id: 'password',
      name: 'password',
      type: 'password',
      required: true,
      label: 'Password',
      placeholder: 'Enter your password'
    });

    return `
      <div class="space-y-4">
        ${userInput.render()}
        ${passInput.render()}
      </div>
      ${this.submitButton.render()}
    `;
  }

  protected renderFooterLinks(): string {
    return `
      <div class="text-center mt-4">
        <span class="text-gray-400">Don't have an account?</span>
        <a href="#" id="register-link" class="ml-2 text-primary-400 hover:text-primary-300">
          Sign Up
        </a>
      </div>
    `;
  }

  protected bindEvents(): void {
    super.bindEvents();

    const registerLink = document.getElementById('register-link');
    registerLink?.addEventListener('click', (e) => {
      e.preventDefault();
      window.dispatchEvent(new CustomEvent('navigate', { detail: '/register' }));
    });

    const forgotLink = document.getElementById('forgot-password-link');
    forgotLink?.addEventListener('click', (e) => e.preventDefault());
  }

  protected async handleFormSubmit(formData: FormData): Promise<void> {
    const submitBtn = document.getElementById('login-submit') as HTMLButtonElement;
    const submitText = document.getElementById('login-submit-text') as HTMLSpanElement;
    const spinner = document.getElementById('login-submit-spinner') as HTMLElement;

    submitBtn.disabled = true;
    submitText.textContent = 'Loading...';
    spinner.classList.remove('hidden');

    try {
      const username = formData.get('username') as string;
      const password = formData.get('password') as string;

      await userAuthenticationService.login(username, password);
      window.dispatchEvent(new CustomEvent('navigate', { detail: '/' }));
    } catch (err) {
      if (err instanceof TwoFactorRequiredProblem) {
        this.openTwoFactorModal(err.userId);
      } else {
        this.errorMessageComponent.show((err as Error).message);
        throw err;
      }
    } finally {
      submitBtn.disabled = false;
      submitText.textContent = 'Log In';
      spinner.classList.add('hidden');
    }
  }

  private openTwoFactorModal(userId: number): void {
    const modal = new TwoFactorAuthModal(
      'login',
      async (code: string) => {
        try {
          await userAuthenticationService.loginWith2FA(userId, code);
          window.dispatchEvent(new CustomEvent('navigate', { detail: '/' }));
        } catch (err) {
          throw new Error((err as Error).message);
        }
      },
      () => {
        DevConsole.print('2FA cancelled');
      }
    );

    modal.show();
  }
}
