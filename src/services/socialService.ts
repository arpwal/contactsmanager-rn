import { NativeModules } from 'react-native';
import type {
  FollowActionResponse,
  PaginatedFollowList,
  PaginatedMutualFollowers,
  PaginatedEventList,
  SocialEvent,
  EventActionResponse
} from '../types/social';

// Get the native module
const { RNSocialService } = NativeModules;

/**
 * Service for social interaction features
 */
export class SocialService {
  /**
   * Follow a user
   * @param userId The ID of the user to follow
   * @returns Promise with follow action response
   */
  static async followUser(userId: string): Promise<FollowActionResponse> {
    try {
      return await RNSocialService.followUser(userId);
    } catch (error) {
      console.error('Failed to follow user:', error);
      throw error;
    }
  }

  /**
   * Unfollow a user
   * @param userId The ID of the user to unfollow
   * @returns Promise with follow action response
   */
  static async unfollowUser(userId: string): Promise<FollowActionResponse> {
    try {
      return await RNSocialService.unfollowUser(userId);
    } catch (error) {
      console.error('Failed to unfollow user:', error);
      throw error;
    }
  }

  /**
   * Check if current user is following a user
   * @param userId The ID of the user to check
   * @returns Promise with follow status
   */
  static async isFollowingUser(
    userId: string
  ): Promise<{ isFollowing: boolean }> {
    try {
      return await RNSocialService.isFollowingUser(userId);
    } catch (error) {
      console.error('Failed to check follow status:', error);
      throw error;
    }
  }

  /**
   * Get followers for a user
   * @param userId User ID to get followers for (optional, defaults to current user)
   * @param skip Number of items to skip
   * @param limit Maximum number of items to return
   * @returns Promise with paginated follower list
   */
  static async getFollowers(
    userId: string = '',
    skip: number = 0,
    limit: number = 10
  ): Promise<PaginatedFollowList> {
    try {
      return await RNSocialService.getFollowers(userId, skip, limit);
    } catch (error) {
      console.error('Failed to get followers:', error);
      throw error;
    }
  }

  /**
   * Get users that a user is following
   * @param userId User ID to get following for (optional, defaults to current user)
   * @param skip Number of items to skip
   * @param limit Maximum number of items to return
   * @returns Promise with paginated following list
   */
  static async getFollowing(
    userId: string = '',
    skip: number = 0,
    limit: number = 10
  ): Promise<PaginatedFollowList> {
    try {
      return await RNSocialService.getFollowing(userId, skip, limit);
    } catch (error) {
      console.error('Failed to get following:', error);
      throw error;
    }
  }

  /**
   * Get mutual follows (people who follow you and you follow back)
   * @param skip Number of items to skip
   * @param limit Maximum number of items to return
   * @returns Promise with paginated mutual followers
   */
  static async getMutualFollows(
    skip: number = 0,
    limit: number = 10
  ): Promise<PaginatedMutualFollowers> {
    try {
      return await RNSocialService.getMutualFollows(skip, limit);
    } catch (error) {
      console.error('Failed to get mutual follows:', error);
      throw error;
    }
  }

  /**
   * Create a new event
   * @param eventData Event data to create
   * @returns Promise with event action response
   */
  static async createEvent(
    eventData: Partial<SocialEvent>
  ): Promise<EventActionResponse> {
    try {
      return await RNSocialService.createEvent(eventData);
    } catch (error) {
      console.error('Failed to create event:', error);
      throw error;
    }
  }

  /**
   * Get event details
   * @param eventId ID of the event to retrieve
   * @returns Promise with event details
   */
  static async getEvent(eventId: string): Promise<SocialEvent> {
    try {
      return await RNSocialService.getEvent(eventId);
    } catch (error) {
      console.error('Failed to get event:', error);
      throw error;
    }
  }

  /**
   * Update an existing event
   * @param eventId ID of the event to update
   * @param eventData Updated event data
   * @returns Promise with event action response
   */
  static async updateEvent(
    eventId: string,
    eventData: Partial<SocialEvent>
  ): Promise<EventActionResponse> {
    try {
      return await RNSocialService.updateEvent(eventId, eventData);
    } catch (error) {
      console.error('Failed to update event:', error);
      throw error;
    }
  }

  /**
   * Delete an event
   * @param eventId ID of the event to delete
   * @returns Promise with event action response
   */
  static async deleteEvent(eventId: string): Promise<EventActionResponse> {
    try {
      return await RNSocialService.deleteEvent(eventId);
    } catch (error) {
      console.error('Failed to delete event:', error);
      throw error;
    }
  }

  /**
   * Get events created by a specific user
   * @param userId User ID to get events for (optional, defaults to current user)
   * @param skip Number of items to skip
   * @param limit Maximum number of items to return
   * @returns Promise with paginated event list
   */
  static async getUserEvents(
    userId: string = '',
    skip: number = 0,
    limit: number = 10
  ): Promise<PaginatedEventList> {
    try {
      return await RNSocialService.getUserEvents(userId, skip, limit);
    } catch (error) {
      console.error('Failed to get user events:', error);
      throw error;
    }
  }

  /**
   * Get events feed (events from users you follow)
   * @param skip Number of items to skip
   * @param limit Maximum number of items to return
   * @returns Promise with paginated event list
   */
  static async getFeed(
    skip: number = 0,
    limit: number = 10
  ): Promise<PaginatedEventList> {
    try {
      return await RNSocialService.getFeed(skip, limit);
    } catch (error) {
      console.error('Failed to get feed:', error);
      throw error;
    }
  }

  /**
   * Get upcoming events
   * @param skip Number of items to skip
   * @param limit Maximum number of items to return
   * @returns Promise with paginated event list
   */
  static async getUpcomingEvents(
    skip: number = 0,
    limit: number = 10
  ): Promise<PaginatedEventList> {
    try {
      return await RNSocialService.getUpcomingEvents(skip, limit);
    } catch (error) {
      console.error('Failed to get upcoming events:', error);
      throw error;
    }
  }

  /**
   * Get personalized "For You" feed
   * @param skip Number of items to skip
   * @param limit Maximum number of items to return
   * @returns Promise with paginated event list
   */
  static async getForYouFeed(
    skip: number = 0,
    limit: number = 10
  ): Promise<PaginatedEventList> {
    try {
      return await RNSocialService.getForYouFeed(skip, limit);
    } catch (error) {
      console.error('Failed to get for you feed:', error);
      throw error;
    }
  }
}

// Export individual functions for direct use
export const {
  followUser,
  unfollowUser,
  isFollowingUser,
  getFollowers,
  getFollowing,
  getMutualFollows,
  createEvent,
  getEvent,
  updateEvent,
  deleteEvent,
  getUserEvents,
  getFeed,
  getUpcomingEvents,
  getForYouFeed,
} = SocialService;
