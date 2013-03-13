//
//  ZOExecutor.h
//  LUMObackDeviceBLE
//
//  Created by Denis Bohm on 7/8/12.
//

#import "ZOObservable.h"

typedef enum {
    ZOExecutorTaskStateReady,
    ZOExecutorTaskStateSuspending,
    ZOExecutorTaskStateSuspendable,
    ZOExecutorTaskStateSuspended
} ZOExecutorTaskState;

@interface ZOExecutorTask : NSObject

@property double priority;

- (void)start;
- (void)suspending;
- (void)suspend;
- (void)resume;
- (void)cancel;

@property NSUInteger order;
@property ZOExecutorTaskState state;

@end

@class ZOExecutor;

@protocol ZOExecutorDelegate <NSObject>
@optional
- (void)executor:(ZOExecutor *)executor submitted:(ZOExecutorTask *)task;
- (void)executor:(ZOExecutor *)executor starting:(ZOExecutorTask *)task;
- (void)executor:(ZOExecutor *)executor suspending:(ZOExecutorTask *)task;
- (void)executor:(ZOExecutor *)executor suspended:(ZOExecutorTask *)task;
- (void)executor:(ZOExecutor *)executor resuming:(ZOExecutorTask *)task;
- (void)executor:(ZOExecutor *)executor canceling:(ZOExecutorTask *)task;
- (void)executor:(ZOExecutor *)executor completed:(ZOExecutorTask *)task;
@end

@interface ZOExecutorObservable : ZOObservable <ZOExecutorDelegate>
@end

@interface ZOExecutor : NSObject

@property (strong, readonly) ZOExecutorObservable *observable;
@property (strong, readonly) ZOExecutorTask *currentTask;
@property (readonly) BOOL isIdle;

- (void)submit:(ZOExecutorTask *)task;
- (void)completed:(ZOExecutorTask *)task;
- (void)cancel:(ZOExecutorTask *)task;
- (void)cancelAll;

// override this method to do extra work to make a task suspendable -denis
- (void)suspendingCurrentTask;

- (void)currentTaskIsNowSuspendable;

@end
