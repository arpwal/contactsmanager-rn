// Import all services
import { ContactsAuthorizationService } from './contactsAuthorization';
import { ContactsService } from './contactsService';
import {
  ContactsSearchService,
  SearchFieldType,
} from './contactsSearchService';

// Export the unified API
export const ContactsManager = {
  Authorization: ContactsAuthorizationService,
  Contacts: ContactsService,
  Search: ContactsSearchService,
  SearchFieldType,
};
