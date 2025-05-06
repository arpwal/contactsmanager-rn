//
//  CMContactsAuthorizationService.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * ContactsAccessStatus enum representing the various access states for contacts
 */
typedef NS_ENUM(NSInteger, ContactsAccessStatus) {
    ContactsAccessStatusNotDetermined,
    ContactsAccessStatusAuthorized,
    ContactsAccessStatusLimitedAuthorized,
    ContactsAccessStatusDenied,
    ContactsAccessStatusRestricted
};

/**
 * ContactsAuthorizationService class for handling contacts access permissions
 */
@interface CMContactsAuthorizationService : NSObject

/**
 * Singleton instance of ContactsAuthorizationService
 */
+ (instancetype)sharedInstance;

/**
 * Requests access to contacts
 * @param completion Block called when access request completes with current status and any error
 */
- (void)requestAccessWithCompletion:(void (^)(ContactsAccessStatus status, NSError * _Nullable error))completion;

/**
 * Checks the current access status for contacts
 * @return Current ContactsAccessStatus value
 */
- (ContactsAccessStatus)checkAccessStatus;

/**
 * Checks if the app has read access to contacts (either authorized or limited)
 * @return YES if the app has read access to contacts, NO otherwise
 */
- (BOOL)hasContactsReadAccess;

/**
 * Determines whether settings alert should be shown to the user
 * @return YES if the alert should be shown, NO otherwise
 */
- (BOOL)shouldShowSettingsAlert;

/**
 * Shows an alert view prompting user to update settings
 * @param viewController The view controller to present the alert from
 */
- (void)showSettingsAlertViewFromViewController:(UIViewController *)viewController;

@end

NS_ASSUME_NONNULL_END 
