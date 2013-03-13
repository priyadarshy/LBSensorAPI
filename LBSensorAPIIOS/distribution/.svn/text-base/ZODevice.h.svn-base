//
//  ZODevice.h
//  LUMObackTool
//
//  Created by Denis Bohm on 12/18/11.
//

#import "ZOObservable.h"
#import "ZOExecutor.h"

@interface ZODeviceVersion : NSObject

@property uint16_t major;
@property uint16_t minor;
@property uint32_t revision;
@property uint32_t capabilities;

@end

@interface ZODeviceBatteryState : NSObject

@property double batteryVoltage;
@property BOOL hasUSBPower;
@property BOOL isCharging;
@property double chargeCurrent;
@property double systemCurrent;
@property double batteryCharge;

@end

@interface ZODeviceStorageState : NSObject

@property uint8_t type;
@property BOOL isDataSeries;
@property BOOL flushOnIdle;
@property BOOL upload;
@property uint8_t priority;
@property uint16_t startPage;
@property uint16_t pageCount;
@property uint16_t firstUsedPage;
@property uint16_t usedPageCount;
@property uint8_t recordSize;
@property NSTimeInterval interval;

@end

@interface ZODeviceAccelerometerSelfTest : NSObject

@property int16_t sx;
@property int16_t sy;
@property int16_t sz;
@property int16_t ax;
@property int16_t ay;
@property int16_t az;

@end

typedef enum {
    accelerometer_rate_1,
    accelerometer_rate_10,
    accelerometer_rate_25,
    accelerometer_rate_50,
    accelerometer_rate_100,
    accelerometer_rate_200,
    accelerometer_rate_400,
} accelerometer_rate_t;

typedef enum {
    accelerometer_scale_2,
    accelerometer_scale_4,
    accelerometer_scale_8,
    accelerometer_scale_16,
} accelerometer_scale_t;

@interface ZODeviceAccelerometerSettings : NSObject

@property BOOL lowPower;
@property accelerometer_rate_t rate;
@property accelerometer_scale_t scale;

@end

@interface ZODeviceSensing : NSObject

@property NSTimeInterval time;
@property int16_t x;
@property int16_t y;
@property int16_t z;

@end

@interface ZODeviceDiagnostic : NSObject

@property NSTimeInterval time;
@property uint16_t type;
@property(strong) NSData *args;
@property(strong) NSString* json;

@end

@interface ZODeviceBluetoothTestReport : NSObject

@property uint16_t packetCount;

@end

@interface ZODeviceTouchSettings : NSObject

@property uint8_t lowPower;
@property uint8_t atiTarget;
@property uint8_t buttonAtiBase;
@property uint8_t buttonThreshold;
@property uint8_t wearAtiBase;
@property uint8_t wearThreshold;

@end

@interface ZODeviceModeSettings : NSObject

@property NSTimeInterval holdDuration;
@property uint8_t vibrateCycles;
@property uint8_t vibrateLevel;
@property NSTimeInterval vibrateOnDuration;
@property NSTimeInterval vibrateOffDuration;

@end

@interface ZODeviceUpdateMetadata : NSObject

@property uint8_t type;
@property uint32_t version;
@property uint32_t revision;
@property uint32_t length;
@property NSTimeInterval time;
@property NSData *digest;

@end

@interface ZODeviceJSON : NSObject

@property(strong) NSDictionary *messageFromLumo;
@property(strong) NSString *debugMessage; 

@end

typedef enum {ZODeviceStateClosed, ZODeviceStateOpening, ZODeviceStateOpen, ZODeviceStateClosing} ZODeviceState;

typedef enum {ZODeviceRestartModeGraceful, ZODeviceRestartModeFault, ZODeviceRestartModeWatchdogTimeout} ZODeviceRestartMode;

@protocol ZODeviceDelegate <NSObject>

