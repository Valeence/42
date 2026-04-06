import type { ProfileRenderSections } from '@/types/index.js';

export class ProfileLayout {
  constructor(
    private ownProfile: boolean,
    private profileComponents: ProfileRenderSections
  ) {}

  render(): string {
    return this.ownProfile ? this.renderOwnProfileLayout() : this.renderOtherProfileLayout();
  }

  private renderOwnProfileLayout(): string {
    const headerHtml = this.profileComponents.header.render();
    const statsHtml = this.profileComponents.stats.render();
    const historyHtml = this.profileComponents.history?.render() ?? '';
    const friendsHtml = this.profileComponents.friends?.render() ?? '';

    return `
      <div class="min-h-screen">
        <div class="max-w-6xl mx-auto px-4 py-8">
          <div class="grid grid-cols-1 xl:grid-cols-3 gap-8">
            <div class="xl:col-span-2 space-y-8">
              ${headerHtml}
              ${statsHtml}
              ${historyHtml}
            </div>
            <div class="space-y-8">
              ${friendsHtml}
            </div>
          </div>
        </div>
      </div>
    `;
  }

  private renderOtherProfileLayout(): string {
    const headerHtml = this.profileComponents.header.render();
    const statsHtml = this.profileComponents.stats.render();

    return `
      <div class="min-h-screen">
        <div class="max-w-4xl mx-auto px-4 py-8">
          <div class="space-y-8">
            ${headerHtml}
            ${statsHtml}
          </div>
        </div>
      </div>
    `;
  }

  bindEvents(onFriendAction?: (action: string) => Promise<void>): void {
    if (!this.ownProfile && onFriendAction) {
      this.profileComponents.header.bindEvents({ onFriendAction });
    }
    this.profileComponents.friends?.bindEvents();
  }
}
