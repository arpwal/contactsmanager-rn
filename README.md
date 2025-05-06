# @contactsmanager/rn

Add powerful contact management and social features to your React Native app with minimal code.

## Purpose

I built ContactsManager after my experiences at companies like Facebook, Google, and startups where I witnessed firsthand the challenges of building truly engaging social products. My vision is to give developers the tools to create authentic social experiences while maintaining the highest standards of privacy and security.

With ContactsManager, you can build all the engaging features that platforms like Facebook, Instagram, and LinkedIn offer, but with a crucial difference: user contact data stays on their devices only. This prevents data misuse while enabling viral growth through genuine connections. Build social features into your app with just a few lines of code, all while preserving the privacy of your users and their contacts.

## Status

> **BETA** - The SDK is currently in beta and is being actively updated. If you have any feature requests, please submit them at [contactsmanager.canny.io/feature-requests](https://contactsmanager.canny.io/feature-requests).

## Key Features

| Feature                     | Description                                                                      | Documentation                                                                             |
| --------------------------- | -------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------- |
| [Follow Contacts](#)        | Enable users to follow others and receive their updates                          | [Social Features](https://docs.contactsmanager.io/features/social-features)               |
| [Activity Feeds](#)         | Build chronological feeds of user activities and interactions                    | [Social Features](https://docs.contactsmanager.io/features/social-features)               |
| [Friend Recommendations](#) | Discover users who might be real-world connections without sharing contact lists | [Friend Recommendations](https://docs.contactsmanager.io/features/friend-recommendations) |
| [Contact Search](#)         | Multi-field search across names, phones, emails with fuzzy matching              | [Contacts Search](https://docs.contactsmanager.io/features/contacts-search)               |
| [App User Discovery](#)     | Identify which contacts are already using your application                       | [Friend Recommendations](https://docs.contactsmanager.io/features/friend-recommendations) |
| [Offline Support](#)        | Full functionality even without internet connectivity                            | [Offline Functionality](https://docs.contactsmanager.io/features/offline-functionality)   |
| [Privacy Protection](#)     | Military-grade encryption and local processing of contact data                   | [Privacy By Design](https://docs.contactsmanager.io/features/privacy-by-design)           |

[View all features and documentation →](https://docs.contactsmanager.io/quickstart)

## 1. Installation

```sh
npm install @contactsmanager/rn
# or
yarn add @contactsmanager/rn
```

### Keeping the SDK Up-to-Date

To update to the latest version of the SDK, run:

```sh
yarn upgrade @contactsmanager/rn --latest
# or
npm update @contactsmanager/rn
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
