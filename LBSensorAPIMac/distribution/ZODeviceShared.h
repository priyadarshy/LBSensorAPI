//
//  ZODeviceShared.h
//  LUMObackTool
//
//  Created by Denis Bohm on 12/18/11.
//

#import "ZODevice.h"
#import "ZODiagnosticCatalog.h"

@class ZOPacket;

@protocol ZODeviceErrorDelegate
@optional
- (void)crcMismatch;
- (void)unrecognizedType;
- (void)malformedPrefix;
- (void)unmatchableData;
- (void)unexpectedLength;
- (void)unrecognizedPropertyType;
- (void)malformedJson;
- (void)unexpectedUploadLength;
- (void)uploadCRCMismatch;
- (void)unrecognizedUploadType;
- (void)handlerException;
- (void)unexpectedUploadPage;
- (void)unexpectedUploadIndex;
- (void)uploadLengthMismatch;
@end

typedef enum {ZODeviceTransferTypeExecute, ZODeviceTransferTypeUpdate} ZODeviceTransferType;

@interface ZODeviceTransfer : NSObject
@property ZODeviceTransferType type;
@property NSData *data;
@property uint32_t address;
@end

@class ZOFirmware;

@interface ZODeviceShared : NSObject<ZODevice>

// Not for public use outside the LUMObackDevice* libraries / frameworks

@property (strong) ZOFirmware *baseFirmware;
@property (strong) ZOFirmware *pluginFirmware;

@property ZODeviceState state;
@property BOOL active;

@property BOOL firmwareUpdateEnabled;
@property BOOL spontaneity;

@property (strong) ZODeviceVersion *version;
@property (strong) NSString *hardwareId;
@property (strong) NSData *softId;
@property (strong) ZODeviceUpdateMetadata *baseMetadata;
@property (strong) ZODeviceUpdateMetadata *pluginMetadata;
@property (strong) ZODeviceBatteryState *batteryState;
@property BOOL quiet;
@property BOOL baseOutOfDate;
@property BOOL pluginOutOfDate;
@property BOOL isUpdateReady;

// Register a handler for a packet sent from the device to the client via the radio.
- (void)registerHandler:(uint16_t) type object:(id)object method:(SEL)method;

// Register a handler for a page of data uploaded from the device to the client via the radio.
- (void)registerUploadHandler:(uint8_t) type object:(id)object method:(SEL)method;

// Enqueue a packet to be sent to the device.
- (void)txPacket:(ZOPacket *)packet;

// Send a packet to the device.
- (void)tx:(NSData *)data;

@property(strong) ZODiagnosticCatalog *diagnosticCatalog;
@property(weak) id<ZODeviceErrorDelegate>errorDelegate;
@property(strong, readonly) NSMutableDictionary *handlerByType;
@property(strong, readonly) NSMutableDictionary *uploadHandlerByType;
@property(strong, readonly) NSMutableData *inputData;
@property(strong, readonly) NSMutableArray *outputDataArray;
@property(strong, readonly) NSMutableData *uploadData;
@property(readonly) uint16_t uploadPage;
@property(readonly) uint16_t uploadLength;

- (BOOL)scan:(NSMutableData *) data;
- (void)send;

- (void)txSetCommunication:(NSDictionary *)communication;
- (void)txCommunicationState;

- (void)txDisconnect;

- (void)onStateOpenBeforeNotify;

@end
