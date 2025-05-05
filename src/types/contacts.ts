/**
 * Contact Types
 * These types represent the core contact data structures
 */

// Contact Field Type Enum
export enum ContactFieldType {
  Any = 0,    // All available fields
  Phone = 1,  // Only phone numbers
  Email = 2,  // Only email addresses
  Notes = 3   // Only notes
}

// Enhanced Contact Detail Types
// Note: Basic types (PhoneNumber and EmailAddress) are already defined in index.ts
export type ContactPhoneNumber = {
  contactId: string;
  value: string;
  type?: string;
  emoji?: string;
};

export type ContactEmailAddress = {
  contactId: string;
  value: string;
  type?: string;
  emoji?: string;
};

// Additional Contact Detail Types
export type ContactAddress = {
  contactId: string;
  street?: string;
  city?: string;
  state?: string;
  postalCode?: string;
  country?: string;
  type?: string;
  emoji?: string;
};

export type ContactDate = {
  contactId: string;
  date: number; // timestamp
  type?: string;
};

export type ContactURL = {
  contactId: string;
  value: string;
  type?: string;
  emoji?: string;
};

export type ContactSocialProfile = {
  contactId: string;
  service: string;
  username?: string;
  urlString?: string;
};

export type ContactRelation = {
  contactId: string;
  name: string;
  type?: string;
};

export type ContactInstantMessage = {
  contactId: string;
  service: string;
  username: string;
  type?: string;
};

export type ContactAvatar = {
  contactId: string;
  data?: string; // base64 encoded image data
  url?: string;
};

// Complete Contact Model
export type Contact = {
  identifier: string;
  displayName?: string;

  // Basic information
  contactType?: number;
  namePrefix?: string;
  givenName?: string;
  middleName?: string;
  familyName?: string;
  previousFamilyName?: string;
  nameSuffix?: string;
  nickname?: string;

  // Organization details
  organizationName?: string;
  departmentName?: string;
  jobTitle?: string;

  // Contact information collections
  phoneNumbers: ContactPhoneNumber[];
  emailAddresses: ContactEmailAddress[];
  addresses: ContactAddress[];
  dates: ContactDate[];
  urlAddresses: ContactURL[];
  socialProfiles: ContactSocialProfile[];
  relations: ContactRelation[];
  instantMessageAddresses: ContactInstantMessage[];

  // Additional information
  notes?: string;
  bio?: string;
  location?: string;

  // Birthday
  birthday?: number; // timestamp

  // Image data
  imageUrl?: string;
  imageData?: string; // base64 encoded
  thumbnailImageData?: string; // base64 encoded
  imageDataAvailable?: boolean;

  // Extra data
  interests: string[];
  avatars: ContactAvatar[];

  // Sync information
  isDeleted: boolean;
  dirtyTime?: number;
  lastSyncedAt?: number;

  // Additional properties
  contactSection: string;
  matchString: string;
  parentContactId?: string;
  sourceId?: string;
  createdAt: number;
};
