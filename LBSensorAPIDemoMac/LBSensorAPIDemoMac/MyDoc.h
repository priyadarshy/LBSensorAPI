//
//  MyDoc.h
//  LBSensorAPIDemoMac
//
//  Created by Andreas Hauenstein on 2013-03-07.
//  Copyright (c) 2013 Lumo BodyTech. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LBSensorAPI.h"

@class MyData;

@interface MyDoc : NSObject

@property (strong) MyData *data;
@property (strong) NSImage *image;

- (id)initWithTitle:(NSString*)title sensor:(LBSensorAPI*)theSensor image:(NSImage *)theImage;

@end
