export interface FormInputConfig {
  name: string;
  id: string;
  type: string;
  label?: string;
  placeholder?: string;
  required?: boolean;
}

export class AuthFormInput {
  render(): string {
    // basic UI for an input field
    const field = this.inputConfig;

    const labelText = field.label ? `
      <label for="${field.id}" class="text-sm text-white block mb-1">
        ${field.label}
      </label>` : '';

    const requiredAttr = field.required ? 'required' : '';
    const placeholderText = field.placeholder || '';

    return `
      <div class="my-2">
        ${labelText}
        <input
          id="${field.id}"
          name="${field.name}"
          type="${field.type}"
          ${requiredAttr}
          placeholder="${placeholderText}"
          class="form-field w-full px-3 py-2 border border-gray-600 bg-gray-900 text-gray-100 rounded-md"
        />
      </div>
    `;
  }

  constructor(private inputConfig: FormInputConfig) {
    // could add a simple validation check here later if needed
  }
}
