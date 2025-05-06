#import "RNSocialService.h"

@implementation RNSocialService

RCT_EXPORT_MODULE()

#pragma mark - Follow Methods

RCT_EXPORT_METHOD(followUser:(NSString *)userId
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: followUser called with userId: %@", userId);

    // Get the social service from the contact service
    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [socialService followUser:userId completion:^(CMFollowActionResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            reject(@"follow_error", error.localizedDescription, error);
            return;
        }

        NSDictionary *responseDict = [self followActionResponseToDictionary:response];
        resolve(responseDict);
    }];
}

RCT_EXPORT_METHOD(unfollowUser:(NSString *)userId
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: unfollowUser called with userId: %@", userId);

    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [socialService unfollowUser:userId completion:^(CMFollowActionResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            reject(@"unfollow_error", error.localizedDescription, error);
            return;
        }

        NSDictionary *responseDict = [self followActionResponseToDictionary:response];
        resolve(responseDict);
    }];
}

RCT_EXPORT_METHOD(isFollowingUser:(NSString *)userId
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: isFollowingUser called with userId: %@", userId);

    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [socialService isFollowingUser:userId completion:^(CMFollowStatusResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            reject(@"follow_status_error", error.localizedDescription, error);
            return;
        }

        resolve(@{@"isFollowing": @(response.isFollowing)});
    }];
}

RCT_EXPORT_METHOD(getFollowers:(NSString *)userId
                  skip:(NSInteger)skip
                  limit:(NSInteger)limit
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: getFollowers called with userId: %@, skip: %ld, limit: %ld", userId, (long)skip, (long)limit);

    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [socialService getFollowersWithUserId:userId.length > 0 ? userId : nil skip:skip limit:limit completion:^(CMPaginatedFollowList * _Nullable list, NSError * _Nullable error) {
        if (error) {
            reject(@"followers_error", error.localizedDescription, error);
            return;
        }

        NSDictionary *responseDict = [self paginatedFollowListToDictionary:list];
        resolve(responseDict);
    }];
}

RCT_EXPORT_METHOD(getFollowing:(NSString *)userId
                  skip:(NSInteger)skip
                  limit:(NSInteger)limit
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: getFollowing called with userId: %@, skip: %ld, limit: %ld", userId, (long)skip, (long)limit);

    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [socialService getFollowingWithUserId:userId.length > 0 ? userId : nil skip:skip limit:limit completion:^(CMPaginatedFollowList * _Nullable list, NSError * _Nullable error) {
        if (error) {
            reject(@"following_error", error.localizedDescription, error);
            return;
        }

        NSDictionary *responseDict = [self paginatedFollowListToDictionary:list];
        resolve(responseDict);
    }];
}

RCT_EXPORT_METHOD(getMutualFollows:(NSInteger)skip
                  limit:(NSInteger)limit
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: getMutualFollows called with skip: %ld, limit: %ld", (long)skip, (long)limit);

    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [socialService getMutualFollowsWithSkip:skip limit:limit completion:^(CMPaginatedMutualFollowers * _Nullable list, NSError * _Nullable error) {
        if (error) {
            reject(@"mutual_follows_error", error.localizedDescription, error);
            return;
        }

        NSDictionary *responseDict = [self paginatedMutualFollowersToDictionary:list];
        resolve(responseDict);
    }];
}

#pragma mark - Event Methods

RCT_EXPORT_METHOD(createEvent:(NSDictionary *)eventData
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: createEvent called");

    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    // Convert eventData dictionary to CMCreateEventRequest
    CMCreateEventRequest *request = [self dictionaryToCreateEventRequest:eventData];
    if (!request) {
        reject(@"event_error", @"Invalid event data format", nil);
        return;
    }

    [socialService createEvent:request completion:^(CMEventActionResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            reject(@"event_error", error.localizedDescription, error);
            return;
        }

        NSDictionary *responseDict = [self eventActionResponseToDictionary:response];
        resolve(responseDict);
    }];
}

RCT_EXPORT_METHOD(getEvent:(NSString *)eventId
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: getEvent called with eventId: %@", eventId);

    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [socialService getEvent:eventId completion:^(CMSocialEvent * _Nullable event, NSError * _Nullable error) {
        if (error) {
            reject(@"event_error", error.localizedDescription, error);
            return;
        }

        if (!event) {
            reject(@"event_error", @"Event not found", nil);
            return;
        }

        NSDictionary *eventDict = [self socialEventToDictionary:event];
        resolve(eventDict);
    }];
}

