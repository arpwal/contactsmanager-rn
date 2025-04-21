#import "ContactsmanagerRn.h"
#import <ContactsManagerObjc/ContactsManagerObjc.h>

@implementation ContactsmanagerRn
RCT_EXPORT_MODULE()

// Example method
// See // https://reactnative.dev/docs/native-modules-ios
RCT_EXPORT_METHOD(multiply:(double)a
                  b:(double)b
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSNumber *result = @(a * b);

    resolve(result);
}

RCT_EXPORT_METHOD(requestContactsAccess:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    // Add debug logging
    NSLog(@"ContactsmanagerRn: requestContactsAccess called");

    Class authServiceClass = NSClassFromString(@"ContactsAuthorizationService");
    if (!authServiceClass) {
        NSLog(@"ContactsmanagerRn: ContactsAuthorizationService class not found!");
        NSDictionary *response = @{
            @"granted": @(NO),
            @"status": @(0),
            @"error": @"ContactsAuthorizationService class not found"
        };
        resolve(response);
        return;
    }

    NSLog(@"ContactsmanagerRn: ContactsAuthorizationService class found");

    [[ContactsAuthorizationService sharedInstance] requestAccessWithCompletion:^(ContactsAccessStatus status, NSError * _Nullable error) {
        if (error) {
            NSLog(@"ContactsmanagerRn: Error requesting contacts access: %@", error);
            reject(@"contacts_permission_error", @"Failed to request contacts permission", error);
            return;
        }

        NSLog(@"ContactsmanagerRn: Access status: %ld", (long)status);

        BOOL granted = (status == ContactsAccessStatusAuthorized || status == ContactsAccessStatusLimitedAuthorized);
        NSDictionary *response = @{
            @"granted": @(granted),
            @"status": @(status)
        };
        resolve(response);
    }];
}

RCT_EXPORT_METHOD(getContacts:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    // Add debug logging
    NSLog(@"ContactsmanagerRn: getContacts called");

    Class authServiceClass = NSClassFromString(@"ContactsAuthorizationService");
    if (!authServiceClass) {
        NSLog(@"ContactsmanagerRn: ContactsAuthorizationService class not found!");
        reject(@"contacts_manager_error", @"ContactsAuthorizationService class not found", nil);
        return;
    }

    ContactsAccessStatus accessStatus = [[ContactsAuthorizationService sharedInstance] checkAccessStatus];
    BOOL hasPermission = (accessStatus == ContactsAccessStatusAuthorized || accessStatus == ContactsAccessStatusLimitedAuthorized);

    NSLog(@"ContactsmanagerRn: Access status for getContacts: %ld", (long)accessStatus);

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
