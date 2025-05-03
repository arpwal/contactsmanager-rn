//
//  CMRecommendationService.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>

#if __has_include(<ContactsManagerObjc/CMContact.h>)
#import <ContactsManagerObjc/CMContact.h>
#elif __has_include("CMContact.h")
#import "CMContact.h"
#endif

#if __has_include(<ContactsManagerObjc/CMSocialModels.h>)
#import <ContactsManagerObjc/CMSocialModels.h>
#elif __has_include("CMSocialModels.h")
#import "CMSocialModels.h"
#endif

#if __has_include(<ContactsManagerObjc/CMAPIClient.h>)
#import <ContactsManagerObjc/CMAPIClient.h>
#elif __has_include("CMAPIClient.h")
#import "CMAPIClient.h"
#endif

@class CMContactService;

NS_ASSUME_NONNULL_BEGIN

/**
 * Types of contact recommendations
 */
typedef NS_ENUM(NSInteger, CMRecommendationType) {
    CMRecommendationTypeInviteRecommendations,
    CMRecommendationTypeAppUsers,
    CMRecommendationTypeUsersYouMightKnow
};

/**
 * CMContactRecommendation - Represents a recommendation result with metadata
 */
@interface CMContactRecommendation : NSObject

@property (nonatomic, strong, readonly) CMContact *contact;
@property (nonatomic, assign, readonly) double score;
@property (nonatomic, copy, readonly) NSString *reason;
@property (nonatomic, assign, readonly) CMRecommendationType type;
@property (nonatomic, copy, readonly, nullable) NSString *organizationUserId;

/**
 * Initialize with contact, score, reason, type, and organization user ID
 */
- (instancetype)initWithContact:(CMContact *)contact
                          score:(double)score
                         reason:(NSString *)reason
                           type:(CMRecommendationType)type
              organizationUserId:(nullable NSString *)organizationUserId;

@end

/**
 * CMRecommendationService - Service responsible for providing contact recommendations
 */
@interface CMRecommendationService : NSObject

/**
 * Initialize with API client
 * @note This method is for internal use by CMContactService only.
 *       Use [CMContactService recommendationService] to get an instance.
 */
- (instancetype)initWithAPIClient:(CMAPIClient *)apiClient NS_UNAVAILABLE;

/**
 * Initialize with API client (using default if nil is provided)
 * @note This method is for internal use by CMContactService only.
 *       Use [CMContactService recommendationService] to get an instance.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 * Initialize the recommendation service with a contact service
 * @param contactService The contact service instance
 * @note This method is for internal use by CMContactService only.
 *       Use [CMContactService recommendationService] to get an instance.
 */
- (instancetype)initWithContactService:(CMContactService *)contactService; // Internal method - do not use directly

/**
 * Get recommended contacts to invite to the app
 * @param limit Maximum number of recommendations to return (default: 30)
 * @param completion Callback with the array of recommendations or an error
 */
- (void)getSharedContactsByUsersToInviteWithLimit:(NSInteger)limit
                                       completion:(void (^)(NSArray<CMContactRecommendation *> * _Nullable recommendations, NSError * _Nullable error))completion;

/**
 * Get contacts who are also using the app
 * @param limit Maximum number of recommendations to return (default: 30)
 * @param completion Callback with the array of recommendations or an error
 */
- (void)getContactsUsingAppWithLimit:(NSInteger)limit
                          completion:(void (^)(NSArray<CMContactRecommendation *> * _Nullable recommendations, NSError * _Nullable error))completion;

/**
 * Get users that the current user might know based on matching phone numbers or email addresses
 * @param limit Maximum number of users to return (default: 30)
 * @param completion Callback with the array of canonical contacts or an error
 */
- (void)getUsersYouMightKnowWithLimit:(NSInteger)limit
                           completion:(void (^)(NSArray<CMCanonicalContact *> * _Nullable contacts, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END 
