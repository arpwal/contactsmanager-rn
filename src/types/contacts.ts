/**
 * Contact Types
 * These types represent the core contact data structures
 */

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
};

export type ContactAvatar = {
  contactId: string;
  data?: string; // base64 encoded image data
  url?: string;
};

// Complete Contact Model
export type Contact = {
  identifier: string;
  displayName: string;
  givenName?: string;
  middleName?: string;
  familyName?: string;
  previousFamilyName?: string;
  nickname?: string;
  organizationName?: string;
  departmentName?: string;
  jobTitle?: string;
  note?: string;
  phoneNumbers: ContactPhoneNumber[];
  emailAddresses: ContactEmailAddress[];
  addresses: ContactAddress[];
  dates: ContactDate[];
  urlAddresses: ContactURL[];
  socialProfiles: ContactSocialProfile[];
  relations: ContactRelation[];
  instantMessageAddresses: ContactInstantMessage[];
  interests: string[];
  avatars: ContactAvatar[];
  isDeleted: boolean;
  createdAt: number;
  dirtyTime?: number;
  contactSection: string;
  matchString: string;
};
