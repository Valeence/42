export class OAuthButtons {
  bindEvents(onOAuthCallback: (provider: string) => void): void {
    const googleBtn = document.getElementById('oauth-google');
    if (googleBtn) {
      googleBtn.addEventListener('click', () => onOAuthCallback('google'));
    } else {
      console.warn('⚠️ Google OAuth button not found!');
    }
  }

  render(): string {
    // small separator + google button area
    return `
      <div class="my-5">
        <div class="relative mb-4">
          <div class="flex items-center">
            <div class="flex-grow border-t border-gray-600"></div>
            <span class="mx-3 text-sm text-gray-400 bg-gray-900 px-2">or</span>
            <div class="flex-grow border-t border-gray-600"></div>
          </div>
        </div>

        <div class="grid gap-2">
          <button 
            id="oauth-google"
            type="button"
            class="w-full flex items-center justify-center py-2 px-4 rounded-md bg-gray-700 hover:bg-gray-600 border border-gray-500 text-gray-200 text-sm font-semibold"
          >
            Sign in with Google
          </button>
        </div>
      </div>
    `;
  }
}
