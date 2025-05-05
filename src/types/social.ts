/**
 * Social Types
 * These types represent social and canonical contact models
 */

import type { Contact } from './contacts';

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
  contact?: Contact;
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

// Follow Relationship Model
export type FollowRelationship = {
  identifier: string;
  followerId: string;
  followedId: string;
  userId: string;
  displayName: string;
  photoURL?: string;
  username?: string;
  bio?: string;
  website?: string;
  createdAt?: number;
  isFollowing: boolean;
  localContact?: Contact;
  follower?: CanonicalContact;
  followed?: CanonicalContact;
  contactId?: string;
};

// Paginated Follow List
export type PaginatedFollowList = {
  items: FollowRelationship[];
  total: number;
  skip: number;
  limit: number;
};

// Paginated Mutual Followers
export type PaginatedMutualFollowers = {
  items: CanonicalContact[];
  total: number;
  skip: number;
  limit: number;
};

// Follow Action Response
export type FollowActionResponse = {
  message?: string;
  alreadyFollowing: boolean;
  wasFollowing: boolean;
  success: boolean;
};

// Follow Status Response
export type FollowStatusResponse = {
  isFollowing: boolean;
};

// Event Creator
export type EventCreator = {
  name?: string;
  avatarUrl?: string;
};

// Social Event
export type SocialEvent = {
  eventId: string;
  organizationId: string;
  canonicalContactId: string;
  eventType: string;
  title: string;
  description?: string;
  location?: string;
  startTime?: number;
  endTime?: number;
  metadata?: Record<string, string>;
  isPublic: boolean;
  createdAt: number;
  updatedAt?: number;
  userId?: string;
  createdBy?: EventCreator;
};

// Paginated Event List
export type PaginatedEventList = {
  items: SocialEvent[];
  total: number;
  skip: number;
  limit: number;
};

// Event Action Response
export type EventActionResponse = {
  message?: string;
  eventId?: string;
  created: boolean;
  updated: boolean;
  deleted: boolean;
  success: boolean;
};

// Create Event Request
export type CreateEventRequest = {
  eventType: string;
  title: string;
  description?: string;
  location?: string;
  startTime?: number;
  endTime?: number;
  metadata?: Record<string, string>;
  isPublic: boolean;
};

// Update Event Request
export type UpdateEventRequest = {
  title?: string;
  description?: string;
  location?: string;
  startTime?: number;
  endTime?: number;
  metadata?: Record<string, string>;
  isPublic?: boolean;
};
