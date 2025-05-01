//
//  ContactsManagerObjc.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/30/25.
//

#import <Foundation/Foundation.h>

//! Project version number for ContactsManagerObjc.
FOUNDATION_EXPORT double ContactsManagerObjcVersionNumber;

//! Project version string for ContactsManagerObjc.
FOUNDATION_EXPORT const unsigned char ContactsManagerObjcVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <ContactsManagerObjc/PublicHeader.h>

// Authorization
#import <ContactsManagerObjc/ContactsAuthorizationService.h>

// Models
#import <ContactsManagerObjc/CMUserInfo.h>
#import <ContactsManagerObjc/CMContact.h>
#import <ContactsManagerObjc/CMContactDetail.h>
#import <ContactsManagerObjc/CMError.h>
#import <ContactsManagerObjc/CMSocialModels.h>
#import <ContactsManagerObjc/CMServerModels.h>

// Services
#import <ContactsManagerObjc/CMContactService.h>
#import <ContactsManagerObjc/CMContactSyncManager.h>
#import <ContactsManagerObjc/CMRecommendationService.h>
#import <ContactsManagerObjc/CMSocialService.h>

// Mappers
#import <ContactsManagerObjc/CMContactMapper.h>

// Extensions
#import <ContactsManagerObjc/CMContactExtensions.h>
#import <ContactsManagerObjc/NSDate+Utilities.h>

// API Client
#import <ContactsManagerObjc/CMAPIClient.h>
#import <ContactsManagerObjc/CMAPIConfig.h>
#import <ContactsManagerObjc/CMAPIError.h>

// Options
#import <ContactsManagerObjc/CMContactsManagerOptions.h>
