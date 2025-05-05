/**
 * Source Types
 * These types represent contact sources and related data structures
 */

// Source Type Enum
export enum SourceType {
  Google = 'google',
  Outlook = 'outlook',
  CSV = 'csv',
  API = 'api',
  Device = 'device',
  Other = 'other',
}

// Contact Source Model
export type ContactSource = {
  identifier: string;
  sourceIdentifier?: string;
  sourceId: string;
  name: string;
  sourceType: SourceType;
  organizationId: string;
  canonicalContactId: string;
  isActive: boolean;
  lastSyncAt?: number;
  syncError?: string;
  credentials?: Record<string, any>;
  settings?: Record<string, any>;
  sourceMetadata?: Record<string, any>;
  createdAt: number;
  updatedAt: number;

  // Additional fields from existing model (preserved)
  isSyncEnabled?: boolean;
  syncInterval?: number;
  syncScope?: string;
  errorCount?: number;
  lastError?: string;
  lastErrorAt?: number;
};

// Sync Info Model
export type ContactSyncInfo = {
  sourceId: string;
  contactId: string;
  sourceContactId: string;
  syncToken?: string;
  syncHash?: string;
  lastSyncedAt: number;
  lastModifiedAt: number;
  isDeleted: boolean;
  remoteData?: Record<string, any>;
};

// Contact Sync Status
export enum SyncStatus {
  NotSynced = 'not_synced',
  Syncing = 'syncing',
  Synced = 'synced',
  Failed = 'failed',
  Conflicted = 'conflicted',
}

// Contact Source Extension
export type ContactSourceSync = {
  sourceId: string;
  status: SyncStatus;
  syncStartedAt?: number;
  syncCompletedAt?: number;
  syncProgress?: number;
  syncError?: string;
  totalContacts?: number;
  syncedContacts?: number;
  newContacts?: number;
  updatedContacts?: number;
  deletedContacts?: number;
  conflictedContacts?: number;
};
