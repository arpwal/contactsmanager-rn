// Import all services
import { ContactsAuthorizationService } from './contactsAuthorization';
import { ContactsService } from './contactsService';
import {
  ContactsSearchService,
  SearchFieldType,
} from './contactsSearchService';
import {
  NotificationService,
  NotificationEventType,
} from './notificationService';
import { SocialService } from './socialService';
import {
  RecommendationService,
  RecommendationType,
} from './recommendationService';

// Export the unified API
export const ContactsManager = {
  Authorization: ContactsAuthorizationService,
  Contacts: ContactsService,
  Search: ContactsSearchService,
  Notification: NotificationService,
  Social: SocialService,
  Recommendation: RecommendationService,
  SearchFieldType,
  NotificationEventType,
  RecommendationType,
};
