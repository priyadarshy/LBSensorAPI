//
//  AppDelegate.m
//  LBSensorAPIDemoMac
//
//  Created by Andreas Hauenstein on 2013-03-07.
//  Copyright (c) 2013 Lumo BodyTech. All rights reserved.
//

#import "AppDelegate.h"
#import "MasterViewController.h"
#import "MyDoc.h"
#import "LBSensorAPI.h"

//-------------------
static void uncaughtExceptionHandler(NSException *exception)
//-------------------
{
    NSLog(@"Unexpected Exception: %@", exception);
    NSLog(@"Stack Trace: %@", [exception callStackSymbols]);
}

@interface AppDelegate()
//=========================
@property (nonatomic,strong) IBOutlet MasterViewController *masterViewController;
@end

@implementation AppDelegate
//===========================
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    NSSetUncaughtExceptionHandler(&uncaughtExceptionHandler);
    
    // This creates the controller for the xib
    self.masterViewController = [[MasterViewController alloc] initWithNibName:@"MasterViewController" bundle:nil];

    // Start the sensor API.
    // WARNING: You need the IOBluetooth framework.
    // WARNING: You need -ObjC linker flag
    [LBSensorAPI autoConnectOff]; // Don't autoconnect to most recent sensor
    [LBSensorAPI start];
    // Register to be notified when sensors show up
    [LBSensorAPI setListSensorsHook:^{
        NSArray *sensors;
        sensors = [LBSensorAPI listSensors];
        NSMutableArray *viewSensors = [NSMutableArray new];
        NSLog(@"found %ld sensors",[sensors count]);
        for (LBSensorAPI *s in sensors) {
            NSLog (@"uuid: %@ owner: %@",s.uuid,s.owner);
            NSString *title = s.owner;
            if (!title) { title = s.uuid; }
            MyDoc *viewSensor = [[MyDoc alloc] initWithTitle:title sensor:s image:[NSImage imageNamed:@"power.png"]];
            [viewSensors addObject:viewSensor];
        }
        self.masterViewController.tableData = viewSensors;
        [self.masterViewController.tableView reloadData];
    }];
    
    // Window size
    NSRect frame = [self.window frame];
    frame.size.height = 700;
    frame.size.width = 500;
    [self.window setFrame:frame display:YES animate:YES];

    // Add our xib to the main app window
    [self.window.contentView addSubview:self.masterViewController.view];
    self.masterViewController.view.frame = ((NSView*)self.window.contentView).bounds;
}

@end
