/**
 * Server Types
 * These types represent server-related data models
 */

// Organization Model
export type Organization = {
  id: string;
  name: string;
  domain?: string;
  planId?: string;
  isActive: boolean;
  createdAt: number;
  updatedAt: number;
  settings?: Record<string, any>;
  metadata?: Record<string, any>;
};

// Organization User Model
export type OrganizationUser = {
  id: string;
  organizationId: string;
  userId: string;
  role: string;
  permissions: string[];
  isActive: boolean;
  createdAt: number;
  updatedAt: number;
  lastLoginAt?: number;
  metadata?: Record<string, any>;
};

// API Key Model
export type ApiKey = {
  id: string;
  organizationId: string;
  name: string;
  key: string;
  permissions: string[];
  expiresAt?: number;
  isActive: boolean;
  createdAt: number;
  updatedAt: number;
  lastUsedAt?: number;
  metadata?: Record<string, any>;
};

// Sync Job Model
export type SyncJob = {
  id: string;
  organizationId: string;
  sourceId: string;
  userId?: string;
  jobType: string;
  status: string;
  progress?: number;
  startedAt?: number;
  completedAt?: number;
  nextRunAt?: number;
  errorMessage?: string;
  result?: Record<string, any>;
  metadata?: Record<string, any>;
};

// Webhook Model
export type Webhook = {
  id: string;
  organizationId: string;
  url: string;
  events: string[];
  isActive: boolean;
  secret?: string;
  createdAt: number;
  updatedAt: number;
  lastCalledAt?: number;
  failureCount?: number;
  metadata?: Record<string, any>;
};

// New types from CMServerModels.h

// Server Contact Bulk Create
export type ServerContactBulkCreate = {
  contacts: ServerContact[];
  skipDuplicates: boolean;
};

// Server Contact Date
export type ServerContactDate = {
  identifier?: string;
  label: string;
  date: string; // ISO 8601 date string
  isPrimary: boolean;
};

// Server Contact Instant Message
export type ServerContactInstantMessage = {
  identifier?: string;
  service: string;
  username?: string;
  userIdentifier?: string;
  type: string;
  isPrimary: boolean;
};

// Server Contact Relation
export type ServerContactRelation = {
  identifier?: string;
  name: string;
  relationType: string;
  notes?: string;
};

// Server Contact Phone Number
export type ServerContactPhoneNumber = {
  identifier?: string;
  type: string;
  label: string;
  value: string;
  isPrimary: boolean;
  emoji?: string;
  phoneId?: string;
};

// Server Contact Email Address
export type ServerContactEmailAddress = {
  identifier?: string;
  type: string;
  label: string;
  value: string;
  isPrimary: boolean;
  emoji?: string;
  emailId?: string;
};

// Server Contact URL Address
export type ServerContactURLAddress = {
  identifier?: string;
  type: string;
  label: string;
  value: string;
  isPrimary: boolean;
  emoji?: string;
  urlId?: string;
};

// Server Contact Social Profile
export type ServerContactSocialProfile = {
  identifier?: string;
  platform: string;
  username?: string;
  url?: string;
};

// Server Contact Address
export type ServerContactAddress = {
  identifier?: string;
  type?: string;
  label: string;
  streetAddress?: string;
  extendedAddress?: string;
  city?: string;
  region?: string;
  postalCode?: string;
  country?: string;
  isPrimary: boolean;
};

// Server Contact
export type ServerContact = {
  identifier?: string;
  displayName: string;
  givenName?: string;
  familyName?: string;
  namePrefix?: string;
  nameSuffix?: string;
  middleName?: string;
  previousFamilyName?: string;
  nickname: string;
  notes: string;
  bio?: string;
  location?: string;
  contactSection?: string;
  organizationId: string;
  sourceId: string;
  sourceContactId?: string;
  phoneNumbers: ServerContactPhoneNumber[];
  emailAddresses: ServerContactEmailAddress[];
  urls: ServerContactURLAddress[];
  socialProfiles: ServerContactSocialProfile[];
  addresses: ServerContactAddress[];
  instantMessageAddresses: ServerContactInstantMessage[];
  relations: ServerContactRelation[];
  tags: string[];
  customFields: Record<string, string>;
  matchString?: string;

  // Organization information
  organizationName?: string;
  departmentName?: string;
  jobTitle?: string;

  // Dates
  birthday?: string; // ISO 8601 date string
  dates: ServerContactDate[];

  // Contact type
  contactType: number; // 0 = person, 1 = organization
};
