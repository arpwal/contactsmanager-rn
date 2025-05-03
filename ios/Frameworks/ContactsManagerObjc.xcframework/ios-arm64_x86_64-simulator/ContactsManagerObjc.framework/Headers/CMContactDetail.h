//
//  CMContactDetail.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Phone Number

/**
 * CMContactPhoneNumber class representing a phone number for a contact
 */
@interface CMContactPhoneNumber : NSObject

@property (nonatomic, copy, readonly) NSString *contactId;
@property (nonatomic, copy) NSString *value;
@property (nonatomic, copy, nullable) NSString *type;
@property (nonatomic, copy, nullable) NSString *emoji;

/**
 * Initialize with contact ID and value
 */
- (instancetype)initWithContactId:(NSString *)contactId value:(NSString *)value;

/**
 * Initialize with contact ID, value, and type
 */
- (instancetype)initWithContactId:(NSString *)contactId value:(NSString *)value type:(nullable NSString *)type;

/**
 * Initialize with contact ID, value, type, and emoji
 */
- (instancetype)initWithContactId:(NSString *)contactId value:(NSString *)value type:(nullable NSString *)type emoji:(nullable NSString *)emoji;

@end

#pragma mark - Email Address

/**
 * CMContactEmailAddress class representing an email address for a contact
 */
@interface CMContactEmailAddress : NSObject

@property (nonatomic, copy, readonly) NSString *contactId;
@property (nonatomic, copy) NSString *value;
@property (nonatomic, copy, nullable) NSString *type;
@property (nonatomic, copy, nullable) NSString *emoji;

/**
 * Initialize with contact ID and value
 */
- (instancetype)initWithContactId:(NSString *)contactId value:(NSString *)value;

/**
 * Initialize with contact ID, value, and type
 */
- (instancetype)initWithContactId:(NSString *)contactId value:(NSString *)value type:(nullable NSString *)type;

/**
 * Initialize with contact ID, value, type, and emoji
 */
- (instancetype)initWithContactId:(NSString *)contactId value:(NSString *)value type:(nullable NSString *)type emoji:(nullable NSString *)emoji;

@end

#pragma mark - Address

/**
 * CMContactAddress class representing a physical address for a contact
 */
@interface CMContactAddress : NSObject

@property (nonatomic, copy, readonly) NSString *contactId;
@property (nonatomic, copy, nullable) NSString *street;
@property (nonatomic, copy, nullable) NSString *city;
@property (nonatomic, copy, nullable) NSString *state;
@property (nonatomic, copy, nullable) NSString *postalCode;
@property (nonatomic, copy, nullable) NSString *country;
@property (nonatomic, copy, nullable) NSString *type;
@property (nonatomic, copy, nullable) NSString *emoji;

/**
 * Initialize with contact ID
 */
- (instancetype)initWithContactId:(NSString *)contactId;

@end

#pragma mark - Date

/**
 * CMContactDate class representing a date associated with a contact
 */
@interface CMContactDate : NSObject

@property (nonatomic, copy, readonly) NSString *contactId;
@property (nonatomic, strong) NSDate *date;
@property (nonatomic, copy, nullable) NSString *type;

/**
 * Initialize with contact ID and date
 */
- (instancetype)initWithContactId:(NSString *)contactId date:(NSDate *)date;

/**
 * Initialize with contact ID, date, and type
 */
- (instancetype)initWithContactId:(NSString *)contactId date:(NSDate *)date type:(nullable NSString *)type;

@end

#pragma mark - URL

/**
 * CMContactURL class representing a URL for a contact
 */
@interface CMContactURL : NSObject

@property (nonatomic, copy, readonly) NSString *contactId;
@property (nonatomic, copy) NSString *value;
@property (nonatomic, copy, nullable) NSString *type;
@property (nonatomic, copy, nullable) NSString *emoji;

/**
 * Initialize with contact ID and value
 */
- (instancetype)initWithContactId:(NSString *)contactId value:(NSString *)value;

/**
 * Initialize with contact ID, value, and type
 */
- (instancetype)initWithContactId:(NSString *)contactId value:(NSString *)value type:(nullable NSString *)type;

/**
 * Initialize with contact ID, value, type, and emoji
 */
- (instancetype)initWithContactId:(NSString *)contactId value:(NSString *)value type:(nullable NSString *)type emoji:(nullable NSString *)emoji;

@end

#pragma mark - Social Profile

/**
 * CMContactSocialProfile class representing a social profile for a contact
 */
@interface CMContactSocialProfile : NSObject

@property (nonatomic, copy, readonly) NSString *contactId;
@property (nonatomic, copy) NSString *service;
@property (nonatomic, copy, nullable) NSString *username;
@property (nonatomic, copy, nullable) NSString *urlString;

/**
 * Initialize with contact ID and service
 */
- (instancetype)initWithContactId:(NSString *)contactId service:(NSString *)service;

@end

#pragma mark - Relation

/**
 * CMContactRelation class representing a relationship for a contact
 */
@interface CMContactRelation : NSObject

@property (nonatomic, copy, readonly) NSString *contactId;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy, nullable) NSString *type;

/**
 * Initialize with contact ID and name
 */
- (instancetype)initWithContactId:(NSString *)contactId name:(NSString *)name;

/**
 * Initialize with contact ID, name, and type
 */
- (instancetype)initWithContactId:(NSString *)contactId name:(NSString *)name type:(nullable NSString *)type;

@end

#pragma mark - Instant Message

/**
 * CMContactInstantMessage class representing an instant message address for a contact
 */
@interface CMContactInstantMessage : NSObject

@property (nonatomic, copy, readonly) NSString *contactId;
@property (nonatomic, copy) NSString *service;
@property (nonatomic, copy) NSString *username;
@property (nonatomic, copy, nullable) NSString *type;

/**
 * Initialize with contact ID, service, and username
 */
- (instancetype)initWithContactId:(NSString *)contactId service:(NSString *)service username:(NSString *)username;

@end

NS_ASSUME_NONNULL_END 