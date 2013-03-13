//
//  LBSensorAPI.h
//  AHNAPIDev
//
//  Created by Andreas Hauenstein on 2013-02-20.
//  Copyright (c) 2013 Lumo BodyTech. All rights reserved.
//

// Basic principle:
//====================
// LBSensorAPI automatically keeps an updated list of sensors in range.
// You can get at the list with
// [LBSensorAPI listSensors]
// The elements of the list are of type LBSensorAPI.
// Then pick one, connect, do whatever.
// The class methods manage all sensors in range,
// the instance methods manage each individual sensor.
// You NEVER have to [[alloc] init] an LBSensorAPI.
// You ALWAYS take it from [LBSensorAPI listSensors].

@interface LBSensorAPI : NSObject
//======================

//================
//=== Typedefs ===
//================
// Hook for any JSON Message from sensor
typedef void (^LBJSONHook)(NSString *type, NSDictionary *args);
// Hook for sensor reply to a request
typedef void (^LBReplyHook)(NSString *reply, NSString *arg);
// Hook type for sensor connection,login,get info attempt
typedef void (^LBSuccessHook)(bool success);


// Generic catalog of actions
typedef enum { ADD=1, REMOVE=2, CLEAR=3, GET=4, SET=5, ON=6, OFF=7} LBAction;

// Take care of a rec message
typedef void(^LBrecMsgHook) (
unsigned int t,
int angle,
int lrangle,
NSString *activity);
// Take care of any JSON message
typedef void(^LBgenericJSONhook) (NSString *type, NSDictionary *args, NSString *json);

//============================
//=== The Hooks and Timers ===
//============================
// Hooks for standard events. Set these as you wish.
@property (copy) LBrecMsgHook recMsgHook;  // you really need this
@property (copy) LBgenericJSONhook genericJSONhook; // mostly for debugging

// Timer and hook for The One currently running request to the sensor.
// A request is anything that expects a reply.
// Set automatically by request: withArgs:
// Example: GET_OWNER may have the reply GET_OWNER:joe@schmoe or NOT_OWNED.
@property NSArray *expectedReplies; // Strings. The possible replies.
@property NSTimer *replyTimer; // Timeout
@property (copy) LBReplyHook replyHook;

// Connection timer and hook
@property NSTimer *connectTimer;
// Hook to call when connection succeeds. API internal use.
@property (copy) LBSuccessHook connectHook;

//=========================
//=== Sensor properties ===
//=========================
@property NSString *uuid;
@property NSString *sensorId;
@property NSString *hardwareId;
@property NSString *owner;
@property NSString *passwd;
@property NSNumber *signalStrength;
@property NSString *pluginVersion;
@property NSString *baseVersion;
@property NSString *batteryState;
@property (strong) NSDate *lastSeen;

// The commands the sensor accepts.
// Commands are JSON messages to the sensor
// that do not have a reply.
// {@"STBLR":{@"args":[n_angle]},@"BUZZ":...}
// if (![self.command objectForKey:@"SOMECMD"]) @"oops";
// Arguments n_* are numeric, s_* means string
@property NSDictionary *commands;

// The requests the sensor accepts.
// Requests are JSON messages to the sensor
// that have a reply.
@property NSDictionary *requests;

@property
enum {
DISCONNECTED=0,
CONNECTING=1, CONNECTED=2,
GETTING_OWNER=3, GOT_OWNER=4,
LOGGING_IN=5, LOGGED_IN=6,
READY=7, DISCONNECTING=8
} sensorState;
@property NSString *lastError;

//=====================
//=== Class Methods ===
//=====================
+ (void) start;
+ (void) stop;
+ (void) setAutoConnectSensor:(LBSensorAPI *)s;
+ (void) autoConnectOn;
+ (void) autoConnectOff;
+ (LBSensorAPI *) autoConnect;
+ (NSArray *) listSensors;
+ (void) disconnectAll;
+ (void) setListSensorsHook:(void(^)())theHook;

+ (NSTimeInterval) updateInterval:(LBAction)action interval:(NSTimeInterval)theInterval;
//+ (NSTimeInterval) connectionTimeout:(LBAction)action timeout:(NSTimeInterval)theTimeout;
+ (NSTimeInterval) requestTimeout:(LBAction)action timeout:(NSTimeInterval)theTimeout;
//+ (NSTimeInterval) inactiveTimeout:(LBAction)action timeout:(NSTimeInterval)theTimeout;

//======================
//=== Object Methods ===
//======================

// These are for application use
- (bool) connectSyncWithTimeout:(NSTimeInterval)theTimeout; // hook:(void(^)(bool success))theHook;
- (void) connectWithTimeout:(NSTimeInterval)theTimeout hook:(void(^)(bool success))theHook;
- (void) shouldReconnect:(LBAction)action; // ON or OFF
- (bool) loginSyncWithTimeout:(NSTimeInterval)theTimeout passwd:(NSString *)passwd;
- (void) getOwner;
- (void) disconnect;
- (bool) command:(NSString*)theCommand
        withArgs:(NSArray*)theArgs
           force:(bool)forceFlag;
- (bool) request:(NSString*)theRequest
            hook:(void(^)(NSString *reply, NSString *arg))theHook;
- (bool) requestSync:(NSString*)theRequest
                hook:(void(^)(NSString *reply, NSString *arg))theHook;
- (NSString *) description;
- (NSString *) printState;


@end
