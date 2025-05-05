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
