// Re-export all model types
export * from './contacts';
export * from './sources';
export * from './social';
export * from './user';
export * from './errors';
export * from './server';
export * from './config';

import type { Contact } from './contacts';

// Maintain backward compatibility with existing code
export enum ContactsAccessStatus {
  NotDetermined = 0,
  Authorized = 1,
  LimitedAuthorized = 2,
  Denied = 3,
  Restricted = 4,
}

// Simplified Contact Types (backward compatibility)
export type PhoneNumber = {
  label: string; // Maps to 'type' in ContactPhoneNumber
  number: string; // Maps to 'value' in ContactPhoneNumber
};

export type EmailAddress = {
  label: string; // Maps to 'type' in ContactEmailAddress
  email: string; // Maps to 'value' in ContactEmailAddress
};

// Simplified Contact Model (backward compatibility)
export type SimplifiedContact = {
  contactId: string; // Maps to 'identifier' in Contact
  displayName: string;
  givenName: string;
  familyName: string;
  phoneNumbers: PhoneNumber[];
  emailAddresses: EmailAddress[];
  thumbnailImageData?: string; // Maps to avatars[0].data in Contact
};

// Result Types
export type ContactsAccessResult = {
  granted: boolean;
  status: ContactsAccessStatus;
};

// Search Result Types
export type SearchResult = {
  contacts: Contact[];
  totalCount: number;
};

// ContactsManagerOptions for initialization
export type ContactsManagerOptions = {
  cacheEnabled?: boolean;
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
