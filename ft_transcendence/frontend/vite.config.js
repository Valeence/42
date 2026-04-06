import { defineConfig } from 'vite'
import tailwindcss from '@tailwindcss/vite'

export default defineConfig({
  plugins: [tailwindcss()],
  resolve: {
    alias: {
      '@': '/src',
      '@config': '/src/config',
      '@features': '/src/features',
      '@shared': '/src/shared',
      '@styles': '/src/styles',
      '@types': '/src/types',
      '@utils': '/src/utils'
    }
  }
})
