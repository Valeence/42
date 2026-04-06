import { userAuthenticationService } from '@/features/auth/services/userAuthenticationService';
import { HomePage } from '@/features/home/pages/MainPage';
import { UserLoginPage } from '@/features/auth/pages/UserLoginPage';
import { UserRegisterPage } from '@/features/auth/pages/UserRegisterPage';
import { GamePage } from '@/features/game/pages/PongGamePage';
import { ProfilePage } from '@/features/profile/pages/UserProfilePage';
import { TournamentCreatePage } from '@/features/tournament/pages/CompetitionCreatePage';
import { TournamentPage } from '@/features/tournament/pages/CompetitionPage';
import { NotFoundPage } from '@/features/home/pages/Error404Page'; 
import type { AppRouteEntry } from '@/types/index.js';
export class Router 
{
  private currentPage: any = null;
  private routes: AppRouteEntry[] = [
    {
      path: '/',
      component: () => new HomePage(),
      title: 'Home - Pong 3D',
      requiresAuth: false
    },
    {
      path: '/login',
      component: () => new UserLoginPage(),
      title: 'Login - Pong 3D',
      requiresAuth: false
    },
    {
      path: '/register',
      component: () => new UserRegisterPage(),
      title: 'Register - Pong 3D',
      requiresAuth: false
    },
    {
      path: '/game',
      component: () => new GamePage(),
      title: 'Pong 3D',
      requiresAuth: false
    },
    {
      path: '/profile',
      component: () => new ProfilePage(),
      title: 'Profile - Pong 3D',
      requiresAuth: true
    },
    {
      path: '/profile/:id',
      component: () => new ProfilePage(),
      title: 'Profile - Pong 3D',
      requiresAuth: true
    },
    {
      path: '/tournament/create',
      component: () => new TournamentCreatePage(),
      title: 'Create Tournament - Pong 3D',
      requiresAuth: false
    },
    {
      path: '/tournament/:id',
      component: () => new TournamentPage(),
      title: 'Tournament - Pong 3D',
      requiresAuth: false
    }
  ];
  private get notFoundRoute(): AppRouteEntry {
    return {
      path: '*',
      component: () => new NotFoundPage(),
      title: '404 - Page Not Found - Pong 3D',
      requiresAuth: false
    };
  }
  async navigate(path: string): Promise<void> 
  {
    window.dispatchEvent(new CustomEvent('beforeNavigate', { detail: path }));
    history.pushState({}, '', path);
    await this.handleRoute();
  }
  async handleRoute(): Promise<void> 
  {
    const path = window.location.pathname;
    let matchedRoute = this.routes.find(r => r.path === path);
    if (!matchedRoute) 
    {
      for (const route of this.routes) 
      {
        if (route.path.includes(':')) 
        {
          const pathPattern = route.path.replace(/:[^/]+/g, '([^/]+)'); 
          const regex = new RegExp(`^${pathPattern}$`);
          if (regex.test(path))
          {
            matchedRoute = route;
            break;
          }
        }
      }
    }
    const route = matchedRoute || this.notFoundRoute;
    if (route.requiresAuth) 
    {
      const isAuthenticated = await userAuthenticationService.checkAuthStatus();
      if (!isAuthenticated) 
      {
        this.navigate('/login');
        return;
      }
    }
    if ((path === '/login' || path === '/register')) 
    {
      const isAuthenticated = await userAuthenticationService.checkAuthStatus();
      if (isAuthenticated) 
      {
        this.navigate('/');
        return;
      }
    }
    document.title = route.title;
    if (this.currentPage && typeof this.currentPage.destroy === 'function')
    {
      this.currentPage.destroy();
    }
    const component = route.component();
    this.currentPage = component;
    component.mount('#page-content');
  }
  init(): void 
{
    window.addEventListener('popstate', () => {
      this.handleRoute();
    });
    window.addEventListener('navigate', (event: CustomEvent) => {
      this.navigate(event.detail);
    });
    this.handleRoute();
  }
}
