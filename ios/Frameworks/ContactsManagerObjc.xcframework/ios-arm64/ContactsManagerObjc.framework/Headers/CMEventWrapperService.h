//
//  CMEventWrapperService.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Enum representing different types of events that can occur in the ContactsManager
 */
typedef NS_ENUM(NSInteger, CMContactsManagerEvent) {
    CMContactsManagerEventAppDidBecomeActive,
    CMContactsManagerEventAppDidEnterBackground,
    CMContactsManagerEventContactStoreDidChange,
    CMContactsManagerEventAppWasTerminated,
    CMContactsManagerEventContactsAccessChanged
};

/**
 * Block type definition for event handlers
 */
typedef void (^CMEventHandlerBlock)(void);

/**
 * Service responsible for managing event subscriptions and notifications
 */
@interface CMEventWrapperService : NSObject

/**
 * Shared instance for singleton access
 */
+ (instancetype)sharedInstance;

/**
 * Subscribe to a specific event
 * @param event The event to subscribe to
 * @param identifier Unique identifier for the subscription
 * @param handler The handler to be called when the event occurs
 */
- (void)subscribeToEvent:(CMContactsManagerEvent)event
           withIdentifier:(NSString *)identifier
                  handler:(CMEventHandlerBlock)handler;

/**
 * Unsubscribe from a specific event
 * @param event The event to unsubscribe from
 * @param identifier The identifier of the subscription to remove
 */
- (void)unsubscribeFromEvent:(CMContactsManagerEvent)event
              withIdentifier:(NSString *)identifier;

/**
 * Start observing system events
 */
- (void)startObserving;

/**
 * Stop observing system events
 */
- (void)stopObserving;

@end

NS_ASSUME_NONNULL_END 