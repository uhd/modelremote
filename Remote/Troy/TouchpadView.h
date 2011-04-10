//
//  TouchpadView.h
//  Troy
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#import <Foundation/Foundation.h>

@protocol TouchpadDelegate <NSObject>

- (void)touchpadDidBeginTouchPoint:(CGPoint)point;
- (void)touchpadDidTouchPoint:(CGPoint)point;
- (void)touchpadDidEndTouchPoint:(CGPoint)point;
- (void)touchpadDidPinchWithScale:(float)scale;

@end

@interface TouchpadView : UIImageView {
    
    id delegate;
    
}

@property (nonatomic, retain) id<TouchpadDelegate> delegate;

- (void)configure;

@end
