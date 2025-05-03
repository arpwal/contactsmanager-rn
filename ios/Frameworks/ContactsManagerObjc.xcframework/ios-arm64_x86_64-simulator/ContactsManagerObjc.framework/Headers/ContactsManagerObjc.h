//
//  ContactsManagerObjc.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/30/25.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

//! Project version number for ContactsManagerObjc.
FOUNDATION_EXPORT double ContactsManagerObjcVersionNumber;

//! Project version string for ContactsManagerObjc.
FOUNDATION_EXPORT const unsigned char ContactsManagerObjcVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <ContactsManagerObjc/PublicHeader.h>

// Authorization
#if __has_include(<ContactsManagerObjc/CMContactsAuthorizationService.h>)
#import <ContactsManagerObjc/CMContactsAuthorizationService.h>
#elif __has_include("Headers/CMContactsAuthorizationService.h")
#import "Headers/CMContactsAuthorizationService.h"
#endif

// Models
#if __has_include(<ContactsManagerObjc/CMUserInfo.h>)
#import <ContactsManagerObjc/CMUserInfo.h>
#elif __has_include("Headers/CMUserInfo.h")
#import "Headers/CMUserInfo.h"
#endif

#if __has_include(<ContactsManagerObjc/CMContact.h>)
#import <ContactsManagerObjc/CMContact.h>
#elif __has_include("Headers/CMContact.h")
#import "Headers/CMContact.h"
#endif

#if __has_include(<ContactsManagerObjc/CMContactDetail.h>)
#import <ContactsManagerObjc/CMContactDetail.h>
#elif __has_include("Headers/CMContactDetail.h")
#import "Headers/CMContactDetail.h"
#endif

#if __has_include(<ContactsManagerObjc/CMError.h>)
#import <ContactsManagerObjc/CMError.h>
#elif __has_include("Headers/CMError.h")
#import "Headers/CMError.h"
#endif

#if __has_include(<ContactsManagerObjc/CMSocialModels.h>)
#import <ContactsManagerObjc/CMSocialModels.h>
#elif __has_include("Headers/CMSocialModels.h")
#import "Headers/CMSocialModels.h"
#endif

#if __has_include(<ContactsManagerObjc/CMServerModels.h>)
#import <ContactsManagerObjc/CMServerModels.h>
#elif __has_include("Headers/CMServerModels.h")
#import "Headers/CMServerModels.h"
#endif

#if __has_include(<ContactsManagerObjc/CMContactSource.h>)
#import <ContactsManagerObjc/CMContactSource.h>
#elif __has_include("Headers/CMContactSource.h")
#import "Headers/CMContactSource.h"
#endif

#if __has_include(<ContactsManagerObjc/CMDeviceInfo.h>)
#import <ContactsManagerObjc/CMDeviceInfo.h>
#elif __has_include("Headers/CMDeviceInfo.h")
#import "Headers/CMDeviceInfo.h"
#endif


// Services
#if __has_include(<ContactsManagerObjc/CMContactService.h>)
#import <ContactsManagerObjc/CMContactService.h>
#elif __has_include("Headers/CMContactService.h")
#import "Headers/CMContactService.h"
#endif

#if __has_include(<ContactsManagerObjc/CMContactSyncManager.h>)
#import <ContactsManagerObjc/CMContactSyncManager.h>
#elif __has_include("Headers/CMContactSyncManager.h")
#import "Headers/CMContactSyncManager.h"
#endif

#if __has_include(<ContactsManagerObjc/CMRecommendationService.h>)
#import <ContactsManagerObjc/CMRecommendationService.h>
#elif __has_include("Headers/CMRecommendationService.h")
#import "Headers/CMRecommendationService.h"
#endif

#if __has_include(<ContactsManagerObjc/CMSocialService.h>)
#import <ContactsManagerObjc/CMSocialService.h>
#elif __has_include("Headers/CMSocialService.h")
#import "Headers/CMSocialService.h"
#endif

#if __has_include(<ContactsManagerObjc/CMContactSearchService.h>)
#import <ContactsManagerObjc/CMContactSearchService.h>
#elif __has_include("Headers/CMContactSearchService.h")
#import "Headers/CMContactSearchService.h"
#endif

