import {
  multiply,
  requestContactsAccess,
  getContacts,
  ContactsAccessStatus,
} from 'contactsmanager-rn';
import type { SimplifiedContact } from 'contactsmanager-rn';
import {
  Text,
  View,
  StyleSheet,
  TouchableOpacity,
  FlatList,
  Image,
  SafeAreaView,
  ActivityIndicator,
  Alert,
  Platform,
  NativeModules,
} from 'react-native';
import { useState, useEffect } from 'react';

export default function App() {
  const [result, setResult] = useState<number | undefined>();
  const [contacts, setContacts] = useState<SimplifiedContact[]>([]);
  const [loading, setLoading] = useState(false);
  const [hasPermission, setHasPermission] = useState(false);
  const [accessStatus, setAccessStatus] = useState<ContactsAccessStatus | null>(
    null
  );
  const [nativeModuleError, setNativeModuleError] = useState<string | null>(
    null
  );

  // Check if the native module is available
  useEffect(() => {
    // Log available native modules for debugging
    console.log('Available NativeModules:', Object.keys(NativeModules));
    console.log('ContactsmanagerRn:', NativeModules.ContactsmanagerRn);

    // Check if the ContactsmanagerRn module is available
    if (!NativeModules.ContactsmanagerRn) {
      setNativeModuleError('Native module ContactsmanagerRn is not available');
      return;
    }

    // Try the multiply function as a basic test
    try {
      multiply(3, 7)
        .then((result) => {
          console.log('Multiply result:', result);
          setResult(result);
        })
        .catch((error) => {
          console.error('Error calling multiply:', error);
          setNativeModuleError(`Error in multiply: ${error.message || error}`);
        });
    } catch (error) {
      console.error('Exception calling multiply:', error);
      setNativeModuleError(
        `Exception: ${error instanceof Error ? error.message : String(error)}`
      );
    }
  }, []);

  const handleRequestAccess = async () => {
    try {
      setLoading(true);
      setNativeModuleError(null);

      console.log('Requesting contacts access...');
      const { granted, status } = await requestContactsAccess();
      console.log('Access result:', { granted, status });

      setHasPermission(granted);
      setAccessStatus(status);

      if (granted) {
        await fetchContacts();
      } else {
        Alert.alert(
          'Permission Denied',
          'Please allow access to contacts in your device settings to use this feature.'
        );
      }
    } catch (error) {
      console.error('Error requesting contacts access:', error);
      setNativeModuleError(
        `Error requesting access: ${error instanceof Error ? error.message : String(error)}`
      );
      Alert.alert('Error', 'Failed to request contacts access');
    } finally {
      setLoading(false);
    }
  };

  const fetchContacts = async () => {
    try {
      setLoading(true);
      setNativeModuleError(null);

      console.log('Fetching contacts...');
      const contactsList = await getContacts();
      console.log(`Retrieved ${contactsList.length} contacts`);

      setContacts(contactsList);
    } catch (error) {
      console.error('Error fetching contacts:', error);
      setNativeModuleError(
        `Error fetching contacts: ${error instanceof Error ? error.message : String(error)}`
      );
      Alert.alert('Error', 'Failed to fetch contacts');
    } finally {
      setLoading(false);
    }
  };

  const renderContact = ({ item }: { item: SimplifiedContact }) => {
    return (
      <View style={styles.contactItem}>
        {item.thumbnailImageData ? (
          <Image
            source={{
              uri: `data:image/jpeg;base64,${item.thumbnailImageData}`,
            }}
            style={styles.contactImage}
          />
        ) : (
          <View style={styles.contactInitials}>
            <Text style={styles.initialsText}>
              {(item.givenName && item.givenName.charAt(0)) ||
                (item.familyName && item.familyName.charAt(0)) ||
                '?'}
            </Text>
          </View>
        )}
        <View style={styles.contactInfo}>
          <Text style={styles.contactName}>
            {item.displayName || 'Unknown'}
          </Text>
          {item.phoneNumbers && item.phoneNumbers.length > 0 && (
            <Text style={styles.contactDetail}>
              {item.phoneNumbers[0]?.number || ''}
            </Text>
          )}
          {item.emailAddresses && item.emailAddresses.length > 0 && (
            <Text style={styles.contactDetail}>
              {item.emailAddresses[0]?.email || ''}
            </Text>
          )}
        </View>
      </View>
    );
  };

  const getStatusText = () => {
    if (accessStatus === null) return '';

    switch (accessStatus) {
      case ContactsAccessStatus.NotDetermined:
        return 'Permission not determined';
      case ContactsAccessStatus.Authorized:
        return 'Full access granted';
      case ContactsAccessStatus.LimitedAuthorized:
        return 'Limited access granted';
      case ContactsAccessStatus.Denied:
        return 'Access denied';
      case ContactsAccessStatus.Restricted:
        return 'Access restricted';
      default:
        return 'Unknown status';
    }
  };

  const renderContent = () => {
    if (nativeModuleError) {
      return (
        <View style={styles.errorContainer}>
          <Text style={styles.errorTitle}>Native Module Error</Text>
          <Text style={styles.errorText}>{nativeModuleError}</Text>
          <Text style={styles.errorNote}>
            This is likely due to framework linking issues. Please check the
            README for setup instructions.
          </Text>
          <View style={styles.errorDebugContainer}>
            <Text style={styles.errorDebugTitle}>Debug Info:</Text>
            <Text style={styles.errorDebugText}>
              Platform: {Platform.OS} {Platform.Version}
            </Text>
            <Text style={styles.errorDebugText}>
              Available Modules: {Object.keys(NativeModules).join(', ')}
            </Text>
          </View>
        </View>
      );
    }

    if (!hasPermission) {
      return (
        <View style={styles.permissionContainer}>
          <Text style={styles.permissionText}>
            This app needs access to your contacts to display them.
          </Text>
          <TouchableOpacity
            style={styles.button}
            onPress={handleRequestAccess}
            disabled={loading}
          >
            <Text style={styles.buttonText}>Request Access</Text>
          </TouchableOpacity>
        </View>
      );
    }

    if (loading) {
      return (
        <View style={styles.loadingContainer}>
          <ActivityIndicator size="large" color="#0066CC" />
          <Text style={styles.loadingText}>Loading contacts...</Text>
        </View>
      );
    }

    if (contacts.length === 0) {
      return (
        <View style={styles.emptyContainer}>
          <Text style={styles.emptyText}>No contacts found</Text>
          <TouchableOpacity style={styles.button} onPress={fetchContacts}>
            <Text style={styles.buttonText}>Refresh</Text>
          </TouchableOpacity>
        </View>
      );
    }

    return (
      <>
        <Text style={styles.contactCount}>
          {contacts.length} contacts found
        </Text>
        <FlatList
          data={contacts}
          renderItem={renderContact}
          keyExtractor={(item) => item.contactId}
          contentContainerStyle={styles.contactsList}
        />
      </>
    );
  };

  return (
    <SafeAreaView style={styles.container}>
      <View style={styles.header}>
        <Text style={styles.headerTitle}>Contacts Manager</Text>
        <Text style={styles.subTitle}>
          Result from multiply: {result ?? 'N/A'}
        </Text>
        {accessStatus !== null && (
          <Text style={styles.statusText}>Status: {getStatusText()}</Text>
        )}
      </View>

      {renderContent()}
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#F5F5F5',
  },
  header: {
    padding: 16,
    backgroundColor: '#fff',
    borderBottomWidth: 1,
    borderBottomColor: '#E0E0E0',
    alignItems: 'center',
  },
  headerTitle: {
    fontSize: 20,
    fontWeight: 'bold',
    color: '#333',
  },
  subTitle: {
    fontSize: 14,
    color: '#666',
    marginTop: 4,
  },
  statusText: {
    fontSize: 12,
    color: '#0066CC',
    marginTop: 4,
  },
  permissionContainer: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    padding: 24,
  },
  permissionText: {
    fontSize: 16,
    textAlign: 'center',
    marginBottom: 20,
    color: '#333',
  },
  button: {
    backgroundColor: '#0066CC',
    paddingVertical: 12,
    paddingHorizontal: 24,
    borderRadius: 8,
    elevation: 2,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.1,
    shadowRadius: 4,
  },
  buttonText: {
    color: '#fff',
    fontSize: 16,
    fontWeight: '600',
  },
  loadingContainer: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  loadingText: {
    marginTop: 12,
    fontSize: 16,
    color: '#666',
  },
  contactsList: {
    padding: 16,
  },
  contactItem: {
    flexDirection: 'row',
    backgroundColor: '#fff',
    padding: 16,
    borderRadius: 12,
    marginBottom: 12,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 1 },
    shadowOpacity: 0.1,
    shadowRadius: 2,
    elevation: 2,
  },
  contactImage: {
    width: 50,
    height: 50,
    borderRadius: 25,
    marginRight: 16,
  },
  contactInitials: {
    width: 50,
    height: 50,
    borderRadius: 25,
    backgroundColor: '#0066CC',
    justifyContent: 'center',
    alignItems: 'center',
    marginRight: 16,
  },
  initialsText: {
    fontSize: 20,
    color: '#fff',
    fontWeight: 'bold',
  },
  contactInfo: {
    flex: 1,
    justifyContent: 'center',
  },
  contactName: {
    fontSize: 16,
    fontWeight: '600',
    marginBottom: 4,
    color: '#333',
  },
  contactDetail: {
    fontSize: 14,
    color: '#666',
    marginBottom: 2,
  },
  emptyContainer: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    padding: 24,
  },
  emptyText: {
    fontSize: 16,
    color: '#666',
    marginBottom: 20,
  },
  contactCount: {
    fontSize: 14,
    color: '#666',
    padding: 16,
    paddingBottom: 0,
  },
  errorContainer: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    padding: 24,
    backgroundColor: '#FFF0F0',
  },
  errorTitle: {
    fontSize: 18,
    fontWeight: 'bold',
    color: '#CC0000',
    marginBottom: 12,
  },
  errorText: {
    fontSize: 16,
    color: '#333',
    textAlign: 'center',
    marginBottom: 12,
  },
  errorNote: {
    fontSize: 14,
    color: '#666',
    textAlign: 'center',
    marginBottom: 24,
    fontStyle: 'italic',
  },
  errorDebugContainer: {
    width: '100%',
    padding: 16,
    backgroundColor: '#F5F5F5',
    borderRadius: 8,
    marginTop: 16,
  },
  errorDebugTitle: {
    fontSize: 14,
    fontWeight: 'bold',
    color: '#333',
    marginBottom: 8,
  },
  errorDebugText: {
    fontSize: 12,
    color: '#666',
    fontFamily: Platform.OS === 'ios' ? 'Menlo' : 'monospace',
  },
});
