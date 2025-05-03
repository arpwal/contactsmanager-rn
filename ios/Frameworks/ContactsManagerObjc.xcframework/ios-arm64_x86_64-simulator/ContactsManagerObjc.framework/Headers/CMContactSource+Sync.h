//
//  CMContactSource+Sync.h
//  ContactsManagerObjc
//
//  Created for ContactsManager
//

#import <Foundation/Foundation.h>

// Forward declarations to avoid circular imports
@class CMContactSource;
@class CMContact;

NS_ASSUME_NONNULL_BEGIN

/**
 * Error domain for contact source errors
 */
extern NSString * const CMContactSourceErrorDomain;

/**
 * Error codes for contact source operations
 */
typedef NS_ENUM(NSInteger, CMContactSourceErrorCode) {
    CMContactSourceErrorSaveFailure,
    CMContactSourceErrorRetrievalFailure,
    CMContactSourceErrorSourceNotFound,
    CMContactSourceErrorJSONEncodingFailure,
    CMContactSourceErrorJSONDecodingFailure
};

/**
 * Error domain for sync errors
 */
extern NSString * const CMSyncErrorDomain;

/**
 * Error codes for sync operations
 */
typedef NS_ENUM(NSInteger, CMSyncErrorCode) {
    CMSyncErrorAlreadyRunning,
    CMSyncErrorContextSaveError,
    CMSyncErrorSourceNotRegistered
};

/**
 * Category on CMContactSource for sync functionality
 */
@interface CMContactSource (Sync)

/**
 * Set up sync functionality with a user ID and batch size
 *
 * @param userId The user ID for API requests
 * @param batchSize The batch size for sync operations (default: 20)
 */
- (void)setupSyncWithUserId:(NSString *)userId batchSize:(NSInteger)batchSize;

/**
 * Register background tasks with the system
 */
- (void)registerBackgroundTasks;

/**
 * Set background task registration status externally
 * Used when tasks are registered elsewhere
 *
 * @param registered The registration status
 */
- (void)setBackgroundTaskRegistered:(BOOL)registered;

/**
 * Synchronize contacts with the server using completion handler
 *
 * @param completion Callback with the number of processed contacts or an error
 */
- (void)syncContactsWithCompletion:(void (^)(NSInteger processedCount, NSError * _Nullable error))completion;

/**
 * Schedule a background task to sync contacts
 */
- (void)scheduleBackgroundSync;

/**
 * Cancel an ongoing sync operation
 */
- (void)cancelSync;

@end

NS_ASSUME_NONNULL_END 