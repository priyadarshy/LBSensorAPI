//
//  MyData.m
//  LBSensorAPIDemoMac
//
//  Created by Andreas Hauenstein on 2013-03-07.
//  Copyright (c) 2013 Lumo BodyTech. All rights reserved.
//

#import "MyData.h"

@implementation MyData

- (id)initWithTitle:(NSString*)title sensor:(LBSensorAPI*)theSensor {
    if ((self = [super init])) {
        self.title = title;
        self.sensor = theSensor;
    }
    return self;
}

@end