RCT_EXPORT_METHOD(updateEvent:(NSString *)eventId
                  eventData:(NSDictionary *)eventData
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: updateEvent called with eventId: %@", eventId);

    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    // Convert eventData dictionary to CMUpdateEventRequest
    CMUpdateEventRequest *request = [self dictionaryToUpdateEventRequest:eventData];
    if (!request) {
        reject(@"event_error", @"Invalid event data format", nil);
        return;
    }

    [socialService updateEvent:eventId eventData:request completion:^(CMEventActionResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            reject(@"event_error", error.localizedDescription, error);
            return;
        }

        NSDictionary *responseDict = [self eventActionResponseToDictionary:response];
        resolve(responseDict);
    }];
}

RCT_EXPORT_METHOD(deleteEvent:(NSString *)eventId
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: deleteEvent called with eventId: %@", eventId);

    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [socialService deleteEvent:eventId completion:^(CMEventActionResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            reject(@"event_error", error.localizedDescription, error);
            return;
        }

        NSDictionary *responseDict = [self eventActionResponseToDictionary:response];
        resolve(responseDict);
    }];
}

RCT_EXPORT_METHOD(getUserEvents:(NSString *)userId
                  skip:(NSInteger)skip
                  limit:(NSInteger)limit
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: getUserEvents called with userId: %@, skip: %ld, limit: %ld", userId, (long)skip, (long)limit);

    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [socialService getUserEventsWithUserId:userId.length > 0 ? userId : nil skip:skip limit:limit completion:^(CMPaginatedEventList * _Nullable list, NSError * _Nullable error) {
        if (error) {
            reject(@"event_error", error.localizedDescription, error);
            return;
        }

        NSDictionary *responseDict = [self paginatedEventListToDictionary:list];
        resolve(responseDict);
    }];
}

RCT_EXPORT_METHOD(getFeed:(NSInteger)skip
                  limit:(NSInteger)limit
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: getFeed called with skip: %ld, limit: %ld", (long)skip, (long)limit);

    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [socialService getFeedWithSkip:skip limit:limit completion:^(CMPaginatedEventList * _Nullable list, NSError * _Nullable error) {
        if (error) {
            reject(@"feed_error", error.localizedDescription, error);
            return;
        }

        NSDictionary *responseDict = [self paginatedEventListToDictionary:list];
        resolve(responseDict);
    }];
}

RCT_EXPORT_METHOD(getUpcomingEvents:(NSInteger)skip
                  limit:(NSInteger)limit
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: getUpcomingEvents called with skip: %ld, limit: %ld", (long)skip, (long)limit);

    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [socialService getUpcomingEventsWithSkip:skip limit:limit completion:^(CMPaginatedEventList * _Nullable list, NSError * _Nullable error) {
        if (error) {
            reject(@"upcoming_events_error", error.localizedDescription, error);
            return;
        }

        NSDictionary *responseDict = [self paginatedEventListToDictionary:list];
        resolve(responseDict);
    }];
}

RCT_EXPORT_METHOD(getForYouFeed:(NSInteger)skip
                  limit:(NSInteger)limit
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNSocialService: getForYouFeed called with skip: %ld, limit: %ld", (long)skip, (long)limit);

    CMSocialService *socialService = [[CMContactService sharedInstance] socialService];
    if (!socialService) {
        reject(@"social_error", @"Social service not available. Make sure ContactService is initialized.", nil);
        return;
    }

    [socialService getForYouFeedWithSkip:skip limit:limit completion:^(CMPaginatedEventList * _Nullable list, NSError * _Nullable error) {
        if (error) {
            reject(@"for_you_feed_error", error.localizedDescription, error);
            return;
        }

        NSDictionary *responseDict = [self paginatedEventListToDictionary:list];
        resolve(responseDict);
    }];
}

#pragma mark - Helper methods

// Helper to convert CMFollowActionResponse to NSDictionary
- (NSDictionary *)followActionResponseToDictionary:(CMFollowActionResponse *)response {
    if (!response) {
        return @{};
    }

    return @{
        @"message": response.message ?: @"",
        @"alreadyFollowing": @(response.alreadyFollowing),
        @"wasFollowing": @(response.wasFollowing),
        @"success": @(response.success)
    };
}

