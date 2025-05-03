//
//  CMAPIClient.h
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

#if __has_include(<ContactsManagerObjc/CMContactSource.h>)
#import <ContactsManagerObjc/CMContactSource.h>
#elif __has_include("CMContactSource.h")
#import "CMContactSource.h"
#endif

#if __has_include(<ContactsManagerObjc/CMDeviceInfo.h>)
#import <ContactsManagerObjc/CMDeviceInfo.h>
#elif __has_include("CMDeviceInfo.h")
#import "CMDeviceInfo.h"
#endif

#if __has_include(<ContactsManagerObjc/CMUserInfo.h>)
#import <ContactsManagerObjc/CMUserInfo.h>
#elif __has_include("CMUserInfo.h")
#import "CMUserInfo.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@class CMContactService;

/**
 * API response structure
 */
@interface CMAPIResponse<ObjectType> : NSObject

@property (nonatomic, copy, readonly) NSString *status;
@property (nonatomic, copy, readonly, nullable) NSString *message;
@property (nonatomic, strong, readonly, nullable) ObjectType data;

- (instancetype)initWithStatus:(NSString *)status 
                       message:(nullable NSString *)message 
                          data:(nullable ObjectType)data;

@end

/**
 * Token response structure
 */
@interface CMTokenResponse : NSObject

@property (nonatomic, copy, readonly) NSString *token;
@property (nonatomic, assign, readonly) NSInteger expiresAt;

- (instancetype)initWithToken:(NSString *)token expiresAt:(NSInteger)expiresAt;

@end

/**
 * API client for ContactsManager service
 */
@interface CMAPIClient : NSObject

/**
 * Shared singleton instance
 */
@property (class, nonatomic, readonly) CMAPIClient *sharedInstance;

/**
 * Device info for the client
 */
@property (nonatomic, strong, readonly) CMDeviceInfo *deviceInfo;

/**
 * Initialize with user ID
 */
- (instancetype)initWithUserId:(NSString *)userId;

/**
 * Initialize with user ID and device info
 */
- (instancetype)initWithUserId:(NSString *)userId deviceInfo:(nullable CMDeviceInfo *)deviceInfo NS_DESIGNATED_INITIALIZER;

/**
 * Unavailable initializer. Use sharedInstance or initWithUserId: instead.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 * Unavailable initializer. Use sharedInstance or initWithUserId: instead.
 */
+ (instancetype)new NS_UNAVAILABLE;

/**
 * Set the ContactService to use for sync operations
 */
- (void)setContactService:(CMContactService *)service;

/**
 * Refresh authentication token
 */
- (void)refreshTokenWithCompletionHandler:(void (^)(NSString * _Nullable token, NSError * _Nullable error))completion;

/**
 * Create a contact source
 */
- (void)createContactSourceWithName:(NSString *)name 
                         sourceType:(CMSourceType)sourceType
                 completionHandler:(void (^)(CMContactSource * _Nullable source, NSError * _Nullable error))completion;

/**
 * Sync contacts with the server
 */
- (void)syncContacts:(NSArray<CMContact *> *)contacts 
      skipDuplicates:(BOOL)skipDuplicates
   completionHandler:(void (^)(NSInteger processedCount, NSError * _Nullable error))completion;

/**
 * Get user info from the server
 */
- (void)getUserInfoWithCompletionHandler:(void (^)(NSDictionary * _Nullable userInfo, NSError * _Nullable error))completion;

/**
 * Validate API key with token and user info
 * @param apiKey API key to validate
 * @param token User's authentication token
 * @param userInfo User information
 * @param completion Block called when validation completes
 */
- (void)validateAPIKey:(NSString *)apiKey
             withToken:(NSString *)token
              userInfo:(CMUserInfo *)userInfo
            completion:(void (^)(BOOL success, NSError * _Nullable error))completion;

/**
 * Check health of the service
 * @param completion Block called with health status
 */
- (void)checkHealthWithCompletion:(void (^)(BOOL healthy))completion;

/**
 * Cancel all pending API requests
 */
- (void)cancelAllRequests;

#pragma mark - Generic HTTP Methods

/**
 * Perform a GET request
 * @param endpoint The API endpoint to call
 * @param parameters Optional query parameters
 * @param requiresAuth Whether the request requires authentication (default: YES)
 * @param completion Block to be called when the request is completed
 */
- (void)get:(NSString *)endpoint 
 parameters:(nullable NSDictionary<NSString *, NSString *> *)parameters
requiresAuth:(BOOL)requiresAuth
 completion:(void (^)(id _Nullable responseObject, NSError * _Nullable error))completion;

/**
 * Perform a POST request
 * @param endpoint The API endpoint to call
 * @param body The request body
 * @param parameters Optional query parameters
 * @param requiresAuth Whether the request requires authentication (default: YES)
 * @param completion Block to be called when the request is completed
 */
- (void)post:(NSString *)endpoint 
        body:(nullable id)body
  parameters:(nullable NSDictionary<NSString *, NSString *> *)parameters
requiresAuth:(BOOL)requiresAuth
  completion:(void (^)(id _Nullable responseObject, NSError * _Nullable error))completion;

/**
 * Perform a PUT request
 * @param endpoint The API endpoint to call
 * @param body The request body
 * @param parameters Optional query parameters
 * @param requiresAuth Whether the request requires authentication (default: YES)
 * @param completion Block to be called when the request is completed
 */
- (void)put:(NSString *)endpoint 
       body:(nullable id)body
 parameters:(nullable NSDictionary<NSString *, NSString *> *)parameters
requiresAuth:(BOOL)requiresAuth
 completion:(void (^)(id _Nullable responseObject, NSError * _Nullable error))completion;

/**
 * Perform a DELETE request
 * @param endpoint The API endpoint to call
 * @param parameters Optional query parameters
 * @param requiresAuth Whether the request requires authentication (default: YES)
 * @param completion Block to be called when the request is completed
 */
- (void)delete:(NSString *)endpoint
   parameters:(nullable NSDictionary<NSString *, NSString *> *)parameters
 requiresAuth:(BOOL)requiresAuth
   completion:(void (^)(id _Nullable responseObject, NSError * _Nullable error))completion;

/**
 * Get social data with special response handling
 * @param endpoint The API endpoint to call
 * @param parameters Optional query parameters
 * @param completion Block to be called when the request is completed
 */
- (void)getSocialData:(NSString *)endpoint
          parameters:(nullable NSDictionary<NSString *, NSString *> *)parameters
          completion:(void (^)(id _Nullable responseObject, NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END 
