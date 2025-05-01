//
//  CMContactsManagerOptions.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>
#import <ContactsManagerObjc/CMContact.h> // Import CMContact.h for CMContactFieldType enum

NS_ASSUME_NONNULL_BEGIN

/**
 * Represents different types of contact data that can be restricted from fetching
 */
typedef NS_ENUM(NSInteger, CMContactDataRestriction) {
    /**
     * Restricts fetching of contact notes
     */
    CMContactDataRestrictionNotes
};

/**
 * Utility functions for data restriction conversion
 */
@interface CMContactDataRestrictionUtils : NSObject

/**
 * Convert a data restriction enum to its corresponding contact key
 */
+ (NSString *)contactKeyFromRestriction:(CMContactDataRestriction)restriction;

@end

/**
 * Configuration options for the ContactsManager
 */
@interface CMContactsManagerOptions : NSObject

/**
 * Keys that should not be fetched when retrieving contacts
 */
@property (nonatomic, copy, readonly) NSSet<NSNumber *> *restrictedKeysToFetch;

/**
 * Create a new options object with specified restricted keys
 *
 * @param restrictedKeysToFetch Set of contact field types that should not be fetched
 * @return A configured CMContactsManagerOptions instance
 */
- (instancetype)initWithRestrictedKeysToFetch:(NSSet<NSNumber *> *)restrictedKeysToFetch;

/**
 * Default options with no restrictions
 */
+ (instancetype)defaultOptions;

@end

NS_ASSUME_NONNULL_END 