// Helper to convert CMPaginatedFollowList to NSDictionary
- (NSDictionary *)paginatedFollowListToDictionary:(CMPaginatedFollowList *)list {
    if (!list) {
        return @{
            @"items": @[],
            @"total": @(0),
            @"skip": @(0),
            @"limit": @(0)
        };
    }

    NSMutableArray *itemsArray = [NSMutableArray array];
    for (CMFollowRelationship *relationship in list.items) {
        NSDictionary *relationshipDict = [self followRelationshipToDictionary:relationship];
        [itemsArray addObject:relationshipDict];
    }

    return @{
        @"items": itemsArray,
        @"total": @(list.total),
        @"skip": @(list.skip),
        @"limit": @(list.limit)
    };
}

// Helper to convert CMFollowRelationship to NSDictionary
- (NSDictionary *)followRelationshipToDictionary:(CMFollowRelationship *)relationship {
    if (!relationship) {
        return @{};
    }

    NSMutableDictionary *dict = [NSMutableDictionary dictionary];

    dict[@"identifier"] = relationship.identifier;
    dict[@"followerId"] = relationship.followerId;
    dict[@"followedId"] = relationship.followedId;
    dict[@"userId"] = relationship.userId;
    dict[@"displayName"] = relationship.displayName;
    dict[@"photoURL"] = relationship.photoURL ?: @"";
    dict[@"username"] = relationship.username ?: @"";
    dict[@"bio"] = relationship.bio ?: @"";
    dict[@"website"] = relationship.website ?: @"";
    dict[@"isFollowing"] = @(relationship.isFollowing);
    dict[@"contactId"] = relationship.contactId ?: @"";

    if (relationship.createdAt) {
        dict[@"createdAt"] = @([relationship.createdAt timeIntervalSince1970] * 1000);
    }

    if (relationship.follower) {
        dict[@"follower"] = [self canonicalContactToDictionary:relationship.follower];
    }

    if (relationship.followed) {
        dict[@"followed"] = [self canonicalContactToDictionary:relationship.followed];
    }

    return dict;
}

// Helper to convert CMPaginatedMutualFollowers to NSDictionary
- (NSDictionary *)paginatedMutualFollowersToDictionary:(CMPaginatedMutualFollowers *)list {
    if (!list) {
        return @{
            @"items": @[],
            @"total": @(0),
            @"skip": @(0),
            @"limit": @(0)
        };
    }

    NSMutableArray *itemsArray = [NSMutableArray array];
    for (CMCanonicalContact *contact in list.items) {
        NSDictionary *contactDict = [self canonicalContactToDictionary:contact];
        [itemsArray addObject:contactDict];
    }

    return @{
        @"items": itemsArray,
        @"total": @(list.total),
        @"skip": @(list.skip),
        @"limit": @(list.limit)
    };
}

