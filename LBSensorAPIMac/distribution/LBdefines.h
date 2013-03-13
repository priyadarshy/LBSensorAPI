//
//  LBdefines.h
//  Author: AHN, Jan 2013

// Collection of generally useful macros

// Simulation
// #define LBSENSOR LBSensorBase

// The real thing
#define LBSENSOR LBSensorAPI

// String abbreviations
#define STR(x) [@(x) stringValue]
#define APS(A,B) [(A) stringByAppendingString:(B)]
#define EQS(A,B) [(A) isEqualToString:(B)]
#define SPR(format,args...) [NSString stringWithFormat: format, ## args]

// Number abbreviatons
#define EQN(A,B) [(A) isEqualToNumber:(B)]

// Logging
#define LOG_ALL 1
#define LOG_ERRORS 2
// Set this to LOG_ERRORS in release
#define LB_LOG_LEVEL LOG_ALL
// Logging macros
#define LB_ERR(format,args...) if(LB_LOG_LEVEL<=LOG_ERRORS){NSLog(@"%@:%d %s ERROR:" format, [@(__FILE__) lastPathComponent], __LINE__, __func__, ## args);}
#define LB_LOG(format,args...) if(LB_LOG_LEVEL<=LOG_ALL){NSLog(@"%@:%d %s LOG:" format, [@(__FILE__) lastPathComponent], __LINE__, __func__, ## args);}

