#import "RNContactSearchService.h"

@implementation RNContactSearchService

RCT_EXPORT_MODULE()

RCT_EXPORT_METHOD(searchContacts:(NSString *)query
                  fieldType:(NSInteger)fieldType
                  offset:(NSInteger)offset
                  limit:(NSInteger)limit
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactSearchService: searchContacts called with query: %@", query);

    // Get the search service from the contact service
    CMContactSearchService *searchService = [[CMContactService sharedInstance] searchService];
    if (!searchService) {
        reject(@"search_error", @"Search service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [searchService searchContactsWithQuery:query
                                fieldType:fieldType
                                   offset:offset
                                    limit:limit
                               completion:^(NSArray<CMContact *> *contacts, NSInteger totalCount, NSError *_Nullable error) {
        if (error) {
            reject(@"search_error", error.localizedDescription, error);
            return;
        }

        NSMutableArray *contactsArray = [NSMutableArray new];
        for (CMContact *contact in contacts) {
            // Convert CMContact to dictionary
            NSDictionary *contactDict = [self contactToDictionary:contact];
            [contactsArray addObject:contactDict];
        }

        NSDictionary *result = @{
            @"contacts": contactsArray,
            @"totalCount": @(totalCount)
        };

        resolve(result);
    }];
}

RCT_EXPORT_METHOD(quickSearch:(NSString *)query
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactSearchService: quickSearch called with query: %@", query);

    CMContactSearchService *searchService = [[CMContactService sharedInstance] searchService];
    if (!searchService) {
        reject(@"search_error", @"Search service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [searchService quickSearchWithQuery:query completion:^(NSArray<CMContact *> *contacts, NSError *_Nullable error) {
        if (error) {
            reject(@"search_error", error.localizedDescription, error);
            return;
        }

        NSMutableArray *contactsArray = [NSMutableArray new];
        for (CMContact *contact in contacts) {
            // Convert CMContact to dictionary
            NSDictionary *contactDict = [self contactToDictionary:contact];
            [contactsArray addObject:contactDict];
        }

        resolve(contactsArray);
    }];
}

RCT_EXPORT_METHOD(getContactsCount:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactSearchService: getContactsCount called");

    CMContactSearchService *searchService = [[CMContactService sharedInstance] searchService];
    if (!searchService) {
        reject(@"search_error", @"Search service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [searchService getContactsCountWithCompletion:^(NSInteger count, NSError *_Nullable error) {
        if (error) {
            reject(@"count_error", error.localizedDescription, error);
        } else {
            resolve(@(count));
        }
    }];
}

#pragma mark - Helper methods

// Helper to convert CMContact to NSDictionary
- (NSDictionary *)contactToDictionary:(CMContact *)contact {
    if (!contact) {
        return nil;
    }

    // Create a base dictionary with properties
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];

    // Add basic properties
    dict[@"identifier"] = contact.identifier;
    dict[@"displayName"] = contact.displayName ?: @"";
    dict[@"givenName"] = contact.givenName ?: @"";
    dict[@"familyName"] = contact.familyName ?: @"";
    dict[@"middleName"] = contact.middleName ?: @"";
    dict[@"namePrefix"] = contact.namePrefix ?: @"";
    dict[@"nameSuffix"] = contact.nameSuffix ?: @"";
    dict[@"nickname"] = contact.nickname ?: @"";
    dict[@"organizationName"] = contact.organizationName ?: @"";
    dict[@"departmentName"] = contact.departmentName ?: @"";
    dict[@"jobTitle"] = contact.jobTitle ?: @"";
    dict[@"notes"] = contact.notes ?: @"";

    // Add arrays for collections (simplified for brevity)
    NSMutableArray *phoneNumbers = [NSMutableArray array];
    for (CMContactPhoneNumber *phone in contact.phoneNumbers) {
        [phoneNumbers addObject:@{
            @"contactId": phone.contactId ?: @"",
            @"value": phone.value ?: @"",
            @"type": phone.type ?: @"",
            @"emoji": phone.emoji ?: @""
        }];
    }
    dict[@"phoneNumbers"] = phoneNumbers;

    NSMutableArray *emailAddresses = [NSMutableArray array];
    for (CMContactEmailAddress *email in contact.emailAddresses) {
        [emailAddresses addObject:@{
            @"contactId": email.contactId ?: @"",
            @"value": email.value ?: @"",
            @"type": email.type ?: @"",
            @"emoji": email.emoji ?: @""
        }];
    }
    dict[@"emailAddresses"] = emailAddresses;

    return dict;
}

@end
