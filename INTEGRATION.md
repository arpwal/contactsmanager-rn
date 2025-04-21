# ContactsManager Integration Guide

This guide will help you integrate the ContactsManager module into your React Native app.

## Prerequisites

- React Native project set up
- Xcode 12+ (for iOS)
- CocoaPods installed

## Installation

1. Install the package:

```sh
# Using npm
npm install contactsmanager-rn

# Using yarn
yarn add contactsmanager-rn
```

2. Install CocoaPods dependencies:

```sh
cd ios && pod install && cd ..
```

3. That's it! The module is ready to use.

## Permissions Setup

### iOS

Add the following entries to your `Info.plist` file:

```xml
<key>NSContactsUsageDescription</key>
<string>This app requires contacts access to function properly.</string>
```

### Android (Coming Soon)

Once Android implementation is available, you'll need to add permissions to your `AndroidManifest.xml`.

## Basic Usage

Here's a simple example of how to request access to contacts and fetch them:

```jsx
import React, { useState } from 'react';
import { Button, View, Text, FlatList, StyleSheet } from 'react-native';
import { requestContactsAccess, getContacts } from 'contactsmanager-rn';

export default function ContactsExample() {
  const [contacts, setContacts] = useState([]);
  const [error, setError] = useState(null);

  const loadContacts = async () => {
    try {
      // First, request permission
      const { granted } = await requestContactsAccess();

      if (granted) {
        // If permission granted, load contacts
        const contactsList = await getContacts();
        setContacts(contactsList);
        setError(null);
      } else {
        setError('Contacts permission was denied');
      }
    } catch (err) {
      setError(err.message);
    }
  };

  return (
    <View style={styles.container}>
      <Button title="Load Contacts" onPress={loadContacts} />

      {error && <Text style={styles.error}>{error}</Text>}

      <FlatList
        data={contacts}
        keyExtractor={(item) => item.contactId}
        renderItem={({ item }) => (
          <Text style={styles.contact}>{item.displayName}</Text>
        )}
      />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 20,
  },
  error: {
    color: 'red',
    marginVertical: 10,
  },
  contact: {
    padding: 10,
    borderBottomWidth: 1,
    borderBottomColor: '#eee',
  },
});
```

## Advanced Usage

### Handling Contact Photos

Contact photos are returned as base64-encoded strings in the `thumbnailImageData` property. You can use them directly with the React Native Image component:

```jsx
import { Image } from 'react-native';

// In your render method
{
  contact.thumbnailImageData && (
    <Image
      source={{ uri: `data:image/png;base64,${contact.thumbnailImageData}` }}
      style={{ width: 50, height: 50, borderRadius: 25 }}
    />
  );
}
```

## Troubleshooting

If you encounter any issues with the module, please check the following:

1. Make sure you've run `pod install` after installing the package
2. Check that you've added the required permissions to your `Info.plist`
3. Verify that the framework is properly linked (see README.md for manual linking steps if needed)

If problems persist, please open an issue on GitHub with details about your environment and the error you're encountering.
