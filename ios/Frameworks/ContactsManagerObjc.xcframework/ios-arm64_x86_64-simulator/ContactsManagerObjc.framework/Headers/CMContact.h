//
//  CMContact.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * ContactFieldType enum representing the types of fields to fetch
 */
typedef NS_ENUM(NSInteger, CMContactFieldType) {
    CMContactFieldTypeAny,    // All available fields
    CMContactFieldTypePhone,  // Only phone numbers
    CMContactFieldTypeEmail,  // Only email addresses
    CMContactFieldTypeNotes   // Only notes
};

@class CMContactPhoneNumber;
@class CMContactEmailAddress;
@class CMContactAddress;
@class CMContactDate;
@class CMContactURL;
@class CMContactSocialProfile;
@class CMContactRelation;
@class CMContactInstantMessage;

/**
 * CMContact class representing a contact in the device's address book
 */
@interface CMContact : NSObject <NSCopying>

// Primary identifiers
@property (nonatomic, copy, readonly) NSString *identifier;
@property (nonatomic, copy, nullable) NSString *displayName;

/**
 * Returns the most relevant contact information following a priority order
 */
- (NSString *)displayInfo;

// Basic information
@property (nonatomic, assign) NSInteger contactType;
@property (nonatomic, copy, nullable) NSString *namePrefix;
@property (nonatomic, copy, nullable) NSString *givenName;
@property (nonatomic, copy, nullable) NSString *middleName;
@property (nonatomic, copy, nullable) NSString *familyName;
@property (nonatomic, copy, nullable) NSString *previousFamilyName;
@property (nonatomic, copy, nullable) NSString *nameSuffix;
@property (nonatomic, copy, nullable) NSString *nickname;

// Organization details
@property (nonatomic, copy, nullable) NSString *organizationName;
@property (nonatomic, copy, nullable) NSString *departmentName;
@property (nonatomic, copy, nullable) NSString *jobTitle;

// Contact information collections
@property (nonatomic, copy) NSArray<CMContactPhoneNumber *> *phoneNumbers;
@property (nonatomic, copy) NSArray<CMContactEmailAddress *> *emailAddresses;
@property (nonatomic, copy) NSArray<CMContactAddress *> *addresses;
@property (nonatomic, copy) NSArray<CMContactDate *> *dates;
@property (nonatomic, copy) NSArray<CMContactURL *> *urlAddresses;
@property (nonatomic, copy) NSArray<CMContactSocialProfile *> *socialProfiles;
@property (nonatomic, copy) NSArray<CMContactRelation *> *relations;
@property (nonatomic, copy) NSArray<CMContactInstantMessage *> *instantMessageAddresses;

// Additional information
@property (nonatomic, copy, nullable) NSString *notes;
@property (nonatomic, copy, nullable) NSString *bio;
@property (nonatomic, copy, nullable) NSString *location;

// Birthday
@property (nonatomic, strong, nullable) NSDate *birthday;

// Image data
@property (nonatomic, copy, nullable) NSString *imageUrl;
@property (nonatomic, strong, nullable) NSData *imageData;
@property (nonatomic, strong, nullable) NSData *thumbnailImageData;
@property (nonatomic, assign) BOOL imageDataAvailable;

// Extra data
@property (nonatomic, copy) NSArray<NSString *> *interests;
@property (nonatomic, copy) NSArray<NSString *> *avatars;

// Sync information
@property (nonatomic, assign) BOOL isDeleted;
@property (nonatomic, assign) double dirtyTime;
@property (nonatomic, assign) double lastSyncedAt;

// Additional properties to match Swift implementation
@property (nonatomic, copy, nullable) NSString *contactSection;
@property (nonatomic, copy, nullable) NSString *matchString;
@property (nonatomic, copy, nullable) NSString *parentContactId;
@property (nonatomic, copy, nullable) NSString *sourceId;
@property (nonatomic, assign) double createdAt;

/**
 * Initialize with an identifier
 */
- (instancetype)initWithIdentifier:(NSString *)identifier;

/**
 * Updates the display name based on the contact's name components
 */
- (void)updateDisplayInfo;

/**
 * Marks the contact as dirty for syncing
 */
- (void)markAsDirty;

/**
 * Checks if two contacts are equal
 */
- (BOOL)isEqualToContact:(CMContact *)other;

/**
 * Generates a search match string containing all contact information
 */
- (NSString *)generateMatchString;

/**
 * Creates a section identifier based on the contact's name
 */
- (NSString *)contactSectionForName;

/**
 * Converts the contact to a server-compatible dictionary format
 * @param organizationId The organization ID to associate with the contact
 * @param sourceId The source ID to associate with the contact
 * @return A dictionary representation suitable for server API calls
 */
- (NSDictionary *)toServerContactWithOrganizationId:(NSString *)organizationId sourceId:(NSString *)sourceId;

@end

NS_ASSUME_NONNULL_END 
