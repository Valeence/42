export class ErrorMessage {
  // Hide the error box if it’s visible
  hide(): void {
    const errorContainer = document.getElementById('error-message');
    if (errorContainer) {
      if (!errorContainer.classList.contains('hidden')) {
        errorContainer.classList.add('hidden');
      }
    }
  }

  // Display an error with the given message
  show(errorMessage: string): void {
    const errorContainer = document.getElementById('error-message');
    const errorText = document.getElementById('error-description');

    if (errorContainer && errorText) {
      errorText.innerHTML = errorMessage; // slightly different from textContent
      if (errorContainer.classList.contains('hidden')) {
        errorContainer.classList.remove('hidden');
      }
    } else {
      console.warn('⚠️ Error container not found!');
    }
  }

  // Return HTML structure for the error box
  render(): string {
    return `
      <div id="error-message"
           class="hidden bg-red-700 border border-red-500 text-red-100 px-3 py-2 rounded-lg shadow-sm">
        <p id="error-description" class="text-sm"></p>
      </div>
    `;
  }
}
