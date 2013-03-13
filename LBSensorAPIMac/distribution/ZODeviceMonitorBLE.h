//
//  ZODeviceMonitorBLE.h
//  LUMObackDeviceBLE
//
//  Created by Denis Bohm on 5/29/12.
//

#import "ZODeviceMonitorShared.h"

#if TARGET_OS_IPHONE
#import <CoreBluetooth/CoreBluetooth.h>
#else
#import <IOBluetooth/IOBluetooth.h>
#endif


@class ZODeviceBLE;
@class ZODeviceProfile;

@interface ZODeviceMonitorBLE : ZODeviceMonitorShared<CBCentralManagerDelegate>

//@property(strong, readonly) CBCentralManager *manager;
@property(strong) CBCentralManager *manager;
@property(strong, readonly) ZODeviceProfile *profile;
@property(strong, readonly) NSArray *serviceUUIDs;
@property NSTimeInterval autoconnectRetryTimeInterval;
@property NSTimer *timer;
@property BOOL scan;

- (id)init;

- (void)connectDevice:(ZODeviceBLE *)device;
- (void)disconnectDevice:(ZODeviceBLE *)device;
- (void)removeDevice:(ZODeviceBLE *)device;

@end
