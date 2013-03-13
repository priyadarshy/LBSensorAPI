//
//  MessagesViewController.m
//  LBSensorAPIDemoIOS
//
//  Created by Andreas Hauenstein on 2013-01-23.
//  Copyright (c) 2013 Lumo BodyTech. All rights reserved.
//

#import "AppDelegate.h"
#import "MessagesViewController.h"
#import "LBdefines.h"
#import "LBUtil.h"


@interface MessagesViewController ()
@property AppDelegate *appDelegate;
@end

@implementation MessagesViewController 

//-----------------------------
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
//-----------------------------
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"Second", @"Second");
        self.tabBarItem.image = [UIImage imageNamed:@"second"];
    }
    return self;
} // initWithNibName()
							
//-----------------------------
- (void)viewDidLoad
//-----------------------------
{
    [super viewDidLoad];

    self.appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	// Make sure we catch textfield events
    [self.txtCmd setDelegate:self];
    [self.txtReq setDelegate:self];
    
} // viewDidLoad()

//-----------------------------
- (void)didReceiveMemoryWarning
//-----------------------------
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

// Print a string at the end of the textview, with a newline, and scroll
//-----------------------------
- (void) pr:(NSString *)txt
//-----------------------------
{
    static NSMutableArray *msgs;
    if (!msgs) { msgs = [NSMutableArray new]; }
    
    [msgs addObject:txt];
    // We only do up to 200 lines
    while ([msgs count] > 200) {
        [msgs removeObjectAtIndex:0];
    }
    self.txtMsgs.text = [msgs componentsJoinedByString:@"\n"];
    NSUInteger length = self.txtMsgs.text.length;
    self.txtMsgs.selectedRange = NSMakeRange(length, 0);
    //if (self.autoScrollSwitch.isOn)
    //    [self.textView scrollRangeToVisible:NSMakeRange(length, 0)];
} // pr()

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

//---------------------------
//--- UI Delegate Methods ---
//---------------------------

//-----------------------------------------------------
- (BOOL)textFieldShouldReturn:(UITextField *)textField
//-----------------------------------------------------
{
	[textField resignFirstResponder]; // Hide keyboard when clicking done
	return YES;
}

//-----------------
//--- IBActions ---
//-----------------

// Button to send command to sensor
// Example commands:
// @"BUZZ"
// @"STBLR:10"
//-----------------------------
- (IBAction)btnCmd:(id)sender
//-----------------------------
{
    NSString *str = self.txtCmd.text;
    NSString *cmd; NSArray *args;
    if ([str rangeOfString:@":"].location != NSNotFound) {
        NSArray *cmdAndArgs = [str componentsSeparatedByString:@":"];
        cmd = cmdAndArgs[0];
        NSString *argstr = cmdAndArgs[1];
        args = [argstr componentsSeparatedByString:@","];
    }
    else {
        cmd = str;
        args = nil;
    }
    if (![self.sensor command:cmd withArgs:args force:NO]) {  // <<<<<<<<<< This sends a command to the sensor
        [self error:self.sensor.lastError];
    }
} // btnCmd()

// Button to send request to sensor
//-----------------------------
- (IBAction)btnReq:(id)sender
//-----------------------------
{
    NSString *req = self.txtReq.text;
    if (![self.sensor request:req              // <<<<<<<<<<<< This sends a request to the sensor
                         hook:^(NSString *reply, NSString *arg) {
                             self.lblReply.text = SPR(@"%@:%@",reply,arg);
                         }
          ])
    {
        [self error:self.sensor.lastError];
    }
} // btnReq()

// Swipe back to the sensors view
//--------------------------------
- (IBAction)swpBack:(id)sender
//--------------------------------
{
    [self.sensor shouldReconnect:OFF];
    //[LBSensorAPI disconnectAll];
    [self.sensor disconnect];
    [LBSensorAPI autoConnectOff];
    //[LBSensorAPI start];
    [self.appDelegate showSensorsView];
} // swpBack()

@end
