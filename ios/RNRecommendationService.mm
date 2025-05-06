#import "RNRecommendationService.h"

@implementation RNRecommendationService

RCT_EXPORT_MODULE()

RCT_EXPORT_METHOD(getInviteRecommendations:(NSInteger)limit
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNRecommendationService: getInviteRecommendations called with limit: %ld", (long)limit);

    // Get the recommendation service from the contact service
    CMRecommendationService *recommendationService = [[CMContactService sharedInstance] recommendationService];
    if (!recommendationService) {
        reject(@"recommendation_error", @"Recommendation service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [recommendationService getSharedContactsByUsersToInviteWithLimit:limit completion:^(NSArray<CMContactRecommendation *> * _Nullable recommendations, NSError * _Nullable error) {
        if (error) {
            reject(@"recommendation_error", error.localizedDescription, error);
            return;
        }

        NSMutableArray *recommendationsArray = [NSMutableArray new];
        for (CMContactRecommendation *recommendation in recommendations) {
            NSDictionary *recommendationDict = [self recommendationToDictionary:recommendation];
            [recommendationsArray addObject:recommendationDict];
        }

        resolve(recommendationsArray);
    }];
}

RCT_EXPORT_METHOD(getContactsUsingApp:(NSInteger)limit
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNRecommendationService: getContactsUsingApp called with limit: %ld", (long)limit);

    CMRecommendationService *recommendationService = [[CMContactService sharedInstance] recommendationService];
    if (!recommendationService) {
        reject(@"recommendation_error", @"Recommendation service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [recommendationService getContactsUsingAppWithLimit:limit completion:^(NSArray<CMLocalCanonicalContact *> * _Nullable contacts, NSError * _Nullable error) {
        if (error) {
            reject(@"recommendation_error", error.localizedDescription, error);
            return;
        }

        NSMutableArray *contactsArray = [NSMutableArray new];
        for (CMLocalCanonicalContact *localContact in contacts) {
            NSDictionary *contactDict = [self localCanonicalContactToDictionary:localContact];
            [contactsArray addObject:contactDict];
        }

        resolve(contactsArray);
    }];
}

RCT_EXPORT_METHOD(getUsersYouMightKnow:(NSInteger)limit
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNRecommendationService: getUsersYouMightKnow called with limit: %ld", (long)limit);

    CMRecommendationService *recommendationService = [[CMContactService sharedInstance] recommendationService];
    if (!recommendationService) {
        reject(@"recommendation_error", @"Recommendation service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [recommendationService getUsersYouMightKnowWithLimit:limit completion:^(NSArray<CMCanonicalContact *> * _Nullable contacts, NSError * _Nullable error) {
        if (error) {
            reject(@"recommendation_error", error.localizedDescription, error);
            return;
        }

        NSMutableArray *contactsArray = [NSMutableArray new];
        for (CMCanonicalContact *contact in contacts) {
            NSDictionary *contactDict = [self canonicalContactToDictionary:contact];
            [contactsArray addObject:contactDict];
        }

        resolve(contactsArray);
    }];
}

#pragma mark - Helper methods

// Helper to convert CMContactRecommendation to NSDictionary
- (NSDictionary *)recommendationToDictionary:(CMContactRecommendation *)recommendation {
    if (!recommendation) {
        return nil;
    }

    NSMutableDictionary *dict = [NSMutableDictionary dictionary];

    // Add basic properties
    dict[@"score"] = @(recommendation.score);
    dict[@"reason"] = recommendation.reason ?: @"";
    dict[@"type"] = @(recommendation.type);
    dict[@"organizationUserId"] = recommendation.organizationUserId ?: @"";

    // Add the contact
    CMContact *contact = recommendation.contact;
    if (contact) {
        NSDictionary *contactDict = [self contactToDictionary:contact];
        dict[@"contact"] = contactDict;
    }

    return dict;
}

// Helper to convert CMContact to NSDictionary (reused from RNContactService)
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
    dict[@"phoneNumbers"] = [self phoneNumbersToDictionary:contact.phoneNumbers];
    dict[@"emailAddresses"] = [self emailAddressesToDictionary:contact.emailAddresses];

    // Simplified implementation with just the key properties
    return dict;
}

// Helper to convert CMCanonicalContact to NSDictionary
- (NSDictionary *)canonicalContactToDictionary:(CMCanonicalContact *)contact {
    if (!contact) {
        return nil;
    }

    NSMutableDictionary *dict = [NSMutableDictionary dictionary];

    dict[@"identifier"] = contact.identifier;
    dict[@"organizationId"] = contact.organizationId ?: @"";
    dict[@"organizationUserId"] = contact.organizationUserId;
    dict[@"email"] = contact.email ?: @"";
    dict[@"phone"] = contact.phone ?: @"";
    dict[@"fullName"] = contact.fullName;
    dict[@"avatarUrl"] = contact.avatarUrl ?: @"";
    dict[@"isActive"] = @(contact.isActive);

    if (contact.createdAt) {
        dict[@"createdAt"] = @([contact.createdAt timeIntervalSince1970] * 1000);
    }

    if (contact.updatedAt) {
        dict[@"updatedAt"] = @([contact.updatedAt timeIntervalSince1970] * 1000);
    }

    dict[@"contactMetadata"] = contact.contactMetadata ?: @{};

    return dict;
}

// Helper to convert phone numbers to array of dictionaries
- (NSArray *)phoneNumbersToDictionary:(NSArray<CMContactPhoneNumber *> *)phoneNumbers {
    NSMutableArray *result = [NSMutableArray array];

    for (CMContactPhoneNumber *phoneNumber in phoneNumbers) {
        [result addObject:@{
            @"contactId": phoneNumber.contactId ?: @"",
            @"value": phoneNumber.value ?: @"",
            @"type": phoneNumber.type ?: @"",
            @"emoji": phoneNumber.emoji ?: @""
        }];
    }

    return result;
}

// Helper to convert email addresses to array of dictionaries
- (NSArray *)emailAddressesToDictionary:(NSArray<CMContactEmailAddress *> *)emailAddresses {
    NSMutableArray *result = [NSMutableArray array];

    for (CMContactEmailAddress *emailAddress in emailAddresses) {
        [result addObject:@{
            @"contactId": emailAddress.contactId ?: @"",
            @"value": emailAddress.value ?: @"",
            @"type": emailAddress.type ?: @"",
            @"emoji": emailAddress.emoji ?: @""
        }];
    }

    return result;
}

// Helper to convert CMLocalCanonicalContact to NSDictionary
- (NSDictionary *)localCanonicalContactToDictionary:(CMLocalCanonicalContact *)localContact {
    if (!localContact) {
        return nil;
    }

    NSMutableDictionary *dict = [NSMutableDictionary dictionary];

    // Add the contactId and sourceContactId
    dict[@"contactId"] = localContact.contactId ?: @"";
    dict[@"sourceContactId"] = localContact.sourceContactId ?: @"";

    // Add the canonical contact
    if (localContact.canonicalContact) {
        dict[@"canonicalContact"] = [self canonicalContactToDictionary:localContact.canonicalContact];
    }

    // Add the local contact if available
    if (localContact.contact) {
        dict[@"contact"] = [self contactToDictionary:localContact.contact];
    } else {
        dict[@"contact"] = [NSNull null];
    }

    return dict;
}

@end
