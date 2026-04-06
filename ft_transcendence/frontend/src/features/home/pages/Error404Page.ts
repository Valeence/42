import { DevConsole } from '@/utils/devConsole.js'; 

export class NotFoundPage
{
  async mount(selector: string): Promise<void>
  {
    const el = document.querySelector(selector);
    if (!el) return;
    this.render(el);
    this.setupEventListeners();
    this.bindEvents();
  }

  private render(element: Element): void
  {
    DevConsole.print('🎨 Rendering 404 page');
    const path = window.location.pathname;
    element.innerHTML = `
      <div class="min-h-screen text-white flex items-center justify-center">
        <div class="text-center max-w-2xl mx-auto px-4">
          <div class="mb-8 animate-bounce">
            <div class="text-9xl font-bold text-primary-500 mb-4">404</div>
            <div class="text-6xl mb-4">🏓</div>
          </div>
          <h1 class="text-4xl font-bold text-white mb-4">
            Page Not Found
          </h1>
          <p class="text-xl text-gray-300 mb-8">
            The page you're looking for doesn't exist or has been moved.
          </p>
          <div class="bg-gray-800/50 rounded-lg p-6 mb-8">
            <h2 class="text-lg font-semibold text-gray-200 mb-4">
              Try these pages instead:
            </h2>
            <div class="grid grid-cols-1 md:grid-cols-3 gap-4">
              <a href="/" id="home-link" class="action-primary text-center block">🏠 Home</a>
              <a href="/game" id="game-link" class="action-secondary text-center block">🎮 Play</a>
              <a href="/tournament/create" id="tournament-link" class="action-secondary text-center block">🏆 Create Tournament</a>
            </div>
          </div>
          <button id="back-button" class="action-secondary mb-8">⬅️ Back</button>
          <div class="text-sm text-gray-400">
            <p class="mb-2">
              If you think this is an error, please check the URL or contact support.
            </p>
            <p>URL: <code class="bg-gray-700 px-2 py-1 rounded">${path}</code></p>
          </div>
        </div>
      </div>
    `;
  }

  private bindEvents(): void
  {
    DevConsole.print('🎯 Binding navigation events');
    
    const navMap: { [key: string]: string } = {
      'home-link': '/',
      'game-link': '/game',
      'tournament-link': '/tournament/create'
    };

    Object.entries(navMap).forEach(([id, route]) => {
      document.getElementById(id)?.addEventListener('click', e => {
        e.preventDefault();
        DevConsole.print(`🔀 Navigating to ${route} from 404`);
        window.dispatchEvent(new CustomEvent('navigate', { detail: route }));
      });
    });

    document.getElementById('back-button')?.addEventListener('click', () => {
      DevConsole.print('⬅️ Back button clicked');
      if (window.history.length > 1) window.history.back();
      else window.dispatchEvent(new CustomEvent('navigate', { detail: '/' }));
    });
  }

  private setupEventListeners(): void
  {
    DevConsole.print('🎧 Setting up page-level event listeners');
  }

  destroy(): void
  {
    DevConsole.print('🧹 Destroying NotFoundPage and cleaning up listeners');
  }
}
