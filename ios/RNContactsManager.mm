#import "RNContactsManager.h"

@implementation RNContactsManager

RCT_EXPORT_MODULE()

RCT_EXPORT_METHOD(multiply:(double)a
                  b:(double)b
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSNumber *result = @(a * b);
    resolve(result);
}

RCT_EXPORT_METHOD(getContacts:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactsManager: getContacts called");

    Class authServiceClass = NSClassFromString(@"CMContactsAuthorizationService");
    if (!authServiceClass) {
        NSLog(@"RNContactsManager: CMContactsAuthorizationService class not found!");
        reject(@"contacts_manager_error", @"CMContactsAuthorizationService class not found", nil);
        return;
    }

    ContactsAccessStatus accessStatus = [[CMContactsAuthorizationService sharedInstance] checkAccessStatus];
    BOOL hasPermission = (accessStatus == ContactsAccessStatusAuthorized || accessStatus == ContactsAccessStatusLimitedAuthorized);

    NSLog(@"RNContactsManager: Access status for getContacts: %ld", (long)accessStatus);

    if (!hasPermission) {
        reject(@"contacts_permission_denied", @"Contacts permission not granted", nil);
        return;
    }

    // Here we would normally use a ContactsManager class from the ObjC framework
    // to fetch contacts, but since we don't have that implementation in the snippets,
    // we'll create a placeholder for now

    // Note: In a real implementation, you would call something like:
    // [[ContactsManager sharedInstance] fetchContactsWithCompletion:^(NSArray *contacts, NSError *error) { ... }];

    // For now, we'll return an empty array to make the interface work
    NSArray *emptyContacts = @[];
    resolve(emptyContacts);

    // TODO: Implement actual contact fetching using the ContactsManagerObjc framework
    // when the complete implementation is available
}

@end
