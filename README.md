# contactsmanager-rn

A React Native module for accessing and managing contacts with built-in privacy features.

## Installation

```sh
npm install contactsmanager-rn
# or
yarn add contactsmanager-rn
```

## iOS Setup

This module includes the `ContactsManagerObjc.xcframework` which is automatically integrated into your project when you install it.

### 1. Install CocoaPods dependencies

```sh
cd ios && pod install && cd ..
```

That's it! The XCFramework should be automatically linked and ready to use.

### Troubleshooting

If you encounter any issues with the framework installation:

#### Option 1: Verify framework location

The framework should be automatically installed in:

- `node_modules/contactsmanager-rn/ios/Frameworks/ContactsManagerObjc.xcframework`

#### Option 2: Manual framework fix

If you're experiencing issues with the framework, you can run our fix script:

```sh
cd ios
chmod +x ../node_modules/contactsmanager-rn/fix_xcframework.sh
../node_modules/contactsmanager-rn/fix_xcframework.sh
pod install
```

#### Option 3: Manual Xcode linking

As a last resort, you can manually add the framework in Xcode:

1. Open your project in Xcode
2. Select your target's "General" settings tab
3. Scroll to "Frameworks, Libraries, and Embedded Content"
4. Click the "+" button
5. Select "Add Other..." and choose "Add Files..."
6. Navigate to `node_modules/contactsmanager-rn/ios/Frameworks/ContactsManagerObjc.xcframework`
7. Make sure to select "Embed & Sign"

## Android Setup

Android implementation is currently in progress.

## Usage

```js
import {
  requestContactsAccess,
  getContacts,
  ContactsAccessStatus,
} from 'contactsmanager-rn';

// Request access to contacts
const requestAccess = async () => {
  try {
    const { granted, status } = await requestContactsAccess();

    if (granted) {
      console.log('Access granted with status:', status);
      // Fetch contacts
      const contacts = await getContacts();
      console.log(`Retrieved ${contacts.length} contacts`);
    } else {
      console.log('Access denied with status:', status);
    }
  } catch (error) {
    console.error('Error accessing contacts:', error);
  }
};
```

## API Reference

### `requestContactsAccess()`

Requests access to the user's contacts. Returns a Promise that resolves to an object with:

- `granted`: boolean - Whether access was granted
- `status`: ContactsAccessStatus - The current access status

### `getContacts()`

Fetches the user's contacts. Returns a Promise that resolves to an array of Contact objects.

### Types

```typescript
enum ContactsAccessStatus {
  NotDetermined = 0,
  Authorized = 1,
  LimitedAuthorized = 2,
  Denied = 3,
  Restricted = 4,
}

type PhoneNumber = {
  label: string;
  number: string;
};

type EmailAddress = {
  label: string;
  email: string;
};

type Contact = {
  contactId: string;
  displayName: string;
  givenName: string;
  familyName: string;
  phoneNumbers: PhoneNumber[];
  emailAddresses: EmailAddress[];
  thumbnailImageData?: string;
};
```

## Troubleshooting

### Module is undefined in React Native

If you're getting errors about the native module being undefined:

1. Make sure you've run `pod install` in the ios directory
2. Check that the framework is in the correct location
3. Try the fix script mentioned in the iOS Setup section
4. If all else fails, manually add the framework in Xcode

### PhaseScriptExecution failed with a nonzero exit code

This usually means the framework can't be found during the build process. Check:

1. The path to the framework in the script phase
2. Make sure both simulator and device slices are available in the xcframework
3. Try the fix script mentioned above

## License

MIT

---

Made with [create-react-native-library](https://github.com/callstack/react-native-builder-bob)
