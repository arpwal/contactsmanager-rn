//
//  CMAPIConfig.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Runtime environment enumeration
 */
typedef NS_ENUM(NSInteger, CMRuntimeEnvironment) {
    CMRuntimeEnvironmentDevelopment,
    CMRuntimeEnvironmentStaging,
    CMRuntimeEnvironmentProduction
};

/**
 * CMAPIConfig - Configuration for API endpoints and settings
 */
@interface CMAPIConfig : NSObject

/**
 * Current environment setting
 */
@property (class, nonatomic, assign) CMRuntimeEnvironment environment;

/**
 * Base URL for the API
 */
@property (class, nonatomic, readonly) NSString *baseURL;

/**
 * API version
 */
@property (class, nonatomic, readonly) NSString *apiVersion;

/**
 * Important API endpoints
 */
@property (class, nonatomic, readonly) NSString *tokenEndpoint;
@property (class, nonatomic, readonly) NSString *contactsEndpoint;
@property (class, nonatomic, readonly) NSString *contactsSyncEndpoint;
@property (class, nonatomic, readonly) NSString *contactSourceEndpoint;
@property (class, nonatomic, readonly) NSString *userInfoEndpoint;

/**
 * Recommendation endpoints
 */
@property (class, nonatomic, readonly) NSString *sharedContactsToInviteEndpoint;
@property (class, nonatomic, readonly) NSString *appUserContactsEndpoint;
@property (class, nonatomic, readonly) NSString *usersYouMightKnowEndpoint;

/**
 * Social endpoints
 */
@property (class, nonatomic, readonly) NSString *socialBasePath;
@property (class, nonatomic, readonly) NSString *followEndpoint;
@property (class, nonatomic, readonly) NSString *unfollowEndpoint;
@property (class, nonatomic, readonly) NSString *isFollowingEndpoint;
@property (class, nonatomic, readonly) NSString *followersEndpoint;
@property (class, nonatomic, readonly) NSString *followingEndpoint;
@property (class, nonatomic, readonly) NSString *mutualFollowsEndpoint;
@property (class, nonatomic, readonly) NSString *eventsEndpoint;
@property (class, nonatomic, readonly) NSString *feedEndpoint;
@property (class, nonatomic, readonly) NSString *upcomingEventsEndpoint;
@property (class, nonatomic, readonly) NSString *forYouEndpoint;

/**
 * API key validation
 */
@property (class, nonatomic, readonly) NSString *validateAPIKeyEndpoint;

/**
 * Networking configuration
 */
@property (class, nonatomic, readonly) NSTimeInterval defaultTimeout;
@property (class, nonatomic, readonly) NSTimeInterval uploadTimeout;

/**
 * Request sizes
 */
@property (class, nonatomic, readonly) NSInteger maxContactsPerBatch;

/**
 * Website URL
 */
@property (class, nonatomic, readonly) NSURL *websiteURL;

/**
 * Configure with a specific environment
 */
+ (void)configureWithEnvironment:(CMRuntimeEnvironment)environment;

/**
 * Get base URL for the specified environment
 */
+ (NSURL *)baseURLForEnvironment:(CMRuntimeEnvironment)environment;

/**
 * Convert environment enum to string
 */
+ (NSString *)stringFromEnvironment:(CMRuntimeEnvironment)environment;

/**
 * Get the base URL for API requests
 */
+ (NSString *)baseURL;

/**
 * Get the endpoint for contact recommendations to invite
 */
+ (NSString *)sharedContactsToInviteEndpoint;

/**
 * Get the endpoint for app user contacts
 */
+ (NSString *)appUserContactsEndpoint;

/**
 * Get the endpoint for users you might know
 */
+ (NSString *)usersYouMightKnowEndpoint;

/**
 * Get the maximum number of contacts per sync batch
 */
+ (NSInteger)maxContactsPerBatch;

@end

NS_ASSUME_NONNULL_END 