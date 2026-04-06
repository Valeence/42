export interface ButtonConfig {
  text: string;
  id: string;
  loadingText: string;
}

export class AuthSubmitButton {
  render(): string {
    const button = this.buttonConfig;
    const spinnerId = `${button.id}-spinner`;
    const textId = `${button.id}-text`;

    // basic submit button template
    return `
      <div class="mt-4 text-center">
        <button 
          id="${button.id}" 
          type="submit" 
          class="w-full relative bg-blue-600 hover:bg-blue-700 text-white font-medium py-2 px-4 rounded"
        >
          <span id="${spinnerId}" class="hidden absolute left-4 top-1/2 -translate-y-1/2">
            <div class="h-4 w-4 border-2 border-white border-t-transparent rounded-full animate-spin"></div>
          </span>
          <span id="${textId}">${button.text}</span>
        </button>
      </div>
    `;
  }

  constructor(private buttonConfig: ButtonConfig) {
    // could maybe toggle spinner visibility later
  }
}
