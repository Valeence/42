import { Router } from './router';
import { PrimaryNavigationBar } from '@/shared/layout/PrimaryNavigationBar';

export class App {
  private readonly router: Router;
  private readonly navigationBar: PrimaryNavigationBar;

  constructor(router: Router) {
    this.router = router;
    this.navigationBar = new PrimaryNavigationBar();
  }

  mount(selector: string): void {
    const root = document.querySelector(selector);
    if (!root) {
      throw new Error(`Element with selector ${selector} not found`);
    }

    root.innerHTML = `
      <div class="min-h-screen flex flex-col">
        <header id="header"></header>
        <main id="main-content" class="flex-1 container mx-auto px-4 py-8">
          <div id="page-content"></div>
        </main>
      </div>
    `;

    this.navigationBar.bindTo('#header');
  }
}
