import type {
  Contact,
  ContactPhoneNumber,
  ContactEmailAddress,
  SimplifiedContact,
} from '../types';

/**
 * Converts a native Contact to a simplified Contact model
 * Used for backward compatibility with existing code
 */
export function nativeToSimplifiedContact(contact: Contact): SimplifiedContact {
  return {
    contactId: contact.identifier,
    displayName: contact.displayName || '',
    givenName: contact.givenName || '',
    familyName: contact.familyName || '',
    phoneNumbers: contact.phoneNumbers.map((phone) => ({
      label: phone.type || '',
      number: phone.value,
    })),
    emailAddresses: contact.emailAddresses.map((email) => ({
      label: email.type || '',
      email: email.value,
    })),
    thumbnailImageData: contact.avatars[0]?.data,
  };
}

/**
 * Converts a simplified Contact to a native Contact model
 * Used for backward compatibility with existing code
 */
export function simplifiedToNativeContact(
  contact: SimplifiedContact
): Partial<Contact> {
  const phoneNumbers: ContactPhoneNumber[] = contact.phoneNumbers.map(
    (phone) => ({
      contactId: contact.contactId,
      value: phone.number,
      type: phone.label,
    })
  );

  const emailAddresses: ContactEmailAddress[] = contact.emailAddresses.map(
    (email) => ({
      contactId: contact.contactId,
      value: email.email,
      type: email.label,
    })
  );

  const avatars = contact.thumbnailImageData
    ? [{ contactId: contact.contactId, data: contact.thumbnailImageData }]
    : [];

  return {
    identifier: contact.contactId,
    displayName: contact.displayName,
    givenName: contact.givenName,
    familyName: contact.familyName,
    phoneNumbers,
    emailAddresses,
    avatars,
    addresses: [],
    dates: [],
    urlAddresses: [],
    socialProfiles: [],
    relations: [],
    instantMessageAddresses: [],
    interests: [],
    isDeleted: false,
    createdAt: Date.now(),
    contactSection: getContactSection(contact),
    matchString: generateMatchString(contact),
  };
}

/**
 * Determines the section letter for a contact
 */
function getContactSection(contact: SimplifiedContact): string {
  if (contact.familyName && contact.familyName.length > 0) {
    return contact.familyName.charAt(0).toUpperCase();
  } else if (contact.givenName && contact.givenName.length > 0) {
    return contact.givenName.charAt(0).toUpperCase();
  } else {
    return '#';
  }
}

/**
 * Generates a match string for search optimization
 */
function generateMatchString(contact: SimplifiedContact): string {
  const parts: string[] = [];

  if (contact.givenName) parts.push(contact.givenName);
  if (contact.familyName) parts.push(contact.familyName);

  // Add phone numbers
  contact.phoneNumbers.forEach((phone) => {
    parts.push(normalizePhoneNumber(phone.number));
  });

  // Add email addresses
  contact.emailAddresses.forEach((email) => {
    parts.push(normalizeEmail(email.email));
  });

  return parts.join(' ');
}

/**
 * Normalizes a phone number for matching
 */
function normalizePhoneNumber(phoneNumber: string): string {
  // Remove non-digits
  return phoneNumber.replace(/\D/g, '');
}

/**
 * Normalizes an email for matching
 */
function normalizeEmail(email: string): string {
  // Convert to lowercase
  return email.toLowerCase();
}

export const ContactsMapper = {
  nativeToSimplifiedContact,
  simplifiedToNativeContact,
};
