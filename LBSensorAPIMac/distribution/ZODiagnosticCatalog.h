//
//  ZODiagnosticCatalog.h
//  LUMObackDeviceMac
//
//  Created by Denis Bohm on 1/29/12.
//

#import <Foundation/Foundation.h>

typedef enum {
    BOOL_TYPE,
    UINT8_TYPE,
    UINT16_TYPE,
    UINT32_TYPE,
    FLOAT16_TYPE,
    FLOAT32_TYPE,
    FLOAT64_TYPE,
    TIME4_TYPE,
    TIME6_TYPE,
    DURATION4_TYPE,
    DURATION6_TYPE,
    BENCHMARK_TYPE,
    STRING_TYPE,
    UTF8_TYPE
} ZODiagnosticArgInfoType;

@interface ZODiagnosticArgInfo : NSObject
@property(strong) NSString *name;
@property ZODiagnosticArgInfoType type;
@end

@interface ZODiagnosticInfo : NSObject
@property uint16_t type;
@property(strong) NSString *typeName;
@property(strong) NSArray *argsInfo;
@end

@interface ZODiagnosticCatalog : NSObject

@property(strong) NSDictionary *infoByType;

+ (ZODiagnosticCatalog *)instance;

- (void)setCatalog:(NSString *)content;

- (ZODiagnosticInfo *)getInfo:(uint16_t)type;

- (NSString *)decodeToJson:(NSTimeInterval)time type:(uint16_t)type args:(NSData *)args;

@end
