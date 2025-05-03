//
//  CMContactExtensions.h
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

NS_ASSUME_NONNULL_BEGIN

/**
 * CMContact extension for comparison and matching functionality
 */
@interface CMContact (Extensions)

/**
 * Compare phone number arrays for equality
 * @param phoneNumbers1 First array of phone numbers
 * @param phoneNumbers2 Second array of phone numbers
 * @return YES if the arrays are equal, NO otherwise
 */
+ (BOOL)arePhoneNumbersEqual:(NSArray<CMContactPhoneNumber *> *)phoneNumbers1 withPhoneNumbers:(NSArray<CMContactPhoneNumber *> *)phoneNumbers2;

/**
 * Compare email address arrays for equality
 * @param emailAddresses1 First array of email addresses
 * @param emailAddresses2 Second array of email addresses
 * @return YES if the arrays are equal, NO otherwise
 */
+ (BOOL)areEmailAddressesEqual:(NSArray<CMContactEmailAddress *> *)emailAddresses1 withEmailAddresses:(NSArray<CMContactEmailAddress *> *)emailAddresses2;

/**
 * Compare URL address arrays for equality
 * @param urlAddresses1 First array of URL addresses
 * @param urlAddresses2 Second array of URL addresses
 * @return YES if the arrays are equal, NO otherwise
 */
+ (BOOL)areURLAddressesEqual:(NSArray<CMContactURL *> *)urlAddresses1 withURLAddresses:(NSArray<CMContactURL *> *)urlAddresses2;

/**
 * Compare address arrays for equality
 * @param addresses1 First array of addresses
 * @param addresses2 Second array of addresses
 * @return YES if the arrays are equal, NO otherwise
 */
+ (BOOL)areAddressesEqual:(NSArray<CMContactAddress *> *)addresses1 withAddresses:(NSArray<CMContactAddress *> *)addresses2;

/**
 * Compare social profile arrays for equality
 * @param socialProfiles1 First array of social profiles
 * @param socialProfiles2 Second array of social profiles
 * @return YES if the arrays are equal, NO otherwise
 */
+ (BOOL)areSocialProfilesEqual:(NSArray<CMContactSocialProfile *> *)socialProfiles1 withSocialProfiles:(NSArray<CMContactSocialProfile *> *)socialProfiles2;

/**
 * Compare relation arrays for equality
 * @param relations1 First array of relations
 * @param relations2 Second array of relations
 * @return YES if the arrays are equal, NO otherwise
 */
+ (BOOL)areRelationsEqual:(NSArray<CMContactRelation *> *)relations1 withRelations:(NSArray<CMContactRelation *> *)relations2;

/**
 * Compare instant message arrays for equality
 * @param imAddresses1 First array of instant message addresses
 * @param imAddresses2 Second array of instant message addresses
 * @return YES if the arrays are equal, NO otherwise
 */
+ (BOOL)areInstantMessagesEqual:(NSArray<CMContactInstantMessage *> *)imAddresses1 withInstantMessages:(NSArray<CMContactInstantMessage *> *)imAddresses2;

/**
 * Compare date arrays for equality
 * @param dates1 First array of dates
 * @param dates2 Second array of dates
 * @return YES if the arrays are equal, NO otherwise
 */
+ (BOOL)areDatesEqual:(NSArray<CMContactDate *> *)dates1 withDates:(NSArray<CMContactDate *> *)dates2;

/**
 * Compare string arrays for equality
 * @param array1 First array of strings
 * @param array2 Second array of strings
 * @return YES if the arrays are equal, NO otherwise
 */
+ (BOOL)areArraysEqual:(NSArray<NSString *> *)array1 withArray:(NSArray<NSString *> *)array2;

@end

NS_ASSUME_NONNULL_END 
