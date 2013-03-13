
//
//  SensorsViewController.m
//  LBSensorAPIDemoIOS
//
//  Created by Andreas Hauenstein on 2013-01-23.
//  Copyright (c) 2013 Lumo BodyTech. All rights reserved.
//

#import "AppDelegate.h"
#import "SensorsViewController.h"
#import "LBdefines.h"
#import "LBSensorAPI.h"
#import "UIBAlertView.h"



@interface SensorsViewController ()

@property NSMutableArray *tableData;
@property AppDelegate *appDelegate;

@end

@implementation SensorsViewController

//--------------------------------
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
//--------------------------------
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"Sensors", @"Sensors");
        self.tabBarItem.image = [UIImage imageNamed:@"first"];
    }
    return self;
}
							
//--------------------------------
- (void)viewDidLoad
//--------------------------------
{
    [super viewDidLoad];
    self.appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	self.tableData = [NSMutableArray array]; // Objs in the tableview
    [self refreshSensorList];
                                                                               
    [LBSensorAPI setListSensorsHook:^void() { [self refreshSensorList]; }];  }  // <<<<<<<<<<<<< get notified of sensors in the vicinity

//--------------------------------
- (void)didReceiveMemoryWarning
//--------------------------------
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


//------------------------------
//--- Table View Data Source ---
//------------------------------

//----------------------------------
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
//----------------------------------
{
    return 1;
}

//----------------------------------
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
//----------------------------------
{
    return self.tableData.count;
}

// Gets the text for display in the tableview
//----------------------------------
- (UITableViewCell *)tableView:(UITableView *)tableView
         cellForRowAtIndexPath:(NSIndexPath *)indexPath
//----------------------------------
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"Cell"];
    if (nil == cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                      reuseIdentifier:@"Cell"];
    }
    LBSensorAPI *s = [self.tableData objectAtIndex:indexPath.row];
    NSString *tstr = s.owner;
    if (!tstr) {
        tstr = s.uuid;
    }
    cell.textLabel.text = tstr;
    return cell;
}

// Override to support conditional editing of the table view.
//----------------------------------
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
//----------------------------------
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}

//----------------------------------
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
//----------------------------------
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        [self.tableData removeObjectAtIndex:indexPath.row];
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
    }
}

//----------------------------------
- (bool)logIntoSensor:(LBSensorAPI *)s
//----------------------------------
{
    if ([s loginSyncWithTimeout:5 passwd:s.passwd]) {
        return YES;
    }
    else {
        return NO;
    }
} // logIntoSensor()

//---------------------------
//--- Table View Delegate ---
//---------------------------

// Gets called when user selects a sensor.
// Log into sensor, prompt for passwd if unknown or failed.
//----------------------------------
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
//----------------------------------
{
    LBSensorAPI *s = [self.tableData objectAtIndex:indexPath.row];
    
    UIActivityIndicatorView *ac = [[UIActivityIndicatorView alloc]
                                   initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    tableView.tableHeaderView = ac;
    bool success = NO;
    do { // just to break out of it
        // Try to connect
        UIAlertView *progressView = [self progressAlert:@"Connecting..."];
        if (![s connectSyncWithTimeout:10]) {
            [self error:@"Could not connect"];
            [progressView dismissWithClickedButtonIndex:0 animated:YES];
            break;
        }
        // User wants to log in. Get owner from sensor if not known.
        if (!s.owner) {
            [s getOwner];
        }
        if (!s.owner) {
            [s disconnect];
            [progressView dismissWithClickedButtonIndex:0 animated:YES];
            [self error:@"Failed to get owner"];
            break;
        }
        if (EQS(s.owner,@"NOT_OWNED")) {
            [s disconnect];
            [progressView dismissWithClickedButtonIndex:0 animated:YES];
            [self error:@"Sensor has no owner"];
            break;
        }
        if (s.passwd) {
            success = [self logIntoSensor:s];
            if (success) {
                [progressView dismissWithClickedButtonIndex:0 animated:YES];
                [self.appDelegate showMessagesView:s];
                return;
            }
        }
        
        if (!success || !s.passwd) { // Passwd not known or wrong
            [progressView dismissWithClickedButtonIndex:0 animated:YES];
            UIBAlertView *alert = [[UIBAlertView alloc] initWithTitle:@"Please enter password"
                                                              message:s.owner
                                                    cancelButtonTitle:nil
                                                    otherButtonTitles:@"Ok", nil];
            alert.activeAlert.alertViewStyle = UIAlertViewStyleSecureTextInput;
            [alert
             showWithDismissHandler:^(NSInteger selectedIndex, BOOL didCancel)
             {
                 s.passwd = [alert.activeAlert textFieldAtIndex:0].text;
                 bool success = [self logIntoSensor:s];
                 if (success) {
                     [self.appDelegate showMessagesView:s];
                 }
                 else {
                     s.passwd = nil;
                     [s disconnect];
                     [self error:s.lastError];
                     
                 }
             }
             ];
        } // if (passwd not known)
    } while (0);
} // didSelectRowAtIndexPath()

//-----------------
//--- IBActions ---
//-----------------

//--------------------------
//--- Non callback stuff ---
//--------------------------

//-------------
- (void) error:(NSString*)err
//-------------
{
    UIAlertView *alert = [[UIAlertView alloc]
                      initWithTitle: @"Error"
                      message: err
                      delegate: nil
                      cancelButtonTitle:@"OK"
                      otherButtonTitles:nil];
    [alert show];
}

//---------------------------------------------------
- (UIAlertView *) progressAlert:(NSString*) message
//---------------------------------------------------
{
    UIAlertView *alert;
    alert = [[UIAlertView alloc] initWithTitle:message
                                       message:nil
                                      delegate:nil
                             cancelButtonTitle:nil
                             otherButtonTitles: nil];
    [alert show];
    UIActivityIndicatorView *indicator =
    [[UIActivityIndicatorView alloc]
     initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
    
    // Adjust the indicator so it is up a few pixels from the bottom of the alert
    indicator.center = CGPointMake(alert.bounds.size.width / 2, alert.bounds.size.height - 50);
    [indicator startAnimating];
    [alert addSubview:indicator];
    return alert;
} // progressAlerrt()


// Display sensors in the vicinity.
// Called from listSensorsHook.
//--------------------------
- (void)refreshSensorList
//--------------------------
{
    NSArray* sensors = [LBSensorAPI listSensors];
    self.tableData = [NSMutableArray new];
    for (LBSensorAPI *s in sensors) {
       //if (s.owner) {
            [self.tableData addObject:s];
       // }
    }
    [self.sensorTable reloadData];
    //LBSensorAPI *s = [LBSensorAPI autoConnect];
    //if (s) {
    //    [self.appDelegate showMessagesView:s];
    //}
} // refreshSensorList()

@end