#if __has_include(<ContactsManagerObjc/CMEventWrapperService.h>)
#import <ContactsManagerObjc/CMEventWrapperService.h>
#elif __has_include("Headers/CMEventWrapperService.h")
#import "Headers/CMEventWrapperService.h"
#endif


// Mappers
#if __has_include(<ContactsManagerObjc/CMContactMapper.h>)
#import <ContactsManagerObjc/CMContactMapper.h>
#elif __has_include("Headers/CMContactMapper.h")
#import "Headers/CMContactMapper.h"
#endif

// Extensions
#if __has_include(<ContactsManagerObjc/CMContactExtensions.h>)
#import <ContactsManagerObjc/CMContactExtensions.h>
#elif __has_include("Headers/CMContactExtensions.h")
#import "Headers/CMContactExtensions.h"
#endif

#if __has_include(<ContactsManagerObjc/NSDate+Utilities.h>)
#import <ContactsManagerObjc/NSDate+Utilities.h>
#elif __has_include("Headers/NSDate+Utilities.h")
#import "Headers/NSDate+Utilities.h"
#endif

#if __has_include(<ContactsManagerObjc/CMContactService+Sync.h>)
#import <ContactsManagerObjc/CMContactService+Sync.h>
#elif __has_include("Headers/CMContactService+Sync.h")
#import "Headers/CMContactService+Sync.h"
#endif


#if __has_include(<ContactsManagerObjc/CMContactSource+Sync.h>)
#import <ContactsManagerObjc/CMContactSource+Sync.h>
#elif __has_include("Headers/CMContactSource+Sync.h")
#import "Headers/CMContactSource+Sync.h"
#endif

#if __has_include(<ContactsManagerObjc/UIViewController+CMEvents.h>)
#import <ContactsManagerObjc/UIViewController+CMEvents.h>
#elif __has_include("Headers/UIViewController+CMEvents.h")
#import "Headers/UIViewController+CMEvents.h"
#endif


// API Client
#if __has_include(<ContactsManagerObjc/CMAPIClient.h>)
#import <ContactsManagerObjc/CMAPIClient.h>
#elif __has_include("Headers/CMAPIClient.h")
#import "Headers/CMAPIClient.h"
#endif

#if __has_include(<ContactsManagerObjc/CMAPIConfig.h>)
#import <ContactsManagerObjc/CMAPIConfig.h>
#elif __has_include("Headers/CMAPIConfig.h")
#import "Headers/CMAPIConfig.h"
#endif

#if __has_include(<ContactsManagerObjc/CMAPIError.h>)
#import <ContactsManagerObjc/CMAPIError.h>
#elif __has_include("Headers/CMAPIError.h")
#import "Headers/CMAPIError.h"
#endif

#if __has_include(<ContactsManagerObjc/CMContactHashingExtension.h>)
#import <ContactsManagerObjc/CMContactHashingExtension.h>
#elif __has_include("Headers/CMContactHashingExtension.h")
#import "Headers/CMContactHashingExtension.h"
#endif

#if __has_include(<ContactsManagerObjc/CMContactStorageManager.h>)
#import <ContactsManagerObjc/CMContactStorageManager.h>
#elif __has_include("Headers/CMContactStorageManager.h")
#import "Headers/CMContactStorageManager.h"
#endif

#if __has_include(<ContactsManagerObjc/CMContactSyncInfo.h>)
#import <ContactsManagerObjc/CMContactSyncInfo.h>
#elif __has_include("Headers/CMContactSyncInfo.h")
#import "Headers/CMContactSyncInfo.h"
#endif

#if __has_include(<ContactsManagerObjc/CMContactSyncInfo.h>)
#import <ContactsManagerObjc/CMContactSyncInfo.h>
#elif __has_include("Headers/CMContactSyncInfo.h")
#import "Headers/CMContactSyncInfo.h"
#endif


// Options
#if __has_include(<ContactsManagerObjc/CMContactsManagerOptions.h>)
#import <ContactsManagerObjc/CMContactsManagerOptions.h>
#elif __has_include("Headers/CMContactsManagerOptions.h")
#import "Headers/CMContactsManagerOptions.h"
#endif
