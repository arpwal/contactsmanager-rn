import { NativeModules, Platform } from 'react-native';

const LINKING_ERROR =
  `The package 'contactsmanager-rn' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo Go\n';

// Add debug logging
console.log('Available NativeModules:', Object.keys(NativeModules));
console.log('ContactsmanagerRn module:', NativeModules.ContactsmanagerRn);

const ContactsmanagerRn = NativeModules.ContactsmanagerRn
  ? NativeModules.ContactsmanagerRn
  : new Proxy(
      {},
      {
        get() {
          throw new Error(LINKING_ERROR);
        },
      }
    );

export function multiply(a: number, b: number): Promise<number> {
  return ContactsmanagerRn.multiply(a, b);
}

export enum ContactsAccessStatus {
  NotDetermined = 0,
  Authorized = 1,
  LimitedAuthorized = 2,
  Denied = 3,
  Restricted = 4,
}

export type PhoneNumber = {
  label: string;
  number: string;
};

export type EmailAddress = {
  label: string;
  email: string;
};

export type Contact = {
  contactId: string;
  displayName: string;
  givenName: string;
  familyName: string;
  phoneNumbers: PhoneNumber[];
  emailAddresses: EmailAddress[];
  thumbnailImageData?: string;
};

export type ContactsAccessResult = {
  granted: boolean;
  status: ContactsAccessStatus;
};

export function requestContactsAccess(): Promise<ContactsAccessResult> {
  return ContactsmanagerRn.requestContactsAccess();
}

export function getContacts(): Promise<Contact[]> {
  return ContactsmanagerRn.getContacts();
}
