import { NativeModules } from 'react-native';
import type { ContactsAccessResult } from '../types';

// Direct access to the native module
const { RNContactsAuthorizationService } = NativeModules;

/**
 * Request access to the device's contacts
 * @returns Promise resolving to an object with granted status and access status code
 */
export function requestContactsAccess(): Promise<ContactsAccessResult> {
  console.log('Requesting contacts access...');
  return RNContactsAuthorizationService.requestContactsAccess();
}

/**
 * Check the current status of contacts access permissions
 * @returns Promise resolving to a numeric status code
 */
export function checkAccessStatus(): Promise<number> {
  console.log('Checking access status...');
  return RNContactsAuthorizationService.checkAccessStatus();
}

/**
 * Check if the app has read access to contacts (either authorized or limited)
 * @returns Promise resolving to a boolean indicating if read access is available
 */
export function hasContactsReadAccess(): Promise<boolean> {
  console.log('Checking if app has contacts read access...');
  return RNContactsAuthorizationService.hasContactsReadAccess();
}

/**
 * Check if the settings alert should be shown to the user
 * @returns Promise resolving to a boolean
 */
export function shouldShowSettingsAlert(): Promise<boolean> {
  return RNContactsAuthorizationService.shouldShowSettingsAlert();
}

/**
 * Show the settings alert to guide user to app settings
 * @returns Promise resolving when the alert is shown
 */
export function showSettingsAlert(): Promise<void> {
  return RNContactsAuthorizationService.showSettingsAlert();
}

// Export the service object
export const ContactsAuthorizationService = {
  requestContactsAccess,
  checkAccessStatus,
  hasContactsReadAccess,
  shouldShowSettingsAlert,
  showSettingsAlert,
};

// For debugging
console.log('RNContactsAuthorizationService:', RNContactsAuthorizationService);
