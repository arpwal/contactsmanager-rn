//
//  CMDeviceInfo.h
//  ContactsManagerObjc
//
//  Created by Arpit Agarwal on 4/20/25.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Device information for analytics and troubleshooting
 */
@interface CMDeviceInfo : NSObject

// Device identifiers
@property (nonatomic, copy, readonly) NSString *deviceId;
@property (nonatomic, copy, readonly) NSString *hardwareId;

// Hardware information
@property (nonatomic, copy, readonly) NSString *deviceName;
@property (nonatomic, copy, readonly) NSString *deviceModel;
@property (nonatomic, copy, readonly) NSString *deviceManufacturer;
@property (nonatomic, copy, readonly) NSString *deviceModelId;

// OS information
@property (nonatomic, copy, readonly) NSString *osName;
@property (nonatomic, copy, readonly) NSString *osVersion;

// Display information
@property (nonatomic, assign, readonly) NSInteger screenWidth;
@property (nonatomic, assign, readonly) NSInteger screenHeight;
@property (nonatomic, assign, readonly) CGFloat screenDensity;

// Network information
@property (nonatomic, copy, readonly) NSString *networkType;

// App information
@property (nonatomic, copy, readonly) NSString *appVersion;
@property (nonatomic, copy, readonly) NSString *appBuild;
@property (nonatomic, copy, readonly) NSString *appId;

// Locale information
@property (nonatomic, copy, readonly) NSString *locale;
@property (nonatomic, copy, readonly) NSString *timezone;

// Hardware capabilities
@property (nonatomic, strong, readonly, nullable) NSNumber *totalMemory;
@property (nonatomic, strong, readonly, nullable) NSNumber *cpuCount;
@property (nonatomic, strong, readonly, nullable) NSNumber *batteryLevel;
@property (nonatomic, strong, readonly, nullable) NSNumber *isCharging;

/**
 * Initialize with device information
 */
- (instancetype)init;

/**
 * Convert to a dictionary for JSON serialization
 */
- (NSDictionary *)asDictionary;

@end

NS_ASSUME_NONNULL_END 