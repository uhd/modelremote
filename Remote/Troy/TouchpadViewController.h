//
//  TouchpadViewController.h
//  Troy
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#import <UIKit/UIKit.h>
#import "TouchpadView.h"
#import "MotionMonitor.h"
#import "CommunicationCenter.h"

@interface TouchpadViewController : UIViewController <TouchpadDelegate, CommunicationCenterDelegate> {
    
    MotionMonitor *motionMonitor;
    UILabel *statusLabel;
    
    float deviceScale;
    
}

@end
