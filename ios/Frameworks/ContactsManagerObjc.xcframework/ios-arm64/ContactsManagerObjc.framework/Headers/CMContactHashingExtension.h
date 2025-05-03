//
//  CMContactHashingExtension.h
//  ContactsManagerObjc
//
//  Created for ContactsManager
//

#import <Foundation/Foundation.h>

#if __has_include(<ContactsManagerObjc/CMContact.h>)
#import <ContactsManagerObjc/CMContact.h>
#elif __has_include("CMContact.h")
#import "CMContact.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 * Extension to add hashing functionality to CMContact
 */
@interface CMContact (Hashing)

/**
 * Generate a hash string representing the current state of the contact
 * @return A string hash that can be used to detect changes in the contact
 */
- (NSString *)generateContactHash;

@end

NS_ASSUME_NONNULL_END 