import { NativeModules } from 'react-native';
import type { Contact, SimplifiedContact } from '../types';
import { ContactsMapper } from './contactsMapper';

// Direct access to the native module
const { RNContactsManager } = NativeModules;

/**
 * Test multiplication function (for testing native module connection)
 */
export function multiply(a: number, b: number): Promise<number> {
  return RNContactsManager.multiply(a, b);
}

/**
 * Retrieve all contacts from the device
 * Simplified contacts for basic usage in UI
 */
export async function getContacts(): Promise<SimplifiedContact[]> {
  console.log('Fetching contacts...');
  try {
    const nativeContacts = await RNContactsManager.getContacts();
    return nativeContacts.map(ContactsMapper.nativeToSimplifiedContact);
  } catch (error) {
    console.error('Failed to fetch contacts:', error);
    throw error;
  }
}

/**
 * Retrieve all contacts with detailed information
 */
export async function getDetailedContacts(): Promise<Contact[]> {
  console.log('Fetching detailed contacts...');
  return RNContactsManager.getContacts();
}

// Export the service object
export const ContactsManager = {
  multiply,
  getContacts,
  getDetailedContacts,
};

// For debugging
console.log('RNContactsManager:', RNContactsManager);
