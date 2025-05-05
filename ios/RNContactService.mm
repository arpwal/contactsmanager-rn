#import "RNContactService.h"

@implementation RNContactService

RCT_EXPORT_MODULE()

RCT_EXPORT_METHOD(initialize:(NSString *)apiKey
                  token:(NSString *)token
                  userInfo:(NSDictionary *)userInfoDict
                  options:(NSDictionary *)optionsDict
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: initialize called");

    // Create CMUserInfo from dictionary
    Class userInfoClass = NSClassFromString(@"CMUserInfo");
    if (!userInfoClass) {
        reject(@"init_error", @"CMUserInfo class not found", nil);
        return;
    }

    NSString *userId = userInfoDict[@"userId"];
    NSString *fullName = userInfoDict[@"fullName"];
    NSString *email = userInfoDict[@"email"];
    NSString *phone = userInfoDict[@"phone"];
    NSString *avatarUrl = userInfoDict[@"avatarUrl"];
    NSDictionary *metadata = userInfoDict[@"metadata"];

    if (!userId) {
        reject(@"init_error", @"userId is required", nil);
        return;
    }

    CMUserInfo *userInfo = [[userInfoClass alloc] initWithUserId:userId
                                                        fullName:fullName
                                                           email:email
                                                           phone:phone
                                                       avatarUrl:avatarUrl
                                                        metadata:metadata];

    // Create options object if provided
    CMContactsManagerOptions *options = nil;
    if (optionsDict) {
        Class optionsClass = NSClassFromString(@"CMContactsManagerOptions");
        if (optionsClass) {
            options = [[optionsClass alloc] init];
            // Set options properties as needed
        }
    }

    // Call the CMContactService method
    [[CMContactService sharedInstance] initializeWithAPIKey:apiKey
                                                      token:token
                                                   userInfo:userInfo
                                                    options:options
                                                 completion:^(BOOL success, NSError * _Nullable error) {
        if (error) {
            reject(@"init_error", error.localizedDescription, error);
        } else {
            resolve(@{@"success": @(success)});
        }
    }];
}

RCT_EXPORT_METHOD(isInitialized:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: isInitialized called");

    BOOL isInitialized = [[CMContactService sharedInstance] isInitialized];
    resolve(@(isInitialized));
}

RCT_EXPORT_METHOD(currentState:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: currentState called");

    NSString *state = [[CMContactService sharedInstance] currentState];
    resolve(state);
}

RCT_EXPORT_METHOD(reset:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: reset called");

    [[CMContactService sharedInstance] resetWithCompletion:^(BOOL success, NSError * _Nullable error) {
        if (error) {
            reject(@"reset_error", error.localizedDescription, error);
        } else {
            resolve(@{@"success": @(success)});
        }
    }];
}

RCT_EXPORT_METHOD(requestContactsAccess:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: requestContactsAccess called");

    [[CMContactService sharedInstance] requestContactsAccessWithCompletion:^(BOOL granted) {
        resolve(@{@"granted": @(granted)});
    }];
}

RCT_EXPORT_METHOD(contactsAccessStatus:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: contactsAccessStatus called");

    NSInteger status = [[CMContactService sharedInstance] contactsAccessStatus];
    resolve(@(status));
}

