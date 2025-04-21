import {
  multiply,
  requestContactsAccess,
  getContacts,
  ContactsAccessStatus,
} from 'contactsmanager-rn';
import type { Contact } from 'contactsmanager-rn';
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
} from 'react-native';
import { useState, useEffect } from 'react';

export default function App() {
  const [result, setResult] = useState<number | undefined>();
  const [contacts, setContacts] = useState<Contact[]>([]);
  const [loading, setLoading] = useState(false);
  const [hasPermission, setHasPermission] = useState(false);
  const [accessStatus, setAccessStatus] = useState<ContactsAccessStatus | null>(
    null
  );

  useEffect(() => {
    multiply(3, 7).then(setResult);
  }, []);

  const handleRequestAccess = async () => {
    try {
      setLoading(true);
      const { granted, status } = await requestContactsAccess();
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
      Alert.alert('Error', 'Failed to request contacts access');
    } finally {
      setLoading(false);
    }
  };

  const fetchContacts = async () => {
    try {
      setLoading(true);
      const contactsList = await getContacts();
      setContacts(contactsList);
    } catch (error) {
      console.error('Error fetching contacts:', error);
      Alert.alert('Error', 'Failed to fetch contacts');
    } finally {
      setLoading(false);
    }
  };

  const renderContact = ({ item }: { item: Contact }) => {
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
              {item.givenName.charAt(0) || item.familyName.charAt(0) || '?'}
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

  return (
    <SafeAreaView style={styles.container}>
      <View style={styles.header}>
        <Text style={styles.headerTitle}>Contacts Manager</Text>
        <Text style={styles.subTitle}>Result from multiply: {result}</Text>
        {accessStatus !== null && (
          <Text style={styles.statusText}>Status: {getStatusText()}</Text>
        )}
      </View>

      {!hasPermission ? (
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
      ) : (
        <>
          {loading ? (
            <View style={styles.loadingContainer}>
              <ActivityIndicator size="large" color="#0066CC" />
              <Text style={styles.loadingText}>Loading contacts...</Text>
            </View>
          ) : contacts.length === 0 ? (
            <View style={styles.emptyContainer}>
              <Text style={styles.emptyText}>No contacts found</Text>
              <TouchableOpacity style={styles.button} onPress={fetchContacts}>
                <Text style={styles.buttonText}>Refresh</Text>
              </TouchableOpacity>
            </View>
          ) : (
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
          )}
        </>
      )}
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
});
