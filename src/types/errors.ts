/**
 * Error Types
 * These types represent error models and codes
 */

// Error Codes Enum
export enum ErrorCode {
  // General Errors (1-99)
  Unknown = 1,
  InvalidParameter = 2,
  NetworkError = 3,
  ServerError = 4,
  Unauthorized = 5,
  Forbidden = 6,
  NotFound = 7,
  Timeout = 8,

  // Contact Errors (100-199)
  ContactNotFound = 100,
  ContactInvalid = 101,
  ContactDuplicate = 102,
  ContactSyncFailed = 103,

  // Source Errors (200-299)
  SourceNotFound = 200,
  SourceInvalid = 201,
  SourceAuthFailed = 202,
  SourceSyncFailed = 203,
  SourceLimitExceeded = 204,

  // Permission Errors (300-399)
  PermissionDenied = 300,
  ContactsPermissionDenied = 301,

  // Data Errors (400-499)
  DataCorruption = 400,
  StorageError = 401,
  DatabaseError = 402,

  // API Errors (500-599)
  APIError = 500,
  APIRateLimitExceeded = 501,
  APIResponseInvalid = 502,
}

// Error Object Model
export type ContactsError = {
  code: ErrorCode;
  message: string;
  underlyingError?: any;
};
