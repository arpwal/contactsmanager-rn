import { NativeModules } from 'react-native';
import type { Contact, ContactFieldType, UserInfo } from '../types';

// Direct access to the native module
const { RNContactService } = NativeModules;

/**
 * Interface for contactsService options
 */
interface ContactsManagerOptions {
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
}

/**
 * Initialize the ContactsManager with API key, token, and user information
 * @param apiKey API key for the ContactsManager service
 * @param token Authentication token
 * @param userInfo User information for initialization
 * @param options Additional options for initialization
 * @returns Promise resolving to success status
 */
export function initialize(
  apiKey: string,
  token: string,
  userInfo: UserInfo,
  options?: ContactsManagerOptions
): Promise<{ success: boolean }> {
  console.log('Initializing ContactService...');
  return RNContactService.initialize(apiKey, token, userInfo, options || {});
}

/**
 * Check if the service is initialized
 * @returns Promise resolving to a boolean indicating initialization status
 */
export function isInitialized(): Promise<boolean> {
  console.log('Checking if ContactService is initialized...');
  return RNContactService.isInitialized();
}

/**
 * Get the current state of the service
 * @returns Promise resolving to a string with the current state
 */
export function currentState(): Promise<string> {
  console.log('Getting ContactService current state...');
  return RNContactService.currentState();
}

/**
 * Reset the service
 * @returns Promise resolving to success status
 */
export function reset(): Promise<{ success: boolean }> {
  console.log('Resetting ContactService...');
  return RNContactService.reset();
}

/**
 * Request access to contacts
 * @returns Promise resolving to granted status
 */
export function requestContactsAccess(): Promise<{ granted: boolean }> {
  console.log('Requesting contacts access via ContactService...');
  return RNContactService.requestContactsAccess();
}

/**
 * Get the current contacts access status
 * @returns Promise resolving to a numeric status code
 */
export function contactsAccessStatus(): Promise<number> {
  console.log('Checking contacts access status via ContactService...');
  return RNContactService.contactsAccessStatus();
}

/**
 * Fetch all contacts
 * @returns Promise resolving to an array of contacts
 */
export function fetchContacts(): Promise<Contact[]> {
  console.log('Fetching contacts...');
  return RNContactService.fetchContacts();
}

/**
 * Fetch contacts with a specific field type filter
 * @param fieldType The type of fields to fetch
 * @returns Promise resolving to an array of contacts
 */
export function fetchContactsWithFieldType(
  fieldType: ContactFieldType
): Promise<Contact[]> {
  console.log(`Fetching contacts with fieldType: ${fieldType}...`);
  return RNContactService.fetchContactsWithFieldType(fieldType);
}

/**
 * Fetch contacts in batches
 * @param batchSize The number of contacts to fetch per batch
 * @param batchIndex The index of the batch (0-based)
 * @returns Promise resolving to an array of contacts
 */
export function fetchContactsWithBatch(
  batchSize: number,
  batchIndex: number
): Promise<Contact[]> {
  console.log(
    `Fetching contacts with batchSize: ${batchSize}, batchIndex: ${batchIndex}...`
  );
  return RNContactService.fetchContactsWithBatch(batchSize, batchIndex);
}

/**
 * Fetch a single contact by ID
 * @param id The identifier of the contact to fetch
 * @returns Promise resolving to a contact
 */
export function fetchContactWithId(id: string): Promise<Contact> {
  console.log(`Fetching contact with ID: ${id}...`);
  return RNContactService.fetchContactWithId(id);
}

/**
 * Get the total count of contacts
 * @returns Promise resolving to the count
 */
export function getContactsCount(): Promise<number> {
  console.log('Getting contacts count...');
  return RNContactService.getContactsCount();
}

/**
 * Enable background sync
 * @returns Promise resolving to success status
 */
export function enableBackgroundSync(): Promise<boolean> {
  console.log('Enabling background sync...');
  return RNContactService.enableBackgroundSync();
}

/**
 * Schedule a background sync task
 * @returns Promise resolving to success status
 */
export function scheduleBackgroundSyncTask(): Promise<boolean> {
  console.log('Scheduling background sync task...');
  return RNContactService.scheduleBackgroundSyncTask();
}

/**
 * Check the health of the service
 * @returns Promise resolving to health status
 */
export function checkHealth(): Promise<{ healthy: boolean }> {
  console.log('Checking ContactService health...');
  return RNContactService.checkHealth();
}

/**
 * Check if a contact has changed since last sync
 * @param contact The contact to check
 * @returns Promise resolving to boolean indicating if the contact has changed
 */
export function hasContactChanged(contact: Contact): Promise<boolean> {
  console.log('Checking if contact has changed...');
  return RNContactService.hasContactChanged(contact);
}

/**
 * Get contacts that need to be synced
 * @returns Promise resolving to an array of contacts
 */
export function getContactsForSync(): Promise<Contact[]> {
  console.log('Getting contacts for sync...');
  return RNContactService.getContactsForSync();
}

/**
 * Start a sync operation
 * @param sourceId The source ID for sync
 * @param userId The user ID for sync
 * @returns Promise resolving to the count of synced contacts
 */
export function startSync(
  sourceId: string,
  userId: string
): Promise<{ syncedCount: number }> {
  console.log(`Starting sync with sourceId: ${sourceId}, userId: ${userId}...`);
  return RNContactService.startSync(sourceId, userId);
}

/**
 * Cancel an ongoing sync operation
 * @returns Promise resolving to success status
 */
export function cancelSync(): Promise<boolean> {
  console.log('Canceling sync...');
  return RNContactService.cancelSync();
}

// Export the service object
export const ContactsService = {
  initialize,
  isInitialized,
  currentState,
  reset,
  requestContactsAccess,
  contactsAccessStatus,
  fetchContacts,
  fetchContactsWithFieldType,
  fetchContactsWithBatch,
  fetchContactWithId,
  getContactsCount,
  enableBackgroundSync,
  scheduleBackgroundSyncTask,
  checkHealth,
  hasContactChanged,
  getContactsForSync,
  startSync,
  cancelSync,
};

// For debugging
console.log('RNContactService:', RNContactService);
