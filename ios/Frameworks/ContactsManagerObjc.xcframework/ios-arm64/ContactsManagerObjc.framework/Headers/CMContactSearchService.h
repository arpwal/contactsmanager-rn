//
//  CMContactSearchService.h
//  ContactsManagerObjc
//
//  Created by ContactsManager on 4/20/25.
//

#import <Foundation/Foundation.h>
#import <Contacts/Contacts.h>

@class CMContact;
@class CMContactService;

NS_ASSUME_NONNULL_BEGIN

/**
 * Enum representing fields that can be searched
 */
typedef NS_OPTIONS(NSUInteger, CMSearchFieldType) {
    CMSearchFieldTypeName         = 1 << 0,
    CMSearchFieldTypeEmail        = 1 << 1,
    CMSearchFieldTypePhone        = 1 << 2,
    CMSearchFieldTypeAddress      = 1 << 3,
    CMSearchFieldTypeOrganization = 1 << 4,
    CMSearchFieldTypeNotes        = 1 << 5,
    CMSearchFieldTypeAll          = 0xFFFFFFFF
};

/**
 * Service responsible for handling contact search operations directly from CNContactStore
 */
@interface CMContactSearchService : NSObject

/**
 * Shared instance for singleton access
 * @note This method is for internal use by CMContactService only.
 *       Use [CMContactService searchService] to get an instance.
 */
+ (instancetype)sharedInstance NS_UNAVAILABLE;

/**
 * Initialize the service
 * @note This method is for internal use by CMContactService only.
 *       Use [CMContactService searchService] to get an instance.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 * Initialize the search service with a contact service
 * @param contactService The contact service instance
 * @note This method is for internal use by CMContactService only.
 *       Use [CMContactService searchService] to get an instance.
 */
- (instancetype)initWithContactService:(CMContactService *)contactService; // Internal method - do not use directly

/**
 * Initialize the service
 * @return YES if initialization was successful, NO otherwise
 */
- (BOOL)initialize;

/**
 * Get the total number of contacts in the device's address book
 * @param error Pointer to an error object that will be set if an error occurs
 * @return Total count of contacts
 */
- (NSInteger)getTotalContactsCountWithError:(NSError **)error;

/**
 * Search contacts using a query string
 * @param query The search query
 * @param searchFields Bitmask of fields to search in (default: all fields)
 * @param offset Starting index for pagination
 * @param limit Maximum number of results to return
 * @param error Pointer to an error object that will be set if an error occurs
 * @return Array of matching contacts
 */
- (NSArray<CMContact *> *)searchContactsWithQuery:(NSString *)query
                                     searchFields:(CMSearchFieldType)searchFields
                                          offset:(NSInteger)offset
                                           limit:(NSInteger)limit
                                           error:(NSError **)error;

/**
 * Performs a quick search that can be used for real-time filtering
 * @param query The search query
 * @param error Pointer to an error object that will be set if an error occurs
 * @return Array of matching contacts
 */
- (NSArray<CMContact *> *)quickSearchWithQuery:(NSString *)query
                                         error:(NSError **)error;

/**
 * Loads all contacts with completion handler
 * @param completion Block to be called when operation completes with contacts or error
 */
- (void)loadContactsWithCompletion:(void (^)(NSArray<CMContact *> * _Nullable contacts, NSError * _Nullable error))completion;

/**
 * Search contacts with pagination
 * @param query The search query
 * @param fieldType The field type to search (default: CMSearchFieldTypeAll)
 * @param offset The offset for pagination
 * @param limit The maximum number of results to return
 * @param completion Completion handler with results and total count
 */
- (void)searchContactsWithQuery:(NSString *)query
                      fieldType:(CMSearchFieldType)fieldType
                         offset:(NSInteger)offset
                          limit:(NSInteger)limit
                     completion:(void (^)(NSArray<CMContact *> *contacts, NSInteger totalCount, NSError *_Nullable error))completion;

/**
 * Quick search for real-time filtering
 * @param query The search query
 * @param completion Completion handler with results
 */
- (void)quickSearchWithQuery:(NSString *)query
                  completion:(void (^)(NSArray<CMContact *> *contacts, NSError *_Nullable error))completion;

/**
 * Get the total number of contacts
 * @param completion Completion handler with count
 */
- (void)getContactsCountWithCompletion:(void (^)(NSInteger count, NSError *_Nullable error))completion;


@end

NS_ASSUME_NONNULL_END 
