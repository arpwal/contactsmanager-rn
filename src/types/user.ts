/**
 * User and Device Types
 * These types represent user information and device details
 */

// User Info Model
export type UserInfo = {
  userId: string;
  email: string;
  name?: string;
  avatarUrl?: string;
  organizationId?: string;
  organizationRole?: string;
  lastLoginAt?: number;
  userSettings?: Record<string, any>;
  metadata?: Record<string, any>;
};

// Device Info Model
export type DeviceInfo = {
  deviceId: string;
  deviceName: string;
  deviceModel?: string;
  deviceType?: string;
  osName: string;
  osVersion: string;
  appVersion: string;
  appBuild: string;
  locale: string;
  timezone: string;
  lastSyncedAt?: number;
  lastActivityAt?: number;
  isActive: boolean;
  deviceSettings?: Record<string, any>;
  metadata?: Record<string, any>;
};
