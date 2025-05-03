//
//  CMServerModels.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/25/25.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CMServerContact;
@class CMServerContactPhoneNumber;
@class CMServerContactEmailAddress;
@class CMServerContactURLAddress;
@class CMServerContactSocialProfile;
@class CMServerContactAddress;
@class CMServerContactInstantMessage;
@class CMServerContactRelation;
@class CMServerContactDate;

#pragma mark - CMServerContactBulkCreate

@interface CMServerContactBulkCreate : NSObject <NSCoding, NSSecureCoding>

@property (nonatomic, strong) NSArray<CMServerContact *> *contacts;
@property (nonatomic, assign) BOOL skipDuplicates;

- (instancetype)initWithContacts:(NSArray<CMServerContact *> *)contacts
                 skipDuplicates:(BOOL)skipDuplicates;

- (NSDictionary *)toDictionary;

@end

#pragma mark - CMServerContactDate

@interface CMServerContactDate : NSObject <NSCoding, NSSecureCoding>

@property (nonatomic, strong, nullable) NSString *identifier;
@property (nonatomic, strong) NSString *label;
@property (nonatomic, strong) NSString *date; // ISO 8601 date string
@property (nonatomic, assign) BOOL isPrimary;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                             label:(NSString *)label
                              date:(NSString *)date
                         isPrimary:(BOOL)isPrimary;

- (NSDictionary *)toDictionary;
+ (instancetype)fromDictionary:(NSDictionary *)dictionary;

@end

#pragma mark - CMServerContactInstantMessage

@interface CMServerContactInstantMessage : NSObject <NSCoding, NSSecureCoding>

@property (nonatomic, strong, nullable) NSString *identifier;
@property (nonatomic, strong) NSString *service;
@property (nonatomic, strong, nullable) NSString *username;
@property (nonatomic, strong, nullable) NSString *userIdentifier;
@property (nonatomic, strong) NSString *type;
@property (nonatomic, assign) BOOL isPrimary;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                           service:(NSString *)service
                          username:(nullable NSString *)username
                    userIdentifier:(nullable NSString *)userIdentifier
                              type:(NSString *)type
                         isPrimary:(BOOL)isPrimary;

- (NSDictionary *)toDictionary;
+ (instancetype)fromDictionary:(NSDictionary *)dictionary;

@end

#pragma mark - CMServerContactRelation

@interface CMServerContactRelation : NSObject <NSCoding, NSSecureCoding>

@property (nonatomic, strong, nullable) NSString *identifier;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *relationType;
@property (nonatomic, strong, nullable) NSString *notes;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                              name:(NSString *)name
                      relationType:(NSString *)relationType
                             notes:(nullable NSString *)notes;

- (NSDictionary *)toDictionary;
+ (instancetype)fromDictionary:(NSDictionary *)dictionary;

@end

#pragma mark - CMServerContactPhoneNumber

@interface CMServerContactPhoneNumber : NSObject <NSCoding, NSSecureCoding>

@property (nonatomic, strong, nullable) NSString *identifier;
@property (nonatomic, strong) NSString *type;
@property (nonatomic, strong) NSString *label;
@property (nonatomic, strong) NSString *value;
@property (nonatomic, assign) BOOL isPrimary;
@property (nonatomic, strong, nullable) NSString *emoji;
@property (nonatomic, strong, nullable) NSString *phoneId;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                              type:(NSString *)type
                             value:(NSString *)value
                         isPrimary:(BOOL)isPrimary
                             emoji:(nullable NSString *)emoji
                           phoneId:(nullable NSString *)phoneId;

- (NSDictionary *)toDictionary;
+ (instancetype)fromDictionary:(NSDictionary *)dictionary;

@end

#pragma mark - CMServerContactEmailAddress

@interface CMServerContactEmailAddress : NSObject <NSCoding, NSSecureCoding>

@property (nonatomic, strong, nullable) NSString *identifier;
@property (nonatomic, strong) NSString *type;
@property (nonatomic, strong) NSString *label;
@property (nonatomic, strong) NSString *value;
@property (nonatomic, assign) BOOL isPrimary;
@property (nonatomic, strong, nullable) NSString *emoji;
@property (nonatomic, strong, nullable) NSString *emailId;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                              type:(NSString *)type
                             value:(NSString *)value
                         isPrimary:(BOOL)isPrimary
                             emoji:(nullable NSString *)emoji
                           emailId:(nullable NSString *)emailId;

- (NSDictionary *)toDictionary;
+ (instancetype)fromDictionary:(NSDictionary *)dictionary;

@end

#pragma mark - CMServerContactURLAddress

@interface CMServerContactURLAddress : NSObject <NSCoding, NSSecureCoding>

@property (nonatomic, strong, nullable) NSString *identifier;
@property (nonatomic, strong) NSString *type;
@property (nonatomic, strong) NSString *label;
@property (nonatomic, strong) NSString *value;
@property (nonatomic, assign) BOOL isPrimary;
@property (nonatomic, strong, nullable) NSString *emoji;
@property (nonatomic, strong, nullable) NSString *urlId;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                              type:(NSString *)type
                             value:(NSString *)value
                         isPrimary:(BOOL)isPrimary
                             emoji:(nullable NSString *)emoji
                            urlId:(nullable NSString *)urlId;

- (NSDictionary *)toDictionary;
+ (instancetype)fromDictionary:(NSDictionary *)dictionary;

@end

#pragma mark - CMServerContactSocialProfile

@interface CMServerContactSocialProfile : NSObject <NSCoding, NSSecureCoding>

@property (nonatomic, strong, nullable) NSString *identifier;
@property (nonatomic, strong) NSString *platform;
@property (nonatomic, strong, nullable) NSString *username;
@property (nonatomic, strong, nullable) NSString *url;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                          platform:(NSString *)platform
                          username:(nullable NSString *)username
                               url:(nullable NSString *)url;

- (NSDictionary *)toDictionary;
+ (instancetype)fromDictionary:(NSDictionary *)dictionary;

@end

#pragma mark - CMServerContactAddress

@interface CMServerContactAddress : NSObject <NSCoding, NSSecureCoding>

@property (nonatomic, strong, nullable) NSString *identifier;
@property (nonatomic, strong, nullable) NSString *type;
@property (nonatomic, strong) NSString *label;
@property (nonatomic, strong, nullable) NSString *streetAddress;
@property (nonatomic, strong, nullable) NSString *extendedAddress;
@property (nonatomic, strong, nullable) NSString *city;
@property (nonatomic, strong, nullable) NSString *region;
@property (nonatomic, strong, nullable) NSString *postalCode;
@property (nonatomic, strong, nullable) NSString *country;
@property (nonatomic, assign) BOOL isPrimary;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                              type:(nullable NSString *)type
                             label:(NSString *)label
                     streetAddress:(nullable NSString *)streetAddress
                   extendedAddress:(nullable NSString *)extendedAddress
                              city:(nullable NSString *)city
                            region:(nullable NSString *)region
                        postalCode:(nullable NSString *)postalCode
                           country:(nullable NSString *)country
                         isPrimary:(BOOL)isPrimary;

- (NSDictionary *)toDictionary;
+ (instancetype)fromDictionary:(NSDictionary *)dictionary;

@end

#pragma mark - CMServerContact

@interface CMServerContact : NSObject <NSCoding, NSSecureCoding>

@property (nonatomic, strong, nullable) NSString *identifier;
@property (nonatomic, strong) NSString *displayName;
@property (nonatomic, strong, nullable) NSString *givenName;
@property (nonatomic, strong, nullable) NSString *familyName;
@property (nonatomic, strong, nullable) NSString *namePrefix;
@property (nonatomic, strong, nullable) NSString *nameSuffix;
@property (nonatomic, strong, nullable) NSString *middleName;
@property (nonatomic, strong, nullable) NSString *previousFamilyName;
@property (nonatomic, strong) NSString *nickname;
@property (nonatomic, strong) NSString *notes;
@property (nonatomic, strong, nullable) NSString *bio;
@property (nonatomic, strong, nullable) NSString *location;
@property (nonatomic, strong, nullable) NSString *contactSection;
@property (nonatomic, strong) NSString *organizationId;
@property (nonatomic, strong) NSString *sourceId;
@property (nonatomic, strong, nullable) NSString *sourceContactId;
@property (nonatomic, strong) NSArray<CMServerContactPhoneNumber *> *phoneNumbers;
@property (nonatomic, strong) NSArray<CMServerContactEmailAddress *> *emailAddresses;
@property (nonatomic, strong) NSArray<CMServerContactURLAddress *> *urls;
@property (nonatomic, strong) NSArray<CMServerContactSocialProfile *> *socialProfiles;
@property (nonatomic, strong) NSArray<CMServerContactAddress *> *addresses;
@property (nonatomic, strong) NSArray<CMServerContactInstantMessage *> *instantMessageAddresses;
@property (nonatomic, strong) NSArray<CMServerContactRelation *> *relations;
@property (nonatomic, strong) NSArray<NSString *> *tags;
@property (nonatomic, strong) NSDictionary<NSString *, NSString *> *customFields;
@property (nonatomic, strong, nullable) NSString *matchString;

// Organization information
@property (nonatomic, strong, nullable) NSString *organizationName;
@property (nonatomic, strong, nullable) NSString *departmentName;
@property (nonatomic, strong, nullable) NSString *jobTitle;

// Dates
@property (nonatomic, strong, nullable) NSString *birthday; // ISO 8601 date string
@property (nonatomic, strong) NSArray<CMServerContactDate *> *dates;

// Contact type
@property (nonatomic, assign) NSInteger contactType; // 0 = person, 1 = organization

- (instancetype)initWithDisplayName:(NSString *)displayName
                     organizationId:(NSString *)organizationId
                           sourceId:(NSString *)sourceId;

- (NSDictionary *)toDictionary;
+ (instancetype)fromDictionary:(NSDictionary *)dictionary;

@end

NS_ASSUME_NONNULL_END 