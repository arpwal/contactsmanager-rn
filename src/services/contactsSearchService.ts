import { NativeModules } from 'react-native';
import type { Contact } from '../types';

// Direct access to the native module
const { RNContactSearchService } = NativeModules;

// Search Field Type enum
export enum SearchFieldType {
  Name = 1, // 1 << 0
  Email = 2, // 1 << 1
  Phone = 4, // 1 << 2
  Address = 8, // 1 << 3
  Organization = 16, // 1 << 4
  Notes = 32, // 1 << 5
  All = 4294967295, // 0xFFFFFFFF
}

/**
 * Search contacts with a query string and field type filter
 * @param query The search query
 * @param fieldType Bitmask of fields to search (default: all fields)
 * @param offset Starting index for pagination
 * @param limit Maximum number of results to return
 * @returns Promise resolving to contacts and total count
 */
export function searchContacts(
  query: string,
  fieldType: SearchFieldType = SearchFieldType.All,
  offset: number = 0,
  limit: number = 20
): Promise<{ contacts: Contact[]; totalCount: number }> {
  console.log(
    `Searching contacts with query: "${query}", fieldType: ${fieldType}, offset: ${offset}, limit: ${limit}...`
  );
  return RNContactSearchService.searchContacts(query, fieldType, offset, limit);
}

/**
 * Perform a quick search for real-time filtering
 * @param query The search query
 * @returns Promise resolving to an array of contacts
 */
export function quickSearch(query: string): Promise<Contact[]> {
  console.log(`Quick searching contacts with query: "${query}"...`);
  return RNContactSearchService.quickSearch(query);
}

/**
 * Get the total count of contacts
 * @returns Promise resolving to the count
 */
export function getContactsCount(): Promise<number> {
  console.log('Getting contacts count via SearchService...');
  return RNContactSearchService.getContactsCount();
}

// Export the service object
export const ContactsSearchService = {
  searchContacts,
  quickSearch,
  getContactsCount,
  SearchFieldType,
};

// For debugging
console.log('RNContactSearchService:', RNContactSearchService);
