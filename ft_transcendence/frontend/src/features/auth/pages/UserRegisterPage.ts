import { userAuthenticationService } from '../services/userAuthenticationService';
import { LoginPageBase } from '../components/LoginPageBase';
import { AuthFormInput } from '../components/LoginFormInput';
import { AuthSubmitButton } from '../components/LoginSubmitButton';
import { DevConsole } from '@/utils/devConsole.js';

export class UserRegisterPage extends LoginPageBase {
  private submitButton: AuthSubmitButton;

  protected getTitle(): string {
    return 'Create Account';
  }

  constructor() {
    super();
    this.submitButton = new AuthSubmitButton({
      id: 'register-submit',
      text: 'Create Account',
      loadingText: 'Loading...'
    });
  }

  protected bindEvents(): void {
    super.bindEvents();

    const loginLink = document.getElementById('login-link');
    loginLink?.addEventListener('click', (e) => {
      e.preventDefault();
      window.dispatchEvent(new CustomEvent('navigate', { detail: '/login' }));
    });
  }

  protected renderFooterLinks(): string {
    return `
      <div class="text-center mt-4">
        <span class="text-gray-400">Already have an account?</span>
        <a href="#" id="login-link" class="ml-2 text-primary-400 hover:text-primary-300">
          Log In
        </a>
      </div>
    `;
  }

  protected async handleFormSubmit(formData: FormData): Promise<void> {
    const submitBtn = document.getElementById('register-submit') as HTMLButtonElement;
    const submitText = document.getElementById('register-submit-text') as HTMLSpanElement;
    const spinner = document.getElementById('register-submit-spinner') as HTMLElement;

    submitBtn.disabled = true;
    submitText.textContent = 'Loading...';
    spinner.classList.remove('hidden');

    try {
      const username = formData.get('username') as string;
      const email = formData.get('email') as string;
      const password = formData.get('password') as string;
      const confirmPassword = formData.get('confirmPassword') as string;

      if (password !== confirmPassword) {
        throw new Error('Passwords do not match');
      }

      await userAuthenticationService.register(username, email, password);
      window.dispatchEvent(new CustomEvent('navigate', { detail: '/' }));
    } catch (err) {
      DevConsole.reportError('❌ Registration failed:', err);
      this.errorMessageComponent.show((err as Error).message);
      throw err;
    } finally {
      submitBtn.disabled = false;
      submitText.textContent = 'Create Account';
      spinner.classList.add('hidden');
    }
  }

  protected renderForm(): string {
    const userInput = new AuthFormInput({
      id: 'username',
      name: 'username',
      type: 'text',
      required: true,
      label: 'Username',
      placeholder: 'Choose a username'
    });

    const emailInput = new AuthFormInput({
      id: 'email',
      name: 'email',
      type: 'email',
      required: true,
      label: 'Email',
      placeholder: 'Enter your email'
    });

    const passInput = new AuthFormInput({
      id: 'password',
      name: 'password',
      type: 'password',
      required: true,
      label: 'Password',
      placeholder: 'Create a password'
    });

    const confirmPassInput = new AuthFormInput({
      id: 'confirmPassword',
      name: 'confirmPassword',
      type: 'password',
      required: true,
      label: 'Confirm Password',
      placeholder: 'Repeat your password'
    });

    return `
      <div class="space-y-4">
        ${userInput.render()}
        ${emailInput.render()}
        ${passInput.render()}
        ${confirmPassInput.render()}
      </div>
      ${this.submitButton.render()}
    `;
  }
}
