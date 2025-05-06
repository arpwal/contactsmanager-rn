import { NativeModules } from 'react-native';
import type { Contact } from '../types/contacts';
import type { CanonicalContact } from '../types/social';

// Get the native module
const { RNRecommendationService } = NativeModules;

/**
 * Represents a contact recommendation with scoring and metadata
 */
export interface ContactRecommendation {
  contact: Contact;
  score: number;
  reason: string;
  type: RecommendationType;
  organizationUserId?: string;
}

/**
 * Represents a contact that exists both locally on device and in the canonical contacts system
 */
export interface LocalCanonicalContact {
  contact: Contact | null;
  contactId: string;
  sourceContactId: string;
  canonicalContact: CanonicalContact;
}

/**
 * Types of contact recommendations
 */
export enum RecommendationType {
  INVITE_RECOMMENDATIONS = 0,
  APP_USERS = 1,
  USERS_YOU_MIGHT_KNOW = 2,
}

/**
 * Get contacts you might want to invite to the app
 * @param limit Maximum number of recommendations to return
 * @returns Promise with array of contact recommendations
 */
export async function getInviteRecommendations(
  limit: number = 10
): Promise<ContactRecommendation[]> {
  try {
    return await RNRecommendationService.getInviteRecommendations(limit);
  } catch (error) {
    console.error('Failed to get invite recommendations:', error);
    throw error;
  }
}

/**
 * Get contacts who are already using the app
 * @param limit Maximum number of contacts to return
 * @returns Promise with array of local canonical contacts
 */
export async function getContactsUsingApp(
  limit: number = 10
): Promise<LocalCanonicalContact[]> {
  try {
    return await RNRecommendationService.getContactsUsingApp(limit);
  } catch (error) {
    console.error('Failed to get contacts using app:', error);
    throw error;
  }
}

/**
 * Get users you might know based on your network
 * @param limit Maximum number of users to return
 * @returns Promise with array of canonical contacts
 */
export async function getUsersYouMightKnow(
  limit: number = 10
): Promise<CanonicalContact[]> {
  try {
    return await RNRecommendationService.getUsersYouMightKnow(limit);
  } catch (error) {
    console.error('Failed to get users you might know:', error);
    throw error;
  }
}

// Export the service object
export const RecommendationService = {
  getInviteRecommendations,
  getContactsUsingApp,
  getUsersYouMightKnow,
  RecommendationType,
};

// For debugging
console.log('RNRecommendationService:', RNRecommendationService);
