import { NativeModules, Platform } from 'react-native';

// Re-export all types
export * from './types';

// Re-export all services directly
export {
  ContactsAuthorizationService,
  requestContactsAccess,
  checkAccessStatus,
  shouldShowSettingsAlert,
} from './services/contactsAuthorization';

export {
  ContactsManager,
  getContacts,
  getDetailedContacts,
  multiply,
} from './services/contactsManager';

export {
  ContactsMapper,
  nativeToSimplifiedContact,
  simplifiedToNativeContact,
} from './services/contactsMapper';

// Also re-export from the services index for backward compatibility
export * from './services';

const LINKING_ERROR =
  `The package 'contactsmanager-rn' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo Go\n';

// Log available modules for debugging
console.log('Available NativeModules:', Object.keys(NativeModules));
console.log('ContactsmanagerRn modules:', {
  RNContactsAuthorizationService: NativeModules.RNContactsAuthorizationService,
  RNContactsManager: NativeModules.RNContactsManager,
});

// Create proxies for native modules to handle errors gracefully
export const RNContactsAuthorizationService =
  NativeModules.RNContactsAuthorizationService
    ? NativeModules.RNContactsAuthorizationService
    : new Proxy(
        {},
        {
          get() {
            throw new Error(LINKING_ERROR);
          },
        }
      );

export const RNContactsManager = NativeModules.RNContactsManager
  ? NativeModules.RNContactsManager
  : new Proxy(
      {},
      {
        get() {
          throw new Error(LINKING_ERROR);
        },
      }
    );
