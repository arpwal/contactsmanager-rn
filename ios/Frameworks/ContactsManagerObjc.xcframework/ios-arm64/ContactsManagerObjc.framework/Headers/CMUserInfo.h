//
//  CMUserInfo.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * User information for initialization
 */
@interface CMUserInfo : NSObject

/**
 * Required: Unique identifier for the user
 */
@property (nonatomic, readonly, strong) NSString *userId;

/**
 * Optional: User's full name
 */
@property (nonatomic, readonly, strong, nullable) NSString *fullName;

/**
 * Optional: User's email address (either email or phone is required)
 * Should be normalized following these guidelines:
 * - Use lowercase (e.g., "user@example.com" not "User@Example.com")
 * - Remove '+' segments (e.g., "user@example.com" not "user+tag@example.com")
 * - For Gmail: dots can be removed/normalized (e.g., "user@gmail.com" = "u.s.e.r@gmail.com")
 * - Remove leading/trailing whitespace
 */
@property (nonatomic, readonly, strong, nullable) NSString *email;

/**
 * Optional: User's phone number (either email or phone is required)
 * Should be normalized following these guidelines:
 * - Use E.164 international format with country code
 * - No spaces, parentheses, or other separators
 * - Examples for US numbers:
 *   - "+14155552671" (not "(415) 555-2671" or "415-555-2671")
 *   - "+12025550123" (not "202-555-0123")
 *   - "+18005551234" (not "1-800-555-1234")
 */
@property (nonatomic, readonly, strong, nullable) NSString *phone;

/**
 * Optional: URL to user's avatar/profile image
 */
@property (nonatomic, readonly, strong, nullable) NSString *avatarUrl;

/**
 * Optional: Additional metadata as key-value pairs
 */
@property (nonatomic, readonly, strong, nullable) NSDictionary<NSString *, NSString *> *metadata;

/**
 * Initialize with required and optional parameters
 * @param userId Required unique identifier
 * @param fullName Optional user's full name
 * @param email Optional email address (should be normalized to lowercase without '+' segments)
 * @param phone Optional phone number (should be in E.164 format with country code, e.g., "+14155552671")
 * @param avatarUrl Optional avatar URL
 * @param metadata Optional additional metadata
 */
- (instancetype)initWithUserId:(NSString *)userId
                      fullName:(nullable NSString *)fullName
                         email:(nullable NSString *)email
                         phone:(nullable NSString *)phone
                     avatarUrl:(nullable NSString *)avatarUrl
                      metadata:(nullable NSDictionary<NSString *, NSString *> *)metadata;

/**
 * Validate that user info contains required fields
 * @return True if valid, false otherwise
 */
- (BOOL)isValid;

@end

NS_ASSUME_NONNULL_END 