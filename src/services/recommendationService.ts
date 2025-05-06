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
 * Types of contact recommendations
 */
export enum RecommendationType {
  INVITE_RECOMMENDATIONS = 0,
  APP_USERS = 1,
  USERS_YOU_MIGHT_KNOW = 2,
}

/**
 * Service for contact recommendations
 */
export class RecommendationService {
  /**
   * Get contacts you might want to invite to the app
   * @param limit Maximum number of recommendations to return
   * @returns Promise with array of contact recommendations
   */
  static async getInviteRecommendations(
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
   * @param limit Maximum number of recommendations to return
   * @returns Promise with array of contact recommendations
   */
  static async getContactsUsingApp(
    limit: number = 10
  ): Promise<ContactRecommendation[]> {
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
  static async getUsersYouMightKnow(
    limit: number = 10
  ): Promise<CanonicalContact[]> {
    try {
      return await RNRecommendationService.getUsersYouMightKnow(limit);
    } catch (error) {
      console.error('Failed to get users you might know:', error);
      throw error;
    }
  }
}

// Export individual functions for direct use
export const {
  getInviteRecommendations,
  getContactsUsingApp,
  getUsersYouMightKnow,
} = RecommendationService;
