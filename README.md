# @contactsmanager/rn

Add powerful contact management and social features to your React Native app with minimal code.

## 1. Installation

```sh
npm install @contactsmanager/rn
# or
yarn add @contactsmanager/rn
```

## 2. SDK Setup

1. Create a free API key from [contactsmanager.io](https://www.contactsmanager.io)
2. Generate an authentication token from your backend server (see [documentation](https://docs.contactsmanager.io/quickstart) for details)
3. Initialize the SDK in your app with the token

```js
import { ContactsManager } from '@contactsmanager/rn';

// Initialize with your API key and token from server
await ContactsManager.initialize({
  apiKey: 'your-api-key',
  token: 'user-auth-token',
  userInfo: {
    userId: 'unique-user-id',
    email: 'user@example.com', // optional
    phone: '+15551234567', // optional
    fullName: 'User Name', // optional
  },
});
```

## 3. Platform Setup

### iOS Setup

The package includes the `ContactsManagerObjc.xcframework` that is automatically integrated into your project.

1. Install CocoaPods dependencies:

```sh
cd ios && pod install && cd ..
```

2. Add the necessary permissions to your `Info.plist`:

```xml
<key>NSContactsUsageDescription</key>
<string>We need access to your contacts to enable social features</string>
```

### Android Setup

Android support is coming soon! Check our [documentation](https://docs.contactsmanager.io/quickstart) for updates.

## 4. Basic Usage

```js
import {
  requestContactsAccess,
  hasContactsReadAccess,
  getContacts,
} from '@contactsmanager/rn';

// Request access to contacts
const requestAccess = async () => {
  try {
    // Request access - handles both full and limited access cases
    const { granted } = await requestContactsAccess();

    if (granted) {
      // Check if we have read access (either full or limited authorization)
      const hasReadAccess = await hasContactsReadAccess();

      if (hasReadAccess) {
        // Fetch contacts
        const contacts = await getContacts();
        console.log(`Retrieved ${contacts.length} contacts`);
      }
    }
  } catch (error) {
    console.error('Error accessing contacts:', error);
  }
};
```

## API Reference

For complete API documentation, please visit:
[https://docs.contactsmanager.io/quickstart](https://docs.contactsmanager.io/quickstart)

## Get a Free Demo

Interested in learning more? Get a free demo setup via:
[https://www.contactsmanager.io/demo](https://www.contactsmanager.io/demo)

## License

MIT

---

Made with [create-react-native-library](https://github.com/callstack/react-native-builder-bob)