// Helper to convert CMCanonicalContact to NSDictionary
- (NSDictionary *)canonicalContactToDictionary:(CMCanonicalContact *)contact {
    if (!contact) {
        return @{};
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

// Helper to convert CMCreateEventRequest parameters from dictionary
- (CMCreateEventRequest *)dictionaryToCreateEventRequest:(NSDictionary *)dict {
    if (!dict) {
        return nil;
    }

    NSString *eventType = dict[@"eventType"];
    NSString *title = dict[@"title"];

    if (!eventType || !title) {
        return nil; // Required fields are missing
    }

    NSString *description = dict[@"description"];
    NSString *location = dict[@"location"];

    // Parse dates
    NSDate *startTime = nil;
    NSDate *endTime = nil;

    if (dict[@"startTime"]) {
        double startTimestamp = [dict[@"startTime"] doubleValue] / 1000.0; // Convert from ms to seconds
        startTime = [NSDate dateWithTimeIntervalSince1970:startTimestamp];
    }

    if (dict[@"endTime"]) {
        double endTimestamp = [dict[@"endTime"] doubleValue] / 1000.0; // Convert from ms to seconds
        endTime = [NSDate dateWithTimeIntervalSince1970:endTimestamp];
    }

    NSDictionary *metadata = dict[@"metadata"];
    BOOL isPublic = [dict[@"isPublic"] boolValue];

    CMCreateEventRequest *request = [[CMCreateEventRequest alloc] initWithEventType:eventType
                                                                             title:title
                                                                       description:description
                                                                          location:location
                                                                         startTime:startTime
                                                                           endTime:endTime
                                                                          metadata:metadata
                                                                          isPublic:isPublic];

    return request;
}

// Helper to convert CMUpdateEventRequest parameters from dictionary
- (CMUpdateEventRequest *)dictionaryToUpdateEventRequest:(NSDictionary *)dict {
    if (!dict) {
        return nil;
    }

    CMUpdateEventRequest *request = [[CMUpdateEventRequest alloc] init];

    // Set properties based on dictionary values
    if (dict[@"title"]) {
        request.title = dict[@"title"];
    }

    if (dict[@"description"]) {
        request.description = dict[@"description"];
    }

    if (dict[@"location"]) {
        request.location = dict[@"location"];
    }

    if (dict[@"startTime"]) {
        double startTimestamp = [dict[@"startTime"] doubleValue] / 1000.0; // Convert from ms to seconds
        request.startTime = [NSDate dateWithTimeIntervalSince1970:startTimestamp];
    }

    if (dict[@"endTime"]) {
        double endTimestamp = [dict[@"endTime"] doubleValue] / 1000.0; // Convert from ms to seconds
        request.endTime = [NSDate dateWithTimeIntervalSince1970:endTimestamp];
    }

    if (dict[@"metadata"]) {
        request.metadata = dict[@"metadata"];
    }

    if (dict[@"isPublic"] != nil) {
        request.isPublic = @([dict[@"isPublic"] boolValue]);
    }

    return request;
}

// Helper to convert CMEventActionResponse to NSDictionary
- (NSDictionary *)eventActionResponseToDictionary:(CMEventActionResponse *)response {
    if (!response) {
        return @{};
    }

    return @{
        @"message": response.message ?: @"",
        @"eventId": response.eventId ?: @"",
        @"created": @(response.created),
        @"updated": @(response.updated),
        @"deleted": @(response.deleted),
        @"success": @(response.success)
    };
}

// Helper to convert CMSocialEvent to NSDictionary
- (NSDictionary *)socialEventToDictionary:(CMSocialEvent *)event {
    if (!event) {
        return @{};
    }

    NSMutableDictionary *dict = [NSMutableDictionary dictionary];

    dict[@"eventId"] = event.eventId;
    dict[@"organizationId"] = event.organizationId;
    dict[@"canonicalContactId"] = event.canonicalContactId;
    dict[@"eventType"] = event.eventType;
    dict[@"title"] = event.title;
    dict[@"description"] = event.description ?: @"";
    dict[@"location"] = event.location ?: @"";
    dict[@"isPublic"] = @(event.isPublic);
    dict[@"userId"] = event.userId ?: @"";

    // Convert dates to timestamps (milliseconds)
    if (event.startTime) {
        dict[@"startTime"] = @([event.startTime timeIntervalSince1970] * 1000);
    }

    if (event.endTime) {
        dict[@"endTime"] = @([event.endTime timeIntervalSince1970] * 1000);
    }

    dict[@"createdAt"] = @([event.createdAt timeIntervalSince1970] * 1000);

    if (event.updatedAt) {
        dict[@"updatedAt"] = @([event.updatedAt timeIntervalSince1970] * 1000);
    }

    // Add metadata
    dict[@"metadata"] = event.metadata ?: @{};

    // Add creator information
    if (event.createdBy) {
        dict[@"createdBy"] = @{
            @"name": event.createdBy.name ?: @"",
            @"avatarUrl": event.createdBy.avatarUrl ?: @""
        };
    }

    return dict;
}

// Helper to convert CMPaginatedEventList to NSDictionary
- (NSDictionary *)paginatedEventListToDictionary:(CMPaginatedEventList *)list {
    if (!list) {
        return @{
            @"items": @[],
            @"total": @(0),
            @"skip": @(0),
            @"limit": @(0)
        };
    }

    NSMutableArray *itemsArray = [NSMutableArray array];
    for (CMSocialEvent *event in list.items) {
        NSDictionary *eventDict = [self socialEventToDictionary:event];
        [itemsArray addObject:eventDict];
    }

    return @{
        @"items": itemsArray,
        @"total": @(list.total),
        @"skip": @(list.skip),
        @"limit": @(list.limit)
    };
}

@end
