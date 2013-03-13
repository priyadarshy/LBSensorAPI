//
//  AppDelegate.m
//  LBSensorAPIDemoIOS
//
//  Created by Andreas Hauenstein on 2013-01-23.
//  Copyright (c) 2013 Lumo BodyTech. All rights reserved.
//

// WARNING: You need -ObjC linker flag

#import "AppDelegate.h"
#import "SensorsViewController.h"
#import "MessagesViewController.h"
#import "LBdefines.h"
#import "LBSensorAPI.h"


@implementation AppDelegate

static
void uncaughtExceptionHandler(NSException *exception) {
    NSLog(@"Unexpected Exception: %@", exception);
    NSLog(@"Stack Trace: %@", [exception callStackSymbols]);
}

//NSObject <UIApplicationDelegate> *g_appDelegate;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    //--- App specific stuff
    NSSetUncaughtExceptionHandler(&uncaughtExceptionHandler);
    //g_appDelegate =  [ [ UIApplication sharedApplication ] delegate ];

    //--- Boilerplate ---
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    self.sensorsViewController = [[SensorsViewController alloc] initWithNibName:@"SensorsViewController" bundle:nil];
    self.messagesViewController = [[MessagesViewController alloc] initWithNibName:@"MessagesViewController" bundle:nil];
    self.tabBarController = [[UITabBarController alloc] init];
    self.tabBarController.viewControllers = @[self.sensorsViewController, self.messagesViewController];
    self.window.rootViewController = self.tabBarController;
    [self.window makeKeyAndVisible];
    
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    
    //[LBSensorAPI autoConnectOn];
    [LBSensorAPI start]; // Start Lumo sensor discovery
    
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    [LBSensorAPI disconnectAll];
}

/*
// Optional UITabBarControllerDelegate method.
- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController
{
}
*/

/*
// Optional UITabBarControllerDelegate method.
- (void)tabBarController:(UITabBarController *)tabBarController didEndCustomizingViewControllers:(NSArray *)viewControllers changed:(BOOL)changed
{
}
*/


//---------------------------
- (void) showSensorsView
//---------------------------
{
    self.tabBarController.selectedIndex = 0;
}

//---------------------------
- (void) showMessagesView:(LBSensorAPI *)s
//---------------------------
{
    //[LBSensorAPI stop];
    //[LBSensorAPI autoConnectOn];
    //[LBSensorAPI setAutoConnectSensor:s];
    self.tabBarController.selectedIndex = 1;
    self.messagesViewController.sensor = s;
    [s shouldReconnect:ON];
    // Register our json message handlers
    s.recMsgHook = ^( unsigned int t,
                     int angle,
                     int lrangle,
                     NSString *activity) {
        NSString *tstr = SPR(@"REC: %d %d %d %@",t,angle,lrangle,activity);
        [self.messagesViewController pr:tstr];
    };
    // Only print raw messages
    s.genericJSONhook = ^(NSString *type, NSDictionary *args, NSString *json)
    {
        // Do not print all raw messages. There are too many.
        static unsigned int i = 0;
        if ([json rangeOfString:@"|"].location != NSNotFound) { // raw mode message
            if (i++ % 4 == 0) {
                [self.messagesViewController pr:json];
            }
        }
    };
    
} // showMessagesView()


@end
