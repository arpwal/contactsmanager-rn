# ContactsManager React Native SDK

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/platform-iOS%20%7C%20Android-lightgrey)](https://github.com/arpwal/contactsmanager-rn)
[![npm version](https://img.shields.io/npm/v/@contactsmanager/rn.svg)](https://www.npmjs.com/package/@contactsmanager/rn)
[![Documentation](https://img.shields.io/badge/docs-contactsmanager.io-blue)](https://docs.contactsmanager.io)
[![Slack](https://img.shields.io/badge/slack-join_chat-brightgreen)](https://join.slack.com/t/contactsmanagersdk/shared_invite/zt-34as6nm2u-N7oMFvcQFoXwQvIo~ePJ1g)

ContactsManager.io is a powerful contact management solution designed specifically for consumer app builders. It provides a seamless, secure, and efficient way to manage user contacts across platforms while maintaining the highest standards of privacy and security.

Add powerful contact management and social features to your React Native app with minimal code.

📚 [Full Documentation](https://docs.contactsmanager.io)

🚀 [Quick Start Guide](https://docs.contactsmanager.io/quickstart)

💬 [Join our Slack Community](https://join.slack.com/t/contactsmanagersdk/shared_invite/zt-34as6nm2u-N7oMFvcQFoXwQvIo~ePJ1g)

## Purpose

I built ContactsManager after my experiences at companies like Facebook, Google, and startups where I witnessed firsthand the challenges of building truly engaging social products. My vision is to give developers the tools to create authentic social experiences while maintaining the highest standards of privacy and security.

With ContactsManager, you can build all the engaging features that platforms like Facebook, Instagram, and LinkedIn offer, but with a crucial difference: user contact data stays on their devices only. This prevents data misuse while enabling viral growth through genuine connections. Build social features into your app with just a few lines of code, all while preserving the privacy of your users and their contacts.

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
import { initialize, isInitialized } from '@contactsmanager/rn';

// Check if already initialized
const alreadyInitialized = await isInitialized();

// Recommendation: Get token from your own server in production
const TOKEN = null;

// Initialize with your API key and token from server
const result = await initialize(API_KEY, userInfo, TOKEN, {});
```

> Note: [Server Side Token Generation](https://docs.contactsmanager.io/services/token-generation#implementation-examples)

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
