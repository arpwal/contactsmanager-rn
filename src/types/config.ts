/**
 * Configuration Types
 * These types represent configuration-related data models
 */

// Contact Manager Options Model
export type ContactsManagerOptions = {
  cacheEnabled: boolean;
  cacheTTL?: number;
  sortOrder?: string;
  groupBySource?: boolean;
  includeDeleted?: boolean;
  maxResults?: number;
  searchFuzzyMatching?: boolean;
  syncEnabled?: boolean;
  syncInterval?: number;
  autoMergeContacts?: boolean;
  mergeThreshold?: number;
  storageEncryption?: boolean;
  debug?: boolean;
  logLevel?: string;
  analytics?: boolean;
  crashReporting?: boolean;
};