@optional
- (void)deviceState:(ZODeviceState)state;
- (void)deviceVersion:(ZODeviceVersion *)version;
- (void)deviceHardwareId:(NSString *)hardwareId;
- (void)deviceBatteryState:(ZODeviceBatteryState *)batteryState;
- (void)deviceStorageStates:(NSArray *)storageStates;
- (void)deviceBluetoothTestReport:(ZODeviceBluetoothTestReport *)report;
- (void)deviceAccelerometerSelfTest:(ZODeviceAccelerometerSelfTest *)selfTest;
- (void)deviceAccelerometerSettings:(ZODeviceAccelerometerSettings *)settings;
- (void)deviceTouchSettings:(ZODeviceTouchSettings *)settings;
- (void)deviceModeSettings:(ZODeviceModeSettings *)settings;
- (void)deviceCommunication:(NSDictionary *)communication;
- (void)devicePluginInactive:(NSDictionary *)inactive;
- (void)deviceTouchInactive:(NSDictionary *)inactive;
- (void)deviceSoftId:(NSData *)value;
- (void)deviceEcho:(uint32_t)value;
- (void)deviceUpdateMetadata:(NSArray *)metadatas;
- (void)deviceUpdateGetCRCs:(uint32_t)address length:(uint32_t)length crcs:(NSArray *)crcs;
- (void)deviceUpdateTransfer;
- (void)deviceUpdateReady;
- (void)deviceRTC:(NSDate *)date isSet:(BOOL)isSet; // date starts at UNIX epoch (before being set by a client)
- (void)deviceRTCSelfTest:(uint32_t)count;
- (void)deviceQuiet:(BOOL)quiet;
- (void)deviceSensingTime:(NSDate *)date; // nil when not set
- (void)deviceSensingUpload:(NSArray *)sensings; // array of ZODeviceSensing
- (void)deviceSensing:(ZODeviceSensing *)sensing;
- (void)deviceDiagnosticUpload:(NSArray *)diagnostics; // array of ZODeviceDiagnostic
- (void)deviceDiagnostic:(ZODeviceDiagnostic *)diagnostic;
- (void)deviceJSON:(ZODeviceJSON *)json;

@end

@interface ZODeviceObservable : ZOObservable <ZODeviceDelegate>
@end

@protocol ZODevice <NSObject>

@property (strong, readonly) NSNumber *RSSI;
@property (strong, readonly) NSDate *discoveryDate;

// uuid to use for bluetooth connection purposes (can be null if the device has never connected before)
@property (strong, readonly) NSString* uuid;

@property BOOL firmwareUpdateEnabled;
@property BOOL spontaneity;

@property (weak) id<ZODeviceDelegate> delegate;
@property (strong, readonly) ZODeviceObservable *observable;
@property (strong, readonly) ZODeviceObservable *notifyObservable;

@property (strong, readonly) ZOExecutor *executor;

@property (readonly) ZODeviceState state;
@property (readonly) BOOL active;

@property (strong, readonly) ZODeviceVersion *version;
@property (strong, readonly) NSString *hardwareId;
@property (strong, readonly) NSData *softId;
@property (strong, readonly) ZODeviceUpdateMetadata *baseMetadata;
@property (strong, readonly) ZODeviceUpdateMetadata *pluginMetadata;
@property (strong, readonly) ZODeviceBatteryState *batteryState;
@property (readonly) BOOL quiet;
@property (readonly) BOOL baseOutOfDate;
@property (readonly) BOOL pluginOutOfDate;
@property (readonly) BOOL isUpdateReady;

- (void)open;
- (void)close;

- (void)submitTaskWithDescription:(NSString *)description block:(void (^)(id<ZODevice>))block;

- (void)submitUpdateCommit;

// tx calls should only be made from tasks submitted to the executor

- (void)txMint:(NSData *)softId;
- (void)txEnterStorageMode;
- (void)txEnterIdleMode;
- (void)txRestart;
- (void)txRestart:(ZODeviceRestartMode)mode;

- (void)txGetProperty:(NSArray *)properties;

- (void)txSetRTC:(NSDate *)date;

- (void)txSetQuiet:(BOOL)quiet;

- (void)txSetSensingTime:(NSDate *)date;

- (void)txEcho:(uint32_t)value;

- (void)txUpdateGetCRCs:(uint32_t)address length:(uint32_t)length count:(uint32_t)count;
- (void)txUpdateErase:(uint32_t)address length:(uint32_t)length;
- (void)txUpdateTransfer:(uint32_t)address data:(NSData *)data;
- (void)txUpdateCommit:(NSArray *)metadatas;

- (void)txMotorOn:(NSTimeInterval)duration
            level:(uint8_t)level
          reverse:(BOOL)reverse;

- (void)txIndicatorOn:(NSTimeInterval)duration
                style:(uint8_t)style
                  red:(uint8_t)red
                green:(uint8_t)green
                 blue:(uint8_t)blue
              current:(uint8_t)current;

- (void)txBluetoothTest:(NSTimeInterval)duration
                    msb:(uint8_t)msb
                    lsb:(uint8_t)lsb;

- (void)txSetAccelerometerSettings:(ZODeviceAccelerometerSettings *)settings;

- (void)txSetTouchSettings:(ZODeviceTouchSettings *)settings;
- (void)txSetTouchInactive:(NSDictionary *)inactive;

- (void)txSetModeSettings:(ZODeviceModeSettings *)settings;

- (void)txSetPluginInactive:(NSDictionary *)inactive;

- (void)txSetCommunication:(NSDictionary *)communication;

- (void)txJson:(NSString *)p_cmdstr; // // AHN Send JSON to device

@end