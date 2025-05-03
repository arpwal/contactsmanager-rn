//
//  CMContactStorageManager.h
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

#if __has_include(<ContactsManagerObjc/CMContactSyncInfo.h>)
#import <ContactsManagerObjc/CMContactSyncInfo.h>
#elif __has_include("CMContactSyncInfo.h")
#import "CMContactSyncInfo.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 * Extension of CMContactService for managing contact storage
 * This keeps the file-based persistence logic separate from the main service
 */
@interface CMContactService (Storage)

/**
 * Get sync info for a specific contact
 * @param contactId The contact identifier
 * @return The sync info object or nil if not found
 */
- (nullable CMContactSyncInfo *)syncInfoForContactId:(NSString *)contactId;

/**
 * Save sync info for a contact
 * @param contact The contact to save sync info for
 * @return The updated sync info object
 */
- (CMContactSyncInfo *)saveSyncInfoForContact:(id)contact;

/**
 * Mark a contact as deleted in the sync info
 * @param contactId The contact identifier to mark as deleted
 */
- (void)markContactAsDeleted:(NSString *)contactId;

/**
 * Get all sync info objects
 * @return Array of all sync info objects
 */
- (NSArray<CMContactSyncInfo *> *)allSyncInfo;

/**
 * Get all active (non-deleted) sync info objects
 * @return Array of active sync info objects
 */
- (NSArray<CMContactSyncInfo *> *)activeSyncInfo;

/**
 * Save the sync info cache to disk
 */
- (void)saveSyncInfoCache;

/**
 * Load the sync info cache from disk
 */
- (void)loadSyncInfoCache;

/**
 * Clear the sync info cache
 */
- (void)clearSyncInfoCache;

/**
 * Check if a contact has changed by comparing hashes
 * @param contact The contact to check
 * @return YES if the contact has changed, NO otherwise
 */
- (BOOL)hasContactChanged:(id)contact;

@end

NS_ASSUME_NONNULL_END 