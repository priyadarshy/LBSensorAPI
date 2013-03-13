//
//  AppDelegate.h
//  LBSensorAPIDemoIOS
//
//  Created by Andreas Hauenstein on 2013-01-23.
//  Copyright (c) 2013 Lumo BodyTech. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LBdefines.h"
#import "MessagesViewController.h"
#import "SensorsViewController.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate, UITabBarControllerDelegate>

//--- Boilerplate ---
@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) UITabBarController *tabBarController;

//---- Our views ---
@property SensorsViewController *sensorsViewController;
@property MessagesViewController *messagesViewController;

- (void) showMessagesView:(LBSensorAPI *)s;
- (void) showSensorsView;


@end
