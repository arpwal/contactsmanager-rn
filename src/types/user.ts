/**
 * User and Device Types
 * These types represent user information and device details
 */

// User Info Model
export type UserInfo = {
  userId: string;
  fullName?: string;
  email?: string;
  phone?: string;
  avatarUrl?: string;
  metadata?: Record<string, string>;
};

// Device Info Model
export type DeviceInfo = {
  // Device identifiers
  deviceId: string;
  hardwareId: string;

  // Hardware information
  deviceName: string;
  deviceModel: string;
  deviceManufacturer: string;
  deviceModelId: string;

  // OS information
  osName: string;
  osVersion: string;

  // Display information
  screenWidth: number;
  screenHeight: number;
  screenDensity: number;

  // Network information
  networkType: string;

  // App information
  appVersion: string;
  appBuild: string;
  appId: string;

  // Locale information
  locale: string;
  timezone: string;

  // Hardware capabilities
  totalMemory?: number;
  cpuCount?: number;
  batteryLevel?: number;
  isCharging?: boolean;

  // Additional fields from existing model (preserved)
  deviceType?: string;
  lastSyncedAt?: number;
  lastActivityAt?: number;
  isActive?: boolean;
  deviceSettings?: Record<string, any>;
  metadata?: Record<string, any>;
};
