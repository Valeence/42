import type { User } from '@/features/auth/types/userAuthTypes.js';

export interface FriendRequest {
  status: 'pending' | 'accepted' | 'declined';
  id: number;
  receiverId: number;
  senderId: number;
  createdAt: string;
  receiver?: User;
  sender?: User;
}

export interface FriendshipStatus {
  requestId?: number;
  isFriend: boolean;
}

export interface Friend {
  username: string;
  id: number;
  isOnline: boolean;
  avatarUrl?: string | null;
  friendshipDate: string;
  lastSeen?: string;
}