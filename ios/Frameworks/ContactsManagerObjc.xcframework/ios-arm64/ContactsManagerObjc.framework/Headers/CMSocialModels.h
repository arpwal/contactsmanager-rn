//
//  CMSocialModels.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <ContactsManagerObjc/CMContact.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Base protocol for all social API responses
 */
@interface CMSocialResponse<ObjectType> : NSObject

@property(nonatomic, copy, readonly) NSString *status;
@property(nonatomic, copy, readonly, nullable) NSString *message;
@property(nonatomic, strong, readonly) ObjectType data;

- (instancetype)initWithStatus:(NSString *)status
                       message:(nullable NSString *)message
                          data:(ObjectType)data;

@end

/**
 * Represents a canonical contact from the server with match information
 */
@interface CMCanonicalContact : NSObject <NSCopying>

@property(nonatomic, copy, readonly) NSString *identifier;
@property(nonatomic, copy, readonly, nullable) NSString *organizationId;
@property(nonatomic, copy, readonly) NSString *organizationUserId;
@property(nonatomic, copy, readonly, nullable) NSString *email;
@property(nonatomic, copy, readonly, nullable) NSString *phone;
@property(nonatomic, copy, readonly) NSString *fullName;
@property(nonatomic, copy, readonly, nullable) NSString *avatarUrl;
@property(nonatomic, assign, readonly) BOOL isActive;
@property(nonatomic, strong, readonly, nullable) NSDate *createdAt;
@property(nonatomic, strong, readonly, nullable) NSDate *updatedAt;
@property(nonatomic, strong, readonly, nullable)
    NSDictionary<NSString *, id> *contactMetadata;

- (instancetype)initWithId:(NSString *)identifier
            organizationId:(nullable NSString *)organizationId
            organizationUserId:(NSString *)organizationUserId
                     email:(nullable NSString *)email
                     phone:(nullable NSString *)phone
                  fullName:(NSString *)fullName
                 avatarUrl:(nullable NSString *)avatarUrl
                  isActive:(BOOL)isActive
                 createdAt:(nullable NSDate *)createdAt
                 updatedAt:(nullable NSDate *)updatedAt
           contactMetadata:
               (nullable NSDictionary<NSString *, id> *)contactMetadata;

// Comparison method
- (BOOL)isEqualToCanonicalContact:(CMCanonicalContact *)other;

// Convenience method to convert to a dictionary
- (NSDictionary *)toDictionary;

// Create a new copy with updated properties
- (instancetype)copyWithUpdates:(NSDictionary *)updates;

@end

/**
 * Represents a contact that exists both locally on device and in the canonical contacts system
 */
@interface CMLocalCanonicalContact : NSObject <NSCopying>

@property(nonatomic, strong, readonly, nullable) CMContact *contact;
@property(nonatomic, copy, readonly) NSString *contactId;
@property(nonatomic, copy, readonly) NSString *sourceContactId;
@property(nonatomic, strong, readonly) CMCanonicalContact *canonicalContact;

- (instancetype)initWithContact:(nullable CMContact *)contact
                      contactId:(NSString *)contactId
                sourceContactId:(NSString *)sourceContactId
               canonicalContact:(CMCanonicalContact *)canonicalContact;

// Comparison method
- (BOOL)isEqualToLocalCanonicalContact:(CMLocalCanonicalContact *)other;

// Convert to dictionary for serialization
- (NSDictionary *)toDictionary;

@end

#pragma mark - Follow Models

@interface CMFollowRelationship : NSObject <NSCopying>

@property(nonatomic, strong, readonly) NSString *identifier;
@property(nonatomic, strong, readonly) NSString *followerId;
@property(nonatomic, strong, readonly) NSString *followedId;
@property(nonatomic, strong, readonly) NSString *userId;
@property(nonatomic, strong, readonly) NSString *displayName;
@property(nonatomic, strong, readonly, nullable) NSString *photoURL;
@property(nonatomic, strong, readonly, nullable) NSString *username;
@property(nonatomic, strong, readonly, nullable) NSString *bio;
@property(nonatomic, strong, readonly, nullable) NSString *website;
@property(nonatomic, strong, readonly, nullable) NSDate *createdAt;
@property(nonatomic, assign, readonly) BOOL isFollowing;
@property(nonatomic, strong) CMContact *_Nullable localContact;
@property(nonatomic, strong, readonly, nullable) CMCanonicalContact *follower;
@property(nonatomic, strong, readonly, nullable) CMCanonicalContact *followed;
@property(nonatomic, strong, readonly, nullable) NSString *contactId;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary *)toDictionary;

@end

@interface CMPaginatedFollowList : NSObject <NSCopying>

@property(nonatomic, strong) NSArray<CMFollowRelationship *> *items;
@property(nonatomic, assign) NSInteger total;
@property(nonatomic, assign) NSInteger skip;
@property(nonatomic, assign) NSInteger limit;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary *)toDictionary;

@end

@interface CMPaginatedMutualFollowers : NSObject

@property(nonatomic, strong) NSArray<CMCanonicalContact *> *items;
@property(nonatomic, assign) NSInteger total;
@property(nonatomic, assign) NSInteger skip;
@property(nonatomic, assign) NSInteger limit;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;

@end

@interface CMFollowActionResponse : NSObject

@property(nonatomic, strong, readonly, nullable) NSString *message;
@property(nonatomic, assign, readonly) BOOL alreadyFollowing;
@property(nonatomic, assign, readonly) BOOL wasFollowing;
@property(nonatomic, assign, readonly) BOOL success;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary *)toDictionary;

@end

@interface CMFollowStatusResponse : NSObject

@property(nonatomic, assign, readonly) BOOL isFollowing;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary *)toDictionary;

@end

#pragma mark - Event Models

@interface CMEventCreator : NSObject

@property(nonatomic, strong, readonly, nullable) NSString *name;
@property(nonatomic, strong, readonly, nullable) NSString *avatarUrl;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary *)toDictionary;

@end

@interface CMSocialEvent : NSObject

@property(nonatomic, strong, readonly) NSString *eventId;
@property(nonatomic, strong, readonly) NSString *organizationId;
@property(nonatomic, strong, readonly) NSString *canonicalContactId;
@property(nonatomic, strong, readonly) NSString *eventType;
@property(nonatomic, strong, readonly) NSString *title;
@property(nonatomic, strong, readonly, nullable) NSString *description;
@property(nonatomic, strong, readonly, nullable) NSString *location;
@property(nonatomic, strong, readonly, nullable) NSDate *startTime;
@property(nonatomic, strong, readonly, nullable) NSDate *endTime;
@property(nonatomic, strong, readonly, nullable) NSDictionary<NSString *, NSString *> *metadata;
@property(nonatomic, assign, readonly) BOOL isPublic;
@property(nonatomic, strong, readonly) NSDate *createdAt;
@property(nonatomic, strong, readonly, nullable) NSDate *updatedAt;
@property(nonatomic, strong, readonly, nullable) NSString *userId;
@property(nonatomic, strong, readonly, nullable) CMEventCreator *createdBy;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary *)toDictionary;

@end

@interface CMPaginatedEventList : NSObject

@property(nonatomic, strong) NSArray<CMSocialEvent *> *items;
@property(nonatomic, assign) NSInteger total;
@property(nonatomic, assign) NSInteger skip;
@property(nonatomic, assign) NSInteger limit;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary *)toDictionary;

@end

@interface CMEventActionResponse : NSObject

@property(nonatomic, strong, readonly, nullable) NSString *message;
@property(nonatomic, strong, readonly, nullable) NSString *eventId;
@property(nonatomic, assign, readonly) BOOL created;
@property(nonatomic, assign, readonly) BOOL updated;
@property(nonatomic, assign, readonly) BOOL deleted;
@property(nonatomic, assign, readonly) BOOL success;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary *)toDictionary;

@end

@interface CMCreateEventRequest : NSObject

@property(nonatomic, strong) NSString *eventType;
@property(nonatomic, strong) NSString *title;
@property(nonatomic, strong, nullable) NSString *description;
@property(nonatomic, strong, nullable) NSString *location;
@property(nonatomic, strong, nullable) NSDate *startTime;
@property(nonatomic, strong, nullable) NSDate *endTime;
@property(nonatomic, strong, nullable) NSDictionary<NSString *, NSString *> *metadata;
@property(nonatomic, assign) BOOL isPublic;

- (instancetype)initWithEventType:(NSString *)eventType
                            title:(NSString *)title
                      description:(nullable NSString *)description
                         location:(nullable NSString *)location
                        startTime:(nullable NSDate *)startTime
                          endTime:(nullable NSDate *)endTime
                         metadata:(nullable NSDictionary<NSString *, NSString *> *)metadata
                         isPublic:(BOOL)isPublic;

- (NSDictionary *)toDictionary;

@end

@interface CMUpdateEventRequest : NSObject

@property(nonatomic, strong, nullable) NSString *title;
@property(nonatomic, strong, nullable) NSString *description;
@property(nonatomic, strong, nullable) NSString *location;
@property(nonatomic, strong, nullable) NSDate *startTime;
@property(nonatomic, strong, nullable) NSDate *endTime;
@property(nonatomic, strong, nullable) NSDictionary<NSString *, NSString *> *metadata;
@property(nonatomic, strong, nullable) NSNumber *isPublic;

- (instancetype)init;
- (NSDictionary *)toDictionary;

@end

NS_ASSUME_NONNULL_END
