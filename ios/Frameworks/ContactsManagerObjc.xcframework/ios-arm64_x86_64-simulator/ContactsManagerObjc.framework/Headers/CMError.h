//
//  CMError.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * CMErrorCode enum representing various error types for the ContactsManagerObjc framework
 */
typedef NS_ENUM(NSInteger, CMErrorCode) {
    CMErrorCodeInvalidAPIKey = 1000,
    CMErrorCodeAPIKeyValidationFailed,
    CMErrorCodeNetworkError,
    CMErrorCodeInitializationFailed,
    CMErrorCodeDatabaseError,
    CMErrorCodeNotInitialized,
    CMErrorCodeContactsAccessDenied,
    CMErrorCodeUserNotAuthenticated,
    CMErrorCodeInvalidUserInfo,
    CMErrorCodeInvalidOperation,
    CMErrorCodeCustomError
};

extern NSString * const CMErrorDomain;

/**
 * Error creation utilities
 */
@interface CMError : NSObject

/**
 * Create an error with the specified code and message
 */
+ (NSError *)errorWithCode:(CMErrorCode)code message:(NSString *)message;

/**
 * Create an error with the specified code, message, and underlying error
 */
+ (NSError *)errorWithCode:(CMErrorCode)code message:(NSString *)message underlyingError:(nullable NSError *)underlyingError;

@end

NS_ASSUME_NONNULL_END 