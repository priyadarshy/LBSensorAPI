//
//  SensorsViewController.h
//  LBSensorAPIDemoIOS
//
//  Created by Andreas Hauenstein on 2013-01-23.
//  Copyright (c) 2013 Lumo BodyTech. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SensorsViewController : UIViewController <UITableViewDelegate, UITableViewDataSource> 
@property (weak, nonatomic) IBOutlet UITableView *sensorTable;

@end
