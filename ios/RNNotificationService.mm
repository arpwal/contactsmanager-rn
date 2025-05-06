//
//  RNNotificationService.mm
//  ContactsmanagerRn
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import "RNNotificationService.h"
#import <React/RCTUtils.h>
#import <React/RCTConvert.h>
#import <Foundation/Foundation.h>

// Import ContactsManagerObjc framework headers
#if __has_include(<ContactsManagerObjc/CMEventWrapperService.h>)
#import <ContactsManagerObjc/CMEventWrapperService.h>
#elif __has_include("ContactsManagerObjc/CMEventWrapperService.h")
#import "ContactsManagerObjc/CMEventWrapperService.h"
#endif

@implementation RNNotificationService

RCT_EXPORT_MODULE()

// Map of event types between native and JavaScript
NSDictionary *eventTypesMap;

// Initialize the module
- (instancetype)init {
  self = [super init];
  if (self) {
    // Initialize the event type mapping dictionary
    eventTypesMap = @{
      @"appDidBecomeActive": @(CMContactsManagerEventAppDidBecomeActive),
      @"appDidEnterBackground": @(CMContactsManagerEventAppDidEnterBackground),
      @"contactStoreDidChange": @(CMContactsManagerEventContactStoreDidChange),
      @"appWasTerminated": @(CMContactsManagerEventAppWasTerminated),
      @"contactsAccessChanged": @(CMContactsManagerEventContactsAccessChanged)
    };
  }
  return self;
}

// Reserve the main queue for this module
- (dispatch_queue_t)methodQueue {
  return dispatch_get_main_queue();
}

// Export method to start observing notifications
RCT_EXPORT_METHOD(startObserving:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject) {
  @try {
    [[CMEventWrapperService sharedInstance] startObserving];
    resolve(@(YES));
  } @catch (NSException *exception) {
    NSError *error = RCTErrorWithMessage(exception.reason);
    reject(@"notification_error", @"Failed to start notification observer", error);
  }
}

// Export method to stop observing notifications
RCT_EXPORT_METHOD(stopObserving:(RCTPromiseResolveBlock)resolve
                 reject:(RCTPromiseRejectBlock)reject) {
  @try {
    [[CMEventWrapperService sharedInstance] stopObserving];
    resolve(@(YES));
  } @catch (NSException *exception) {
    NSError *error = RCTErrorWithMessage(exception.reason);
    reject(@"notification_error", @"Failed to stop notification observer", error);
  }
}

// Export method to subscribe to a specific event
RCT_EXPORT_METHOD(subscribeToEvent:(NSString *)eventType
                  withIdentifier:(NSString *)identifier
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject) {
  NSNumber *eventValue = eventTypesMap[eventType];

  if (eventValue == nil) {
    NSError *error = RCTErrorWithMessage([NSString stringWithFormat:@"Invalid event type: %@", eventType]);
    reject(@"invalid_event", @"Invalid event type specified", error);
    return;
  }

  @try {
    // Create a weakSelf reference to avoid retain cycles
    __weak RNNotificationService *weakSelf = self;

    [[CMEventWrapperService sharedInstance] subscribeToEvent:(CMContactsManagerEvent)[eventValue integerValue]
                                             withIdentifier:identifier
                                                    handler:^{
      // This handler will be called when the event occurs
      // We could send events to JS here using RCTEventEmitter, but for now
      // we'll just handle the subscription part

      // In a future implementation, we might want to emit events to JS here
    }];

    resolve(@(YES));
  } @catch (NSException *exception) {
    NSError *error = RCTErrorWithMessage(exception.reason);
    reject(@"subscription_error", @"Failed to subscribe to event", error);
  }
}

// Export method to unsubscribe from a specific event
RCT_EXPORT_METHOD(unsubscribeFromEvent:(NSString *)eventType
                  withIdentifier:(NSString *)identifier
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject) {
  NSNumber *eventValue = eventTypesMap[eventType];

  if (eventValue == nil) {
    NSError *error = RCTErrorWithMessage([NSString stringWithFormat:@"Invalid event type: %@", eventType]);
    reject(@"invalid_event", @"Invalid event type specified", error);
    return;
  }

  @try {
    [[CMEventWrapperService sharedInstance] unsubscribeFromEvent:(CMContactsManagerEvent)[eventValue integerValue]
                                                 withIdentifier:identifier];
    resolve(@(YES));
  } @catch (NSException *exception) {
    NSError *error = RCTErrorWithMessage(exception.reason);
    reject(@"subscription_error", @"Failed to unsubscribe from event", error);
  }
}

@end
