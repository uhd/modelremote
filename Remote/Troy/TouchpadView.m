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

    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        self.image = [UIImage imageNamed:@"iPadControlPadBackground.png"];
    } else {
        self.image = [UIImage imageNamed:@"iPhoneControlPadBackground.png"];
    }
    
    self.userInteractionEnabled = YES;
    self.multipleTouchEnabled = YES;
    UIPinchGestureRecognizer *twoFingerPinch = 
    [[[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(twoFingerPinch:)] autorelease];
    [self addGestureRecognizer:twoFingerPinch];

}

#pragma mark touch interpretation
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    
    if ([[touches allObjects] count] == 1) {
        CGPoint point = [[touches anyObject] locationInView:nil];
        [delegate touchpadDidBeginTouchPoint:point];
    }
        
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
	
    if ([touches count] == 1) {
        CGPoint point = [[touches anyObject] locationInView:nil];
        [delegate touchpadDidTouchPoint:point];
    }
	
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	
    if ([[touches allObjects] count] == 1) {
        CGPoint point = [[touches anyObject] locationInView:nil];
        [delegate touchpadDidEndTouchPoint:point];
    }
    
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {

}

- (void)twoFingerPinch:(UIPinchGestureRecognizer *)recognizer {
    
    switch (recognizer.state) {
        case UIGestureRecognizerStateBegan:
            [delegate touchpadDidBeginPinch];
            break;
            
        case UIGestureRecognizerStateChanged:
            [delegate touchpadDidPinchWithScale:recognizer.scale];
            break;
            
        case UIGestureRecognizerStateEnded:
            [delegate touchpadDidEndPinch];
            break;
            
        default:
            break;
    }
    
}

@end
