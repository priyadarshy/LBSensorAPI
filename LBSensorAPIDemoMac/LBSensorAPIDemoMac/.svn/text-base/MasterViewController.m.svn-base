//
//  MasterViewController.m
//  LBSensorAPIDemoMac
//
//  Created by Andreas Hauenstein on 2013-03-07.
//  Copyright (c) 2013 Lumo BodyTech. All rights reserved.
//

#import "MasterViewController.h"
#import "MyDoc.h"
#import "MyData.h"
#import "LBdefines.h"

@interface MasterViewController ()

@end

@implementation MasterViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

// Helpers
//=============

//------------------------------
- (void)alert:(NSString *)msg
//------------------------------
{
    NSAlert *alert = [NSAlert alertWithMessageText:msg
                                     defaultButton:@"OK"
                                   alternateButton:nil
                                       otherButton:nil
                         informativeTextWithFormat:@""];
    [alert runModal];
} // alert

//------------------------------
- (NSString *)promptForPasswd:(NSString *)msg
//------------------------------
{
    NSAlert *alert = [NSAlert alertWithMessageText:msg
                                     defaultButton:@"Login"
                                // alternateButton:@"Cancel"
                                   alternateButton:nil
                                       otherButton:nil
                         informativeTextWithFormat:@""];
    
    NSSecureTextField *input = [[NSSecureTextField alloc] initWithFrame:NSMakeRect(0, 0, 200, 24)];
    [input setStringValue:@""];
    [alert setAccessoryView:input];
    NSInteger button = [alert runModal];
    if (button == NSAlertDefaultReturn) {
        [input validateEditing];
        return [input stringValue];
    } else if (button == NSAlertAlternateReturn) {
        return nil;
    } else {
        NSAssert1(NO, @"Invalid input dialog button %ld", button);
        return nil;
    }
} // promptForPasswd

// Write a string to the textview
//------------------------------
- (void)pr:(NSString *)msg
//------------------------------
{
    static NSMutableArray *msgs;
    if (!msgs) { msgs = [NSMutableArray new]; }
    
    // We only do up to 200 lines
    while ([msgs count] > 200) {
        [msgs removeObjectAtIndex:[msgs count]-1];
    }
    [msgs insertObject:msg atIndex:0];
    self.textView.string = [msgs componentsJoinedByString:@"\n"];
    NSUInteger length = [self.textView.string length];
    self.textView.selectedRange = NSMakeRange(length, 0);
} // pr


// NSTableViewDataSource
//=========================
//-----------------
- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
//-----------------
{
    // Get a new ViewCell
    NSTableCellView *cellView = [tableView makeViewWithIdentifier:tableColumn.identifier owner:self];
    
    // Since this is a single-column table view, this would not be necessary.
    // But it's a good practice to do it in order by remember it when a table is multicolumn.
    if( [tableColumn.identifier isEqualToString:@"OnlyColumn"] )
    {
        MyDoc *viewSensor = [self.tableData objectAtIndex:row];
        cellView.imageView.image = viewSensor.image;
        cellView.textField.stringValue = viewSensor.data.title;
        return cellView;
    }
    return cellView;
}


//-----------------
- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView
//-----------------
{
    return [self.tableData count];
}

// NSTableViewDelegate
//=======================

//-----------------
-(BOOL)tableView:(NSTableView *)tableView shouldSelectRow:(NSInteger)row
//-----------------
{
    // This has to return immediately to highlight the cell.
    // Therefore, we delay the time consuming stuff into the future.
    [self performSelector:@selector(connect2sensor:) withObject:@(row) afterDelay:0.1];
    return YES;
}

//------------------------------------------
-(void) connect2sensor:(NSNumber *) theRow
//------------------------------------------
{
    NSInteger row = [theRow integerValue];
    //NSTableCellView *cellView = [self.tableView viewAtColumn:0 row:row makeIfNecessary:false];
    //[cellView se
    //[cellview ba]
    // Get the sensor
    MyDoc *doc = self.tableData[row];
    LBSensorAPI *s = doc.data.sensor;
    NSLog (@"trying sensor %@",s.uuid);
    [LBSensorAPI stop]; // Have to stop scanning before connect (CSR dongle)

    do {
        self.currentSensor = s;
        self.lblStatus.stringValue = @"Status: Connecting";
        if (![s connectSyncWithTimeout:10] ) {
            break;
        }
        self.lblStatus.stringValue = @"Status: Connected";
        self.lblStatus.stringValue = @"Status: Getting owner";
        __block NSString *owner = nil;
        [s requestSync:@"OWNER_GET" hook:^(NSString *reply, NSString *arg) {
            if (reply) {
                owner = arg;
            }
        }];
        if (!owner) {
            self.lblStatus.stringValue = @"Status: Getting owner failed";
            break;
        }
        NSString *passwd = [self promptForPasswd:SPR(@"Enter password for %@",owner)];
        if (![s loginSyncWithTimeout:10 passwd:passwd]) {
            self.lblStatus.stringValue = @"Status: Login failed";
            break;
        }
        self.lblStatus.stringValue = @"Status: Logged in";
        // We got a sensor connection. Set the message hook.
        s.genericJSONhook = ^(NSString *type, NSDictionary *args, NSString *json) {
            [self pr:json];
        };
        return;
    } while (0);
    [s disconnect];
    self.currentSensor = nil;
   // return NO;
} // connect2sensor()

// IBActions
//==============
//-------------------------------------
- (IBAction)btnDisconnect:(id)sender
//-------------------------------------
{
    self.lblStatus.stringValue = @"Status: Disconnecting";
    [self.currentSensor disconnect];
    self.currentSensor = nil;
    [LBSensorAPI start];
    self.lblStatus.stringValue = @"Status: Scanning";
    // Restart scanning
    
}

@end

