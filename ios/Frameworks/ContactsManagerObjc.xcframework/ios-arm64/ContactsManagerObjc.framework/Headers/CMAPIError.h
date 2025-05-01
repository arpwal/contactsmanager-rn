//
//  CMAPIError.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Error domain for ContactsManager API errors
 */
extern NSString * const CMAPIErrorDomain;

/**
 * Error codes for ContactsManager API errors
 */
typedef NS_ENUM(NSInteger, CMAPIErrorCode) {
    CMAPIErrorInvalidURL,
    CMAPIErrorNoData,
    CMAPIErrorDecodingError,
    CMAPIErrorServerError,
    CMAPIErrorNetworkError,
    CMAPIErrorUnauthorized,
    CMAPIErrorTokenExpired,
    CMAPIErrorUnknownError,
    CMAPIErrorCodeInvalidResponse,
    CMAPIErrorCodeInvalidAPIKey,
    CMAPIErrorCodeValidationFailed
};

/**
 * Utility class for creating API errors
 */
@interface CMAPIError : NSObject

/**
 * Create an error with the specified code and message
 */
+ (NSError *)errorWithCode:(CMAPIErrorCode)code;

/**
 * Create an error with the specified code and message
 */
+ (NSError *)errorWithCode:(CMAPIErrorCode)code message:(NSString *)message;

/**
 * Create an invalidURL error
 */
+ (NSError *)invalidURLError;

/**
 * Create a noData error
 */
+ (NSError *)noDataError;

/**
 * Create a decodingError error
 */
+ (NSError *)decodingError;

/**
 * Create a serverError with status code and message
 */
+ (NSError *)serverErrorWithStatusCode:(NSInteger)statusCode message:(NSString *)message;

/**
 * Create a networkError wrapping an underlying error
 */
+ (NSError *)networkErrorWithUnderlyingError:(NSError *)error;

/**
 * Create an unauthorized error
 */
+ (NSError *)unauthorizedError;

/**
 * Create a tokenExpired error
 */
+ (NSError *)tokenExpiredError;

/**
 * Create an unknownError error
 */
+ (NSError *)unknownError;

/**
 * Get a localized description for an error code
 */
+ (NSString *)localizedDescriptionForErrorCode:(CMAPIErrorCode)code
                                   statusCode:(nullable NSNumber *)statusCode
                                      message:(nullable NSString *)message;

@end

NS_ASSUME_NONNULL_END 
