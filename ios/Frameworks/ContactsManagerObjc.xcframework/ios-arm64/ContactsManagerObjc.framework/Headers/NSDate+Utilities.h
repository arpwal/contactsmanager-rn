//
//  NSDate+Utilities.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Category adding utility methods to NSDate
 */
@interface NSDate (Utilities)

/**
 * Create a date from an ISO 8601 string
 * @param string The ISO 8601 formatted string
 * @return A date object, or nil if the string could not be parsed
 */
+ (nullable NSDate *)dateFromISOString:(nullable NSString *)string;

/**
 * Convert a date to an ISO 8601 string
 * @return An ISO 8601 formatted string representation of the date
 */
- (NSString *)toISOString;

@end

NS_ASSUME_NONNULL_END 