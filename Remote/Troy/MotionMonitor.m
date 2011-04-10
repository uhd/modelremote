//
//  MotionMonitor.m
//  Troy
//
//  Created by Max Goedjen on 4/9/11.
//  UHD
//

#import "MotionMonitor.h"


@implementation MotionMonitor

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
        motionManager = [[CMMotionManager alloc] init];
    
        [[UIAccelerometer sharedAccelerometer] setDelegate:self];
        [motionManager startAccelerometerUpdates];
        
        if (motionManager.gyroAvailable) {         
            [motionManager startGyroUpdates];
        }        
    
    }
    
    return self;
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration {
    
    CMRotationRate data = motionManager.gyroData.rotationRate;

    /*NSLog(@"ACCELERATION: %f %f %f", acceleration.x, acceleration.y, acceleration.z);    
    NSLog(@"GYRO: %f %f %f", data.x, data.y, data.z);*/
}

- (void)dealloc
{
    [motionManager dealloc];
    [super dealloc];
}

@end
