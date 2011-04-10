//
//  MotionMonitor.h
//  Troy
//
//  Created by Max Goedjen on 4/9/11.
//  UHD
//

#import <Foundation/Foundation.h>
#import <CoreMotion/Coremotion.h>

@interface MotionMonitor : NSObject <UIAccelerometerDelegate> {
        
    CMMotionManager *motionManager;
    
}

@end