RCT_EXPORT_METHOD(fetchContacts:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: fetchContacts called");

    [[CMContactService sharedInstance] fetchContactsWithCompletion:^(NSArray<CMContact *> * _Nullable contacts, NSError * _Nullable error) {
        if (error) {
            reject(@"fetch_error", error.localizedDescription, error);
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

RCT_EXPORT_METHOD(fetchContactsWithFieldType:(NSInteger)fieldType
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: fetchContactsWithFieldType called with fieldType: %ld", (long)fieldType);

    [[CMContactService sharedInstance] fetchContactsWithFieldType:fieldType completion:^(NSArray<CMContact *> * _Nullable contacts, NSError * _Nullable error) {
        if (error) {
            reject(@"fetch_error", error.localizedDescription, error);
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

RCT_EXPORT_METHOD(fetchContactsWithBatch:(NSInteger)batchSize
                  batchIndex:(NSInteger)batchIndex
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: fetchContactsWithBatch called with batchSize: %ld, batchIndex: %ld", (long)batchSize, (long)batchIndex);

    [[CMContactService sharedInstance] fetchContactsWithBatchSize:batchSize batchIndex:batchIndex completion:^(NSArray<CMContact *> * _Nullable contacts, NSError * _Nullable error) {
        if (error) {
            reject(@"fetch_error", error.localizedDescription, error);
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

RCT_EXPORT_METHOD(fetchContactWithId:(NSString *)identifier
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: fetchContactWithId called with ID: %@", identifier);

    [[CMContactService sharedInstance] fetchContactWithIdentifier:identifier completion:^(CMContact * _Nullable contact, NSError * _Nullable error) {
        if (error) {
            reject(@"fetch_error", error.localizedDescription, error);
            return;
        }

        if (!contact) {
            reject(@"not_found", @"Contact not found", nil);
            return;
        }

        // Convert CMContact to dictionary
        NSDictionary *contactDict = [self contactToDictionary:contact];
        resolve(contactDict);
    }];
}

RCT_EXPORT_METHOD(getContactsCount:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: getContactsCount called");

    [[CMContactService sharedInstance] getContactsCountWithCompletion:^(NSInteger count, NSError * _Nullable error) {
        if (error) {
            reject(@"count_error", error.localizedDescription, error);
        } else {
            resolve(@(count));
        }
    }];
}

RCT_EXPORT_METHOD(enableBackgroundSync:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: enableBackgroundSync called");

    [[CMContactService sharedInstance] enableBackgroundSync];
    resolve(@(YES));
}

RCT_EXPORT_METHOD(scheduleBackgroundSyncTask:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: scheduleBackgroundSyncTask called");

    [[CMContactService sharedInstance] scheduleBackgroundSyncTask];
    resolve(@(YES));
}

RCT_EXPORT_METHOD(checkHealth:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: checkHealth called");

    [CMContactService checkHealthWithCompletion:^(BOOL healthy) {
        resolve(@{@"healthy": @(healthy)});
    }];
}

RCT_EXPORT_METHOD(hasContactChanged:(NSDictionary *)contactDict
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: hasContactChanged called");

    // Convert dictionary to CMContact
    CMContact *contact = [self dictionaryToContact:contactDict];
    if (!contact) {
        reject(@"invalid_contact", @"Failed to convert dictionary to contact", nil);
        return;
    }

    BOOL hasChanged = [[CMContactService sharedInstance] hasContactChanged:contact];
    resolve(@(hasChanged));
}

RCT_EXPORT_METHOD(getContactsForSync:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: getContactsForSync called");

    [[CMContactService sharedInstance] getContactsForSyncWithCompletion:^(NSArray<CMContact *> * _Nullable contacts, NSError * _Nullable error) {
        if (error) {
            reject(@"sync_error", error.localizedDescription, error);
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

RCT_EXPORT_METHOD(startSync:(NSString *)sourceId
                  userId:(NSString *)userId
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: startSync called with sourceId: %@, userId: %@", sourceId, userId);

    [[CMContactService sharedInstance] startSyncWithSourceId:sourceId userId:userId completion:^(NSInteger syncedCount, NSError * _Nullable error) {
        if (error) {
            reject(@"sync_error", error.localizedDescription, error);
        } else {
            resolve(@{@"syncedCount": @(syncedCount)});
        }
    }];
}

RCT_EXPORT_METHOD(cancelSync:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactService: cancelSync called");

    [[CMContactService sharedInstance] cancelSync];
    resolve(@(YES));
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
    dict[@"bio"] = contact.bio ?: @"";
    dict[@"location"] = contact.location ?: @"";
    dict[@"contactSection"] = contact.contactSection ?: @"";
    dict[@"matchString"] = contact.matchString ?: @"";
    dict[@"parentContactId"] = contact.parentContactId ?: @"";
    dict[@"sourceId"] = contact.sourceId ?: @"";

    // Add numeric properties
    dict[@"contactType"] = @(contact.contactType);
    dict[@"isDeleted"] = @(contact.isDeleted);
    dict[@"dirtyTime"] = @(contact.dirtyTime);
    dict[@"lastSyncedAt"] = @(contact.lastSyncedAt);
    dict[@"createdAt"] = @(contact.createdAt);

    // Image data
    dict[@"imageUrl"] = contact.imageUrl ?: @"";
    dict[@"imageDataAvailable"] = @(contact.imageDataAvailable);

    if (contact.imageData) {
        dict[@"imageData"] = [contact.imageData base64EncodedStringWithOptions:0];
    }

    if (contact.thumbnailImageData) {
        dict[@"thumbnailImageData"] = [contact.thumbnailImageData base64EncodedStringWithOptions:0];
    }

    // Add birthday if available
    if (contact.birthday) {
        dict[@"birthday"] = @([contact.birthday timeIntervalSince1970] * 1000);
    }

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

    // Simplified, would need to implement for all contact properties
    dict[@"addresses"] = @[];
    dict[@"dates"] = @[];
    dict[@"urlAddresses"] = @[];
    dict[@"socialProfiles"] = @[];
    dict[@"relations"] = @[];
    dict[@"instantMessageAddresses"] = @[];
    dict[@"interests"] = @[];
    dict[@"avatars"] = @[];

    return dict;
}

// Helper to convert NSDictionary to CMContact
- (CMContact *)dictionaryToContact:(NSDictionary *)dict {
    if (!dict) {
        return nil;
    }

    NSString *identifier = dict[@"identifier"];
    if (!identifier) {
        return nil;
    }

    CMContact *contact = [[CMContact alloc] initWithIdentifier:identifier];

    // Set basic properties
    contact.displayName = dict[@"displayName"];
    contact.givenName = dict[@"givenName"];
    contact.familyName = dict[@"familyName"];
    contact.middleName = dict[@"middleName"];
    contact.namePrefix = dict[@"namePrefix"];
    contact.nameSuffix = dict[@"nameSuffix"];
    contact.nickname = dict[@"nickname"];
    contact.organizationName = dict[@"organizationName"];
    contact.departmentName = dict[@"departmentName"];
    contact.jobTitle = dict[@"jobTitle"];
    contact.notes = dict[@"notes"];
    contact.bio = dict[@"bio"];
    contact.location = dict[@"location"];
    contact.contactSection = dict[@"contactSection"];
    contact.matchString = dict[@"matchString"];
    contact.parentContactId = dict[@"parentContactId"];
    contact.sourceId = dict[@"sourceId"];

    // Handle numeric properties
    contact.contactType = [dict[@"contactType"] integerValue];
    contact.isDeleted = [dict[@"isDeleted"] boolValue];
    contact.dirtyTime = [dict[@"dirtyTime"] doubleValue];
    contact.lastSyncedAt = [dict[@"lastSyncedAt"] doubleValue];
    contact.createdAt = [dict[@"createdAt"] doubleValue];

    // Simplified implementation, would need to convert all properties

    return contact;
}

@end
