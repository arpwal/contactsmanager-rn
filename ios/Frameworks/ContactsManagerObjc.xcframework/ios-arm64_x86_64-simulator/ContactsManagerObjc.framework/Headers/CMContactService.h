//
//  CMContactService.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>
#import <Contacts/Contacts.h>
#import <UIKit/UIKit.h>

@class CMContact;
@class CMUserInfo;
@class CMContactsManagerOptions;
@class CMSocialService;
@class CMRecommendationService;
@class CMContactSearchService;

NS_ASSUME_NONNULL_BEGIN

/**
 * Error codes for ContactsManager service
 */
typedef NS_ENUM(NSInteger, CMContactsServiceErrorCode) {
    CMContactsServiceErrorCodeInvalidAPIKey,
    CMContactsServiceErrorCodeAPIKeyValidationFailed,
    CMContactsServiceErrorCodeNetworkError,
    CMContactsServiceErrorCodeInitializationFailed,
    CMContactsServiceErrorCodeDatabaseError,
    CMContactsServiceErrorCodeNotInitialized,
    CMContactsServiceErrorCodeContactsAccessDenied,
    CMContactsServiceErrorCodeUserNotAuthenticated,
    CMContactsServiceErrorCodeInvalidUserInfo,
    CMContactsServiceErrorCodeCustomError
};

/**
 * Completion block for contact fetching operations
 */
typedef void (^CMContactFetchCompletionBlock)(NSArray<CMContact *> * _Nullable contacts, NSError * _Nullable error);

/**
 * Completion block for single contact fetching
 */
typedef void (^CMContactFetchSingleCompletionBlock)(CMContact * _Nullable contact, NSError * _Nullable error);

/**
 * CMContactService class for managing contacts
 */
@interface CMContactService : NSObject

/**
 * Singleton instance of CMContactService
 */
+ (instancetype)sharedInstance;

/**
 * Initialize the ContactsManager SDK with API key, token, and user information
 * @param apiKey Valid API key for accessing the ContactsManager API
 * @param token Authentication token for the user
 * @param userInfo User information for identification and personalization
 * @param options Additional configuration options
 * @param completion Completion block called with success or error
 */
- (void)initializeWithAPIKey:(NSString *)apiKey 
                       token:(NSString *)token 
                    userInfo:(CMUserInfo *)userInfo
                     options:(nullable CMContactsManagerOptions *)options
                  completion:(void (^)(BOOL success, NSError * _Nullable error))completion;

/**
 * Check if the service is properly initialized
 * @return YES if initialized, NO otherwise
 */
- (BOOL)isInitialized;

/**
 * Get the current initialization state description
 * @return String describing the current state
 */
- (NSString *)currentState;

/**
 * Reset the service to uninitialized state
 * @param completion Completion block called when reset completes
 */
- (void)resetWithCompletion:(void (^)(BOOL success, NSError * _Nullable error))completion;

/**
 * Request access to contacts
 * @param completion Block called when access request completes
 */
- (void)requestContactsAccessWithCompletion:(void (^)(BOOL granted))completion;

/**
 * Get the current contacts access status
 * @return Current ContactsAccessStatus value
 */
- (NSInteger)contactsAccessStatus;

/**
 * Fetch all contacts
 * @param completion Block called when fetch completes with contacts or error
 */
- (void)fetchContactsWithCompletion:(CMContactFetchCompletionBlock)completion;

/**
 * Fetch contacts with a specified field type filter
 * @param fieldType The field type to filter contacts by
 * @param completion Block called when fetch completes with contacts or error
 */
- (void)fetchContactsWithFieldType:(NSInteger)fieldType completion:(CMContactFetchCompletionBlock)completion;

/**
 * Fetch contacts in batches
 * @param batchSize The number of contacts to fetch per batch
 * @param batchIndex The index of the batch to fetch (0-based)
 * @param completion Block called when fetch completes with contacts or error
 */
- (void)fetchContactsWithBatchSize:(NSInteger)batchSize batchIndex:(NSInteger)batchIndex completion:(CMContactFetchCompletionBlock)completion;

/**
 * Fetch a contact by ID
 * @param identifier The identifier of the contact to fetch
 * @param completion Block called when fetch completes with contact or error
 */
- (void)fetchContactWithIdentifier:(NSString *)identifier completion:(CMContactFetchSingleCompletionBlock)completion;

/**
 * Get the total number of contacts
 * @param completion Block called with the count or error
 */
- (void)getContactsCountWithCompletion:(void (^)(NSInteger count, NSError * _Nullable error))completion;

/**
 * Enable background sync functionality
 * Before using this method, you must:
 * 1. Add the "Background Processing" capability to your app
 * 2. Register the background task identifier in your Info.plist
 */
- (void)enableBackgroundSync;

/**
 * Manually schedule a background sync task
 * This should be called when the app is about to enter the background
 */
- (void)scheduleBackgroundSyncTask;

/**
 * Get access to the social service
 * @return Shared instance of the social service or nil if not initialized
 */
- (nullable CMSocialService *)socialService;

/**
 * Get access to the recommendation service
 * @return Shared instance of the recommendation service or nil if not initialized
 */
- (nullable CMRecommendationService *)recommendationService;

/**
 * Get access to the contact search service 
 * @return Shared instance of the search service or nil if not initialized
 */
- (nullable CMContactSearchService *)searchService;

/**
 * Check health of the service
 * @param completion Block called with health status
 */
+ (void)checkHealthWithCompletion:(void (^)(BOOL healthy))completion;

/**
 * Check if a contact has changed since last sync
 * @param contact The contact to check
 * @return YES if the contact has changes that need syncing
 */
- (BOOL)hasContactChanged:(CMContact *)contact;

/**
 * Save sync information for a contact
 * @param contact The contact to save sync info for
 */
- (void)saveSyncInfoForContact:(CMContact *)contact;

/**
 * Get contacts that need to be synced
 * @param completion Block called with an array of contacts needing sync
 */
- (void)getContactsForSyncWithCompletion:(CMContactFetchCompletionBlock)completion;

/**
 * Start a sync operation with the server
 * @param sourceId The source ID to use for sync
 * @param userId The user ID for API requests
 * @param completion Block called when sync completes with count of synced contacts
 */
- (void)startSyncWithSourceId:(NSString *)sourceId 
                       userId:(NSString *)userId
                   completion:(void (^)(NSInteger syncedCount, NSError * _Nullable error))completion;

/**
 * Cancel any ongoing sync operation
 */
- (void)cancelSync;

@end

NS_ASSUME_NONNULL_END 
