//
//  ZODeviceMonitor.h
//  LUMObackTool
//
//  Created by Denis Bohm on 12/18/11.
//

#import "ZODevice.h"

#import <Foundation/Foundation.h>

@protocol ZODeviceMonitorDelegate

- (void)deviceDidConnect:(id<ZODevice>)device;
- (void)deviceDidDisconnect:(id<ZODevice>)device;

@end

@protocol ZODeviceMonitor <NSObject>

@property (weak) id<ZODeviceMonitorDelegate> delegate;
@property BOOL active;
@property (strong) NSString *autoconnectDeviceUUID;

- (void)start;
- (void)stop;

- (void)simulate;

@end
