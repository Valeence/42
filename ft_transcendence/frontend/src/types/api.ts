export interface ServicePayload<T = any> {
  success: boolean;
  data?: T;
  message?: string;
  error?: string;
}
export interface PaginatedPayload<T> {
  data: T[];
  total: number;
  page: number;
  limit: number;
  totalPages: number;
}
export interface ServiceErrorInfo {
  status: number;
  message: string;
  code?: string;
}
