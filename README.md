# LUMOBack Sensor API

![LUMOback Logo](http://unbouncepages-com.s3.amazonaws.com/www.lumoback.com/1y8lm9s-logo-new_4kekoku44hsydibk.png)

## Overview

**LBSensorAPI**, is a static Objective-C library so that you can build custom iOS apps using a LUMOback sensor. The library and header files are availble here on github. Below you will find a small tutorial to get started using the API with a demo iPhone app!

### Project Setup
Follow these steps to setup your XCode project to use the `LBSensorAPI`. Make sure you select iOS device or your iPhone. The API does not work in the simulator; you will get a build error. 

#### Adding the static library.
In your XCode Project copy in the `distribution` folder this contains the static library (.a file), the necessary headers and some resource files. Make sure you have `CoreBluetooth.framework` as part of your project. You should see both `libLBSensorAPIIOS.a` and `CoreBluetooth.Framework` here. 

#### Including Headers
Add the following include line to your code:
	
	#import "LBSensorAPI.h"
	
#### Finding and Connecting to Sensors
Most applications will find it useful to find sensors in range of the iPhone, select one and connect to it. 

##### Start the API

    [LBSensorAPI start];
    
#### Register for in-range sensor updates

Using the `[LBSensorAPI setListSensorsHook:^{}]` you can write a custom block of code to be called when new sensors are in range. In the below example we get the current list of sensors each time using `[LBSensorAPI listSensors]`. The sensors are automatically ordered by descending RSSI i.e. those sensors closest to you will be at the beginning of the array. You might find it helpful to display the UUID or sensor owner in your view in order to select one of these sensors or to refresh the view here. 

```
// Execute the following block when sensors are found. 
[LBSensorAPI setListSensorsHook:^
		{
        // Get a list of all sensors in range right now. 
        NSArray *sensors = [LBSensorAPI listSensors];
        }
];
```

#### Login & Connect to the sensor. 
Once you pick a sensor from the list of in-range and connectable sensors you can attempt to connect to that sensor and login. The timeout (in seconds) specifies how long you will wait for the sensor to connect. In this example we just connect to the sensor that shows the highest signal strength. 

```
LBSensorAPI *mySensor = [sensors objectAtIndex:(0)];
[mySensor loginSyncWithTimeout:5 passwd:mySensor.passwd];
```

#### Listening for Sensor Messages 
Finally, you can start receiving live activity data from the sensor! Register a block of code to be executed like below. You can add your own custom application logic here.

```
	
    // Register a hook for handling 'REC' messages here.
    mySensor.recMsgHook = ^( unsigned int t,
                     		  int angle,
                     		  int lrangle,
                     		  NSString *activity) 
    {
        // Your custom code here. 
        NSLog(@"REC: %d %d %d %@",t, angle, lrangle, activity);
    };
```

In other scenarios you might find it useful to register the generic json handler. 

```
 s.genericJSONhook = ^(NSString *type, NSDictionary *args, NSString *json)
    {
        // Parse some json here and have some fun!
    };
```


#### And more?

Check back as we document the API further. Also take a look at `"LBSensorAPI.h"` to see what other hooks you can register for!

For help. Contact `developer@lumoback.com`

Have fun hacking with your LUMOback Sensor!
