//
//  UIViewController+CMEvents.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#if __has_include(<ContactsManagerObjc/CMEventWrapperService.h>)
#import <ContactsManagerObjc/CMEventWrapperService.h>
#elif __has_include("CMEventWrapperService.h")
#import "CMEventWrapperService.h"
#endif


NS_ASSUME_NONNULL_BEGIN

/**
 * Category that adds convenience methods to UIViewController for subscribing to ContactsManager events.
 */
@interface UIViewController (CMEvents)

/**
 * Subscribe to a ContactsManager event with an identifier and handler.
 * This method automatically unsubscribes when the view controller is deallocated.
 *
 * @param event The event to subscribe to
 * @param identifier A unique identifier for the subscription
 * @param handler The block to execute when the event occurs
 */
- (void)subscribeToContactsManagerEvent:(CMContactsManagerEvent)event
                         withIdentifier:(NSString *)identifier
                                handler:(CMEventHandlerBlock)handler;

/**
 * Unsubscribe from a ContactsManager event with the given identifier.
 *
 * @param event The event to unsubscribe from
 * @param identifier The unique identifier used when subscribing
 */
- (void)unsubscribeFromContactsManagerEvent:(CMContactsManagerEvent)event
                             withIdentifier:(NSString *)identifier;

@end

NS_ASSUME_NONNULL_END 
