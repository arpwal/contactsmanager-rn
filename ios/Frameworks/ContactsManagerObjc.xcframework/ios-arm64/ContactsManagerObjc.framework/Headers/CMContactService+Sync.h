//
//  CMContactService+Sync.h
//  ContactsManagerObjc
//
//  Created for ContactsManager
//

#import <Foundation/Foundation.h>

#if __has_include(<ContactsManagerObjc/CMContactService.h>)
#import <ContactsManagerObjc/CMContactService.h>
#elif __has_include("CMContactService.h")
#import "CMContactService.h"
#endif

// Forward declaration for CMContactSyncInfo
@class CMContact;
@class CMContactSyncInfo;

NS_ASSUME_NONNULL_BEGIN

/**
 * Category on CMContactService to provide sync functionality
 */
@interface CMContactService (Sync)

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
 * Get sync information for a contact
 * @param contact The contact to get sync info for
 * @return The sync info object or nil if none exists
 */
- (nullable CMContactSyncInfo *)syncInfoForContact:(CMContact *)contact;

/**
 * Get contacts that need to be synced
 * @param completion Block called with an array of contacts needing sync
 */
- (void)getContactsForSyncWithCompletion:(CMContactFetchCompletionBlock)completion;

/**
 * Start a sync operation
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
