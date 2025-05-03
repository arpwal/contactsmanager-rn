//
//  CMContactSource.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Enum for source types
 */
typedef NS_ENUM(NSInteger, CMSourceType) {
    CMSourceTypeGoogle,
    CMSourceTypeOutlook,
    CMSourceTypeCSV,
    CMSourceTypeAPI,
    CMSourceTypeDevice,
    CMSourceTypeOther
};

/**
 * Utility functions for source type conversion
 */
@interface CMSourceTypeUtils : NSObject

/**
 * Convert an enum value to its string representation
 */
+ (NSString *)stringFromSourceType:(CMSourceType)sourceType;

/**
 * Convert a string to its corresponding enum value
 */
+ (CMSourceType)sourceTypeFromString:(NSString *)string;

@end

/**
 * Represents a contact source in the system
 */
@interface CMContactSource : NSObject

/**
 * Unique identifier for the source
 */
@property (nonatomic, copy, readonly) NSString *identifier;

/**
 * Source identifier (e.g., "device_UUID") used for server identification
 */
@property (nonatomic, copy) NSString *sourceIdentifier;

/**
 * Source ID (server-side ID)
 */
@property (nonatomic, copy, readonly) NSString *sourceId;

/**
 * Display name for the source
 */
@property (nonatomic, copy) NSString *name;

/**
 * Type of the source (Google, Outlook, etc.)
 */
@property (nonatomic, copy) NSString *sourceType;

/**
 * Organization ID
 */
@property (nonatomic, copy) NSString *organizationId;

/**
 * Canonical Contact ID
 */
@property (nonatomic, copy) NSString *canonicalContactId;

/**
 * Whether the source is active
 */
@property (nonatomic, assign) BOOL isActive;

/**
 * Timestamp of the last sync
 */
@property (nonatomic, assign, nullable) NSNumber *lastSyncAt;

/**
 * Error message from the last sync attempt
 */
@property (nonatomic, copy, nullable) NSString *syncError;

/**
 * Dictionary of credentials (stored as JSON string internally)
 */
@property (nonatomic, strong, nullable) NSDictionary<NSString *, id> *credentials;

/**
 * Dictionary of settings (stored as JSON string internally)
 */
@property (nonatomic, strong, nullable) NSDictionary<NSString *, id> *settings;

/**
 * Dictionary of source metadata (stored as JSON string internally)
 */
@property (nonatomic, strong, nullable) NSDictionary<NSString *, id> *sourceMetadata;

/**
 * Timestamp of creation
 */
@property (nonatomic, assign) NSTimeInterval createdAt;

/**
 * Timestamp of last update
 */
@property (nonatomic, assign) NSTimeInterval updatedAt;

/**
 * Unavailable initializer. Use initWithId:name:sourceType:organizationId:canonicalContactId: instead.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 * Initialize with required fields
 * This is the designated initializer for CMContactSource
 */
- (instancetype)initWithId:(NSString *)identifier
                      name:(NSString *)name
                sourceType:(CMSourceType)sourceType
             organizationId:(NSString *)organizationId
         canonicalContactId:(NSString *)canonicalContactId NS_DESIGNATED_INITIALIZER;

/**
 * Convert to a server-compatible dictionary
 */
- (NSDictionary *)toDictionary;

/**
 * Create a contact source from a dictionary
 */
+ (instancetype)contactSourceFromDictionary:(NSDictionary *)dictionary;

@end

NS_ASSUME_NONNULL_END 