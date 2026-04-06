interface ImportMetaEnv {
  readonly PROD: boolean
  readonly DEV: boolean
  readonly MODE: string
  readonly VITE_API_URL?: string
  readonly VITE_WS_URL?: string
}
interface ImportMeta {
  readonly env: ImportMetaEnv
}
declare var process: {
  env: {
    NODE_ENV?: string
    [key: string]: string | undefined
  }
}
