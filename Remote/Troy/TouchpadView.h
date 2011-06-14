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
- (void)touchpadDidBeginPinch;
- (void)touchpadDidPinchWithScale:(float)scale;
- (void)touchpadDidEndPinch;
- (void)touchpadDidBeginPan:(CGPoint)point;
- (void)touchpadDidPan:(CGPoint)point;
- (void)touchpadDidEndPan:(CGPoint)point;

@end

@interface TouchpadView : UIImageView {
    
    id delegate;
    
}

@property (nonatomic, retain) id<TouchpadDelegate> delegate;

- (void)configure;

@end
