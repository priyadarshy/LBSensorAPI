//
//  MessagesViewController.h
//  LBSensorAPIDemoIOS
//
//  Created by Andreas Hauenstein on 2013-01-23.
//  Copyright (c) 2013 Lumo BodyTech. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LBdefines.h"
#import "LBSensorAPI.h"


@interface MessagesViewController : UIViewController <UITextFieldDelegate>
@property (weak, nonatomic) IBOutlet UITextView *txtMsgs;
- (IBAction)btnCmd:(id)sender;
- (IBAction)btnReq:(id)sender;
@property (weak, nonatomic) IBOutlet UILabel *lblReply;
@property (weak, nonatomic) IBOutlet UITextField *txtCmd;
@property (weak, nonatomic) IBOutlet UITextField *txtReq;
- (IBAction)swpBack:(id)sender;
@property LBSensorAPI *sensor;

- (void) pr:(NSString *)txt;

@end
