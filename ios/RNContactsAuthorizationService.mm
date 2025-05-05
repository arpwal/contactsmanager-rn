#import "RNContactsAuthorizationService.h"

@implementation RNContactsAuthorizationService

RCT_EXPORT_MODULE()

RCT_EXPORT_METHOD(requestContactsAccess:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactsAuthorizationService: requestContactsAccess called");

    Class authServiceClass = NSClassFromString(@"CMContactsAuthorizationService");
    if (!authServiceClass) {
        NSLog(@"RNContactsAuthorizationService: CMContactsAuthorizationService class not found!");
        NSDictionary *response = @{
            @"granted": @(NO),
            @"status": @(0),
            @"error": @"CMContactsAuthorizationService class not found"
        };
        resolve(response);
        return;
    }

    NSLog(@"RNContactsAuthorizationService: CMContactsAuthorizationService class found");

    [[CMContactsAuthorizationService sharedInstance] requestAccessWithCompletion:^(ContactsAccessStatus status, NSError * _Nullable error) {
        if (error) {
            NSLog(@"RNContactsAuthorizationService: Error requesting contacts access: %@", error);
            reject(@"contacts_permission_error", @"Failed to request contacts permission", error);
            return;
        }

        NSLog(@"RNContactsAuthorizationService: Access status: %ld", (long)status);

        BOOL granted = (status == ContactsAccessStatusAuthorized || status == ContactsAccessStatusLimitedAuthorized);
        NSDictionary *response = @{
            @"granted": @(granted),
            @"status": @(status)
        };
        resolve(response);
    }];
}

RCT_EXPORT_METHOD(checkAccessStatus:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactsAuthorizationService: checkAccessStatus called");

    Class authServiceClass = NSClassFromString(@"CMContactsAuthorizationService");
    if (!authServiceClass) {
        NSLog(@"RNContactsAuthorizationService: CMContactsAuthorizationService class not found!");
        reject(@"contacts_manager_error", @"CMContactsAuthorizationService class not found", nil);
        return;
    }

    ContactsAccessStatus status = [[CMContactsAuthorizationService sharedInstance] checkAccessStatus];
    resolve(@(status));
}

RCT_EXPORT_METHOD(shouldShowSettingsAlert:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    NSLog(@"RNContactsAuthorizationService: shouldShowSettingsAlert called");

    Class authServiceClass = NSClassFromString(@"CMContactsAuthorizationService");
    if (!authServiceClass) {
        NSLog(@"RNContactsAuthorizationService: CMContactsAuthorizationService class not found!");
        reject(@"contacts_manager_error", @"CMContactsAuthorizationService class not found", nil);
        return;
    }

    BOOL shouldShow = [[CMContactsAuthorizationService sharedInstance] shouldShowSettingsAlert];
    resolve(@(shouldShow));
}

@end
