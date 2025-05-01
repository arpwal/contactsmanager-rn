//
//  CMContactSyncManager.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>
#import <ContactsManagerObjc/CMContact.h>
#import <ContactsManagerObjc/CMContactSource.h>
#import <ContactsManagerObjc/CMDeviceInfo.h>
#import <ContactsManagerObjc/CMServerModels.h>

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
 * Manages contact synchronization with the server
 */
@interface CMContactSyncManager : NSObject

/**
 * Initialize with user ID, source identifier, and device info
 *
 * @param userId The user ID for API requests
 * @param sourceIdentifier The identifier for this device as a source
 * @param deviceInfo Optional device information
 * @param batchSize The batch size for sync operations (default: 20)
 * @return An initialized contact sync manager
 */
- (instancetype)initWithUserId:(NSString *)userId
               sourceIdentifier:(NSString *)sourceIdentifier
                    deviceInfo:(nullable CMDeviceInfo *)deviceInfo
                     batchSize:(NSInteger)batchSize;

/**
 * Initialize with user ID and source identifier
 *
 * @param userId The user ID for API requests
 * @param sourceIdentifier The identifier for this device as a source
 * @return An initialized contact sync manager
 */
- (instancetype)initWithUserId:(NSString *)userId
               sourceIdentifier:(NSString *)sourceIdentifier;

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
 * Register or get the contact source for this device
 *
 * @param completion Callback with the server contact source or an error
 */
- (void)registerContactSourceWithCompletion:(void (^)(CMServerContactSource * _Nullable source, NSError * _Nullable error))completion;

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