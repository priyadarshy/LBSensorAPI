//
//  MasterViewController.h
//  LBSensorAPIDemoMac
//
//  Created by Andreas Hauenstein on 2013-03-07.
//  Copyright (c) 2013 Lumo BodyTech. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "LBSensorAPI.h"

@interface MasterViewController : NSViewController <NSTableViewDelegate,NSTableViewDataSource>


@property LBSensorAPI *currentSensor;

// TableView data source
@property NSMutableArray *tableData;

// IB stuff
@property IBOutlet NSTextView *textView;
@property IBOutlet NSTableView *tableView;
@property IBOutlet NSTextField *lblStatus;
- (IBAction)btnDisconnect:(id)sender;

@end
