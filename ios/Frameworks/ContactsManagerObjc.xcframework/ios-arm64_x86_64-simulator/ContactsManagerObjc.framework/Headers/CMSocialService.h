//
//  CMSocialService.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>

#if __has_include(<ContactsManagerObjc/CMAPIClient.h>)
#import <ContactsManagerObjc/CMAPIClient.h>
#elif __has_include("CMAPIClient.h")
#import "CMAPIClient.h"
#endif

#if __has_include(<ContactsManagerObjc/CMSocialModels.h>)
#import <ContactsManagerObjc/CMSocialModels.h>
#elif __has_include("CMSocialModels.h")
#import "CMSocialModels.h"
#endif

@class CMContactService;

NS_ASSUME_NONNULL_BEGIN

/**
 * Service that provides methods for interacting with social features
 */
@interface CMSocialService : NSObject

/**
 * Initialize the social service with the shared API client
 * @note This method is for internal use by CMContactService only.
 *       Use [CMContactService socialService] to get an instance.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 * Initialize the social service with a specific API client
 * @param apiClient The API client to use
 * @note This method is for internal use by CMContactService only.
 *       Use [CMContactService socialService] to get an instance.
 */
- (instancetype)initWithAPIClient:(CMAPIClient *)apiClient NS_UNAVAILABLE;

/**
 * Initialize the social service with a contact service
 * @param contactService The contact service instance
 * @note This method is for internal use by CMContactService only.
 *       Use [CMContactService socialService] to get an instance.
 */
- (instancetype)initWithContactService:(CMContactService *)contactService; // Internal method - do not use directly

#pragma mark - Follow Methods

/**
 * Follow another user
 * @param userId The ID of the user to follow
 * @param completion Callback with the follow action response or an error
 */
- (void)followUser:(NSString *)userId
        completion:(void (^)(CMFollowActionResponse * _Nullable response, NSError * _Nullable error))completion;

/**
 * Unfollow a user
 * @param userId The ID of the user to unfollow
 * @param completion Callback with the unfollow action response or an error
 */
- (void)unfollowUser:(NSString *)userId
        completion:(void (^)(CMFollowActionResponse * _Nullable response, NSError * _Nullable error))completion;

/**
 * Check if the current user is following a specified user
 * @param userId The ID of the user to check
 * @param completion Callback with the follow status or an error
 */
- (void)isFollowingUser:(NSString *)userId
            completion:(void (^)(CMFollowStatusResponse * _Nullable response, NSError * _Nullable error))completion;

/**
 * Get followers of a user
 * @param userId The ID of the user to get followers for (optional, uses current user if nil)
 * @param skip Number of records to skip for pagination
 * @param limit Maximum number of records to return
 * @param completion Callback with the paginated follow list or an error
 */
- (void)getFollowersWithUserId:(nullable NSString *)userId
                         skip:(NSInteger)skip
                        limit:(NSInteger)limit
                   completion:(void (^)(CMPaginatedFollowList * _Nullable list, NSError * _Nullable error))completion;

/**
 * Get users that a specified user is following
 * @param userId The ID of the user to get following for (optional, uses current user if nil)
 * @param skip Number of records to skip for pagination
 * @param limit Maximum number of records to return
 * @param completion Callback with the paginated follow list or an error
 */
- (void)getFollowingWithUserId:(nullable NSString *)userId
                         skip:(NSInteger)skip
                        limit:(NSInteger)limit
                   completion:(void (^)(CMPaginatedFollowList * _Nullable list, NSError * _Nullable error))completion;

/**
 * Get users that mutually follow the current user
 * @param skip Number of records to skip for pagination
 * @param limit Maximum number of records to return
 * @param completion Callback with the paginated follow list or an error
 */
- (void)getMutualFollowsWithSkip:(NSInteger)skip
                          limit:(NSInteger)limit
                     completion:(void (^)(CMPaginatedMutualFollowers * _Nullable list, NSError * _Nullable error))completion;

#pragma mark - Event Methods

/**
 * Create a new event
 * @param eventData The data for the event to create
 * @param completion Callback with the event action response or an error
 */
- (void)createEvent:(CMCreateEventRequest *)eventData
        completion:(void (^)(CMEventActionResponse * _Nullable response, NSError * _Nullable error))completion;

/**
 * Get an event by ID
 * @param eventId The ID of the event to retrieve
 * @param completion Callback with the social event or an error
 */
- (void)getEvent:(NSString *)eventId
     completion:(void (^)(CMSocialEvent * _Nullable event, NSError * _Nullable error))completion;

/**
 * Update an existing event
 * @param eventId The ID of the event to update
 * @param eventData The updated event data
 * @param completion Callback with the event action response or an error
 */
- (void)updateEvent:(NSString *)eventId
          eventData:(CMUpdateEventRequest *)eventData
         completion:(void (^)(CMEventActionResponse * _Nullable response, NSError * _Nullable error))completion;

/**
 * Delete an event
 * @param eventId The ID of the event to delete
 * @param completion Callback with the event action response or an error
 */
- (void)deleteEvent:(NSString *)eventId
        completion:(void (^)(CMEventActionResponse * _Nullable response, NSError * _Nullable error))completion;

/**
 * Get events created by a user
 * @param userId The ID of the user to get events for (optional, uses current user if nil)
 * @param skip Number of records to skip for pagination
 * @param limit Maximum number of records to return
 * @param completion Callback with the paginated event list or an error
 */
- (void)getUserEventsWithUserId:(nullable NSString *)userId
                          skip:(NSInteger)skip
                         limit:(NSInteger)limit
                    completion:(void (^)(CMPaginatedEventList * _Nullable list, NSError * _Nullable error))completion;

/**
 * Get a feed of events from users that the current user is following
 * @param skip Number of records to skip for pagination
 * @param limit Maximum number of records to return
 * @param completion Callback with the paginated event list or an error
 */
- (void)getFeedWithSkip:(NSInteger)skip
                 limit:(NSInteger)limit
            completion:(void (^)(CMPaginatedEventList * _Nullable list, NSError * _Nullable error))completion;

/**
 * Get upcoming events
 * @param skip Number of records to skip for pagination
 * @param limit Maximum number of records to return
 * @param completion Callback with the paginated event list or an error
 */
- (void)getUpcomingEventsWithSkip:(NSInteger)skip
                           limit:(NSInteger)limit
                      completion:(void (^)(CMPaginatedEventList * _Nullable list, NSError * _Nullable error))completion;

/**
 * Get "For You" feed of all public events in the organization, not filtered by follow relationships
 * @param skip Number of records to skip for pagination
 * @param limit Maximum number of records to return
 * @param completion Callback with the paginated event list or an error
 */
- (void)getForYouFeedWithSkip:(NSInteger)skip
                        limit:(NSInteger)limit
                   completion:(void (^)(CMPaginatedEventList * _Nullable list, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END 
