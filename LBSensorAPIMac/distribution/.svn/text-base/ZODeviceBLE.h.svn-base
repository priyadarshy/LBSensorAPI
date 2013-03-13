//
//  ZODeviceBLE.h
//  ZODeviceBLE
//
//  Created by Denis Bohm on 5/29/12.
//

#import "ZODeviceProfile.h"
#import "ZODeviceService.h"
#import "ZODeviceShared.h"

#if TARGET_OS_IPHONE
#import <CoreBluetooth/CoreBluetooth.h>
#else
#import <IOBluetooth/IOBluetooth.h>
#endif

@protocol ZOBulkTransferDelegate;
@class ZODeviceMonitorBLE;
@class ZORadar;
@class ZORadarPong;

@interface ZODeviceBLE : ZODeviceShared<CBPeripheralDelegate>

@property(weak) ZODeviceMonitorBLE *monitor;
@property(strong, readonly) CBPeripheral *peripheral;
@property(strong, readonly) NSDictionary *advertisementData;
@property(strong) NSNumber *RSSI;
@property(strong) NSDate *discoveryDate;
@property(strong) ZORadarPong *pong;

@property(strong, readonly) ZODeviceProfile *profile;
@property(strong, readonly) NSArray *services;
@property(strong, readonly) NSMutableDictionary *servicesByCharacteristicUUID;

@property(strong, readonly) ZORadar *radar;

- (id)init:(ZODeviceMonitorBLE *)monitor peripheral:(CBPeripheral *)peripheral;

- (void)rssiStart;
- (void)rssiStop;

- (void)connected;
- (void)disconnected;

- (void)registerServiceCharacteristic:(id<ZODeviceService>)service characteristics:(NSArray *)characteristics;
- (void)notify:(id<ZODeviceService>)service characteristics:(NSArray *)characteristics;

- (void)forceClose;

@end
