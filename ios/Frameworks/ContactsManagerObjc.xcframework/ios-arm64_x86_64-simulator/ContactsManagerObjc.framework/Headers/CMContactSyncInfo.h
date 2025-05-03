//
//  CMContactSyncInfo.h
//  ContactsManagerObjc
//
//  Created for ContactsManager
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Lightweight model for storing contact sync information
 * This is used for the file-based database to avoid storing full contacts
 */
@interface CMContactSyncInfo : NSObject <NSCoding, NSSecureCoding>

// Primary identifier
@property (nonatomic, copy) NSString *contactId;

// Sync metadata
@property (nonatomic, assign) double lastSyncedAt;
@property (nonatomic, copy) NSString *contactHash;
@property (nonatomic, assign) BOOL isDeleted;
@property (nonatomic, assign) BOOL isDirty;

// Display info for UI without loading full contacts
@property (nonatomic, copy) NSString *matchString;
@property (nonatomic, copy) NSString *displayNameForSort;
@property (nonatomic, copy) NSString *primaryInfo;
@property (nonatomic, copy, nullable) NSString *thumbnailUri;

// Added properties for sync functionality
@property (nonatomic, copy) NSString *sourceId;
@property (nonatomic, assign) BOOL syncInProgress;
@property (nonatomic, copy, nullable) NSString *syncError;

/**
 * Initialize with a contact ID
 * @param contactId The unique identifier for the contact
 */
- (instancetype)initWithContactId:(NSString *)contactId;

/**
 * Updates the primary display info from the given contact
 * @param contact The contact to extract display info from
 */
- (void)updateDisplayInfoFromContact:(id)contact;

/**
 * Mark the contact as requiring sync
 */
- (void)markForSync;

/**
 * Update sync info after a successful sync
 * @param timestamp The timestamp of the sync (defaults to current time if nil)
 */
- (void)markSynced:(nullable NSNumber *)timestamp;

/**
 * Record a sync error
 * @param error The error that occurred during sync
 */
- (void)recordSyncError:(NSError *)error;

/**
 * Check if the contact needs to be synced
 * @return YES if the contact needs syncing
 */
- (BOOL)needsSync;

@end

NS_ASSUME_NONNULL_END 
