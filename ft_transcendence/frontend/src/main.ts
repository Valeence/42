import './styles/main.css'
import { App } from './app'
import { Router } from './router'
import { userAuthenticationService } from './features/auth/services/userAuthenticationService'
import { ApiConfig } from './config/api.js';
import { DevConsole } from '@/utils/devConsole.js'; 
DevConsole.print('🚀 Application starting...');
ApiConfig.logUrls();
class Main 
{
  private mainApp: App
  private mainRouter: Router
  constructor() 
  {
    this.mainRouter = new Router()
    this.mainApp = new App(this.mainRouter)
    this.init()
  }
  private async init(): Promise<void> 
  {
    await userAuthenticationService.checkAuthStatus();
    this.mainApp.mount('#app');
    this.mainRouter.init();
    DevConsole.print('🚀 Pong 3D frontend started!')
  }
}
new Main();