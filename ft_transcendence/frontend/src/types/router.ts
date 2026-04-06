export interface AppRouteEntry {
  path: string;
  component: () => any;
  title: string;
  requiresAuth: boolean;
}
