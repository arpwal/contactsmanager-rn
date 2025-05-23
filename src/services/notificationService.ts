import { NativeModules } from 'react-native';

// Get the native module
const { RNNotificationService } = NativeModules;

/**
 * Event types that can be observed in the notification system
 */
export enum NotificationEventType {
  APP_DID_BECOME_ACTIVE = 'appDidBecomeActive',
  APP_DID_ENTER_BACKGROUND = 'appDidEnterBackground',
  CONTACT_STORE_DID_CHANGE = 'contactStoreDidChange',
  APP_WAS_TERMINATED = 'appWasTerminated',
  CONTACTS_ACCESS_CHANGED = 'contactsAccessChanged',
}

/**
 * Start observing system events and notifications
 * @returns Promise that resolves when observation has started
 */
export async function startObserving(): Promise<boolean> {
  try {
    return await RNNotificationService.startObserving();
  } catch (error) {
    console.error('Failed to start notification observer:', error);
    throw error;
  }
}

/**
 * Stop observing system events and notifications
 * @returns Promise that resolves when observation has stopped
 */
export async function stopObserving(): Promise<boolean> {
  try {
    return await RNNotificationService.stopObserving();
  } catch (error) {
    console.error('Failed to stop notification observer:', error);
    throw error;
  }
}

/**
 * Subscribe to a specific event type
 * @param eventType The type of event to subscribe to
 * @param identifier Unique identifier for this subscription
 * @returns Promise that resolves when subscription is successful
 */
export async function subscribeToEvent(
  eventType: NotificationEventType,
  identifier: string
): Promise<boolean> {
  try {
    return await RNNotificationService.subscribeToEvent(eventType, identifier);
  } catch (error) {
    console.error(`Failed to subscribe to ${eventType} event:`, error);
    throw error;
  }
}

/**
 * Unsubscribe from a specific event type
 * @param eventType The type of event to unsubscribe from
 * @param identifier The unique identifier used during subscription
 * @returns Promise that resolves when unsubscription is successful
 */
export async function unsubscribeFromEvent(
  eventType: NotificationEventType,
  identifier: string
): Promise<boolean> {
  try {
    return await RNNotificationService.unsubscribeFromEvent(
      eventType,
      identifier
    );
  } catch (error) {
    console.error(`Failed to unsubscribe from ${eventType} event:`, error);
    throw error;
  }
}

// Export the service object
export const NotificationService = {
  startObserving,
  stopObserving,
  subscribeToEvent,
  unsubscribeFromEvent,
  NotificationEventType,
};

// For debugging
console.log('RNNotificationService:', RNNotificationService);
