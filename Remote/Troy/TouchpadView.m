//
//  TouchpadView.m
//  Troy
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#import "TouchpadView.h"


@implementation TouchpadView

@synthesize delegate;

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.

    }
    
    return self;
}

- (BOOL)canBecomeFirstResponder {
	return YES;
}

- (void)dealloc
{
    [super dealloc];
}

- (void)configure {

    self.image = [UIImage imageNamed:@"iPadControlPadBackground.png"];
    self.userInteractionEnabled = YES;
    self.multipleTouchEnabled = YES;
    UIPinchGestureRecognizer *twoFingerPinch = 
    [[[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(twoFingerPinch:)] autorelease];
    [self addGestureRecognizer:twoFingerPinch];

}

#pragma mark touch interpretation
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    
	CGPoint point = [[touches anyObject] locationInView:nil];
    [delegate touchpadDidBeginTouchPoint:point];
    
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
	
    if ([touches count] == 1) {

        CGPoint point = [[touches anyObject] locationInView:nil];
        [delegate touchpadDidTouchPoint:point];

    }
	
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	
    CGPoint point = [[touches anyObject] locationInView:nil];
    [delegate touchpadDidEndTouchPoint:point];

}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
		
}

- (void)twoFingerPinch:(UIPinchGestureRecognizer *)recognizer {
    
    [delegate touchpadDidPinchWithScale:recognizer.scale];
    
}

@end
