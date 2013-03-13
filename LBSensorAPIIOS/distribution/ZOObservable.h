//
//  ZOObservable.h
//  LUMObackDeviceBLE
//
//  Created by Denis Bohm on 7/9/12.
//

#import <Foundation/Foundation.h>

@interface ZOObservable : NSObject

- (id)initWithProtocol:(Protocol *)protocol;
+ (ZOObservable *)observableWithProtocol:(Protocol *)protocol;

- (void)addObserver:(id)observer;
- (void)removeObserver:(id)observer;

@end
