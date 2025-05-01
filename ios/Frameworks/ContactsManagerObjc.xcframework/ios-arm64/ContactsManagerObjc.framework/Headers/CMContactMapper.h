//
//  CMContactMapper.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>
#import <Contacts/Contacts.h>
#import <ContactsManagerObjc/CMContact.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * CMContactMapper class for mapping between CNContact and CMContact objects
 */
@interface CMContactMapper : NSObject

/**
 * Convert a CNContact to a CMContact
 * @param cnContact The CNContact to convert
 * @return A CMContact object with data from the CNContact
 */
+ (CMContact *)contactFromCNContact:(CNContact *)cnContact;

/**
 * Convert a CMContact to a mutable CNContact
 * @param contact The CMContact to convert
 * @return A mutable CNContact object with data from the CMContact
 */
+ (CNMutableContact *)cnContactFromContact:(CMContact *)contact;

/**
 * Get the keys to fetch when querying contacts
 * @param includeNotes Whether to include notes in the fetch
 * @return An array of CNKeyDescriptor objects
 */
+ (NSArray<id<CNKeyDescriptor>> *)keysToFetch:(BOOL)includeNotes;

/**
 * Get the keys to fetch for the specified field types
 * @param fieldTypes Array of field types to fetch
 * @return An array of CNKeyDescriptor objects
 */
+ (NSArray<id<CNKeyDescriptor>> *)keysToFetchForFieldTypes:(NSArray<NSNumber *> *)fieldTypes;

@end

NS_ASSUME_NONNULL_END 
