/**
 * Social Types
 * These types represent social and canonical contact models
 */

// Canonical Contact Model
export type CanonicalContact = {
  identifier: string;
  organizationId?: string;
  organizationUserId: string;
  email?: string;
  phone?: string;
  fullName: string;
  avatarUrl?: string;
  isActive: boolean;
  createdAt?: number;
  updatedAt?: number;
  contactMetadata?: Record<string, any>;
};

// Local Canonical Contact Mapping
export type LocalCanonicalContact = {
  contactId: string;
  sourceContactId: string;
  canonicalContact: CanonicalContact;
};

// Social Response Model
export type SocialResponse<T = any> = {
  status: string;
  message?: string;
  data: T;
};
