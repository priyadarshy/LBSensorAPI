//
//  MyDoc.m
//  LBSensorAPIDemoMac
//
//  Created by Andreas Hauenstein on 2013-03-07.
//  Copyright (c) 2013 Lumo BodyTech. All rights reserved.
//

#import "MyDoc.h"
#import "MyData.h"

@implementation MyDoc

- (id)initWithTitle:(NSString*)title sensor:(LBSensorAPI*)theSensor image:(NSImage *)theImage
{
    if ((self = [super init])) {
        self.data = [[MyData alloc] initWithTitle:title sensor:theSensor];
        self.image = theImage;
    }
    return self;
}

@end
