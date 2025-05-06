//
//  CMNotificationService.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>

// Import event wrapper service for notification events
#if __has_include(<ContactsManagerObjc/CMEventWrapperService.h>)
#import <ContactsManagerObjc/CMEventWrapperService.h>
#elif __has_include("CMEventWrapperService.h")
#import "CMEventWrapperService.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 * Notification types supported by the service
 */
typedef NS_ENUM(NSInteger, CMNotificationType) {
    CMNotificationTypeSystem,
    CMNotificationTypeNewMatches,
    CMNotificationTypeConnectionRequest,
    CMNotificationTypeImportant
};

/**
 * Model class representing a notification
 */
@interface CMNotification : NSObject

@property (nonatomic, copy, readonly) NSString *notificationId;
@property (nonatomic, copy, readonly) NSString *title;
@property (nonatomic, copy, readonly) NSString *body;
@property (nonatomic, assign, readonly) CMNotificationType type;
@property (nonatomic, strong, readonly, nullable) NSDictionary *data;
@property (nonatomic, strong, readonly) NSDate *createdAt;
@property (nonatomic, assign, readonly) BOOL isRead;

/**
 * Initialize with all properties
 */
- (instancetype)initWithId:(NSString *)notificationId
                     title:(NSString *)title
                      body:(NSString *)body
                      type:(CMNotificationType)type
                      data:(nullable NSDictionary *)data
                 createdAt:(NSDate *)createdAt
                    isRead:(BOOL)isRead;

@end

/**
 * Completion block for notification operations
 */
typedef void (^CMNotificationCompletionBlock)(BOOL success, NSError * _Nullable error);

/**
 * Completion block for fetching notifications
 */
typedef void (^CMNotificationFetchCompletionBlock)(NSArray<CMNotification *> * _Nullable notifications, NSError * _Nullable error);

/**
 * CMNotificationService - Service for managing system and app notifications
 */
@interface CMNotificationService : NSObject

/**
 * Shared instance singleton accessor
 */
+ (instancetype)sharedInstance;

/**
 * Register for push notifications
 * @param completion Block called when registration completes
 */
- (void)registerForPushNotifications:(CMNotificationCompletionBlock)completion;

/**
 * Update device token for push notifications
 * @param deviceToken The device token received from APNS
 * @param completion Block called when update completes
 */
- (void)updateDeviceToken:(NSData *)deviceToken
               completion:(CMNotificationCompletionBlock)completion;

/**
 * Fetch all notifications for the current user
 * @param completion Block called with fetched notifications
 */
- (void)fetchNotifications:(CMNotificationFetchCompletionBlock)completion;

/**
 * Mark a notification as read
 * @param notificationId The ID of the notification to mark as read
 * @param completion Block called when operation completes
 */
- (void)markNotificationAsRead:(NSString *)notificationId
                    completion:(CMNotificationCompletionBlock)completion;

/**
 * Mark all notifications as read
 * @param completion Block called when operation completes
 */
- (void)markAllNotificationsAsRead:(CMNotificationCompletionBlock)completion;

/**
 * Delete a notification
 * @param notificationId The ID of the notification to delete
 * @param completion Block called when operation completes
 */
- (void)deleteNotification:(NSString *)notificationId
                completion:(CMNotificationCompletionBlock)completion;

/**
 * Delete all notifications
 * @param completion Block called when operation completes
 */
- (void)deleteAllNotifications:(CMNotificationCompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
