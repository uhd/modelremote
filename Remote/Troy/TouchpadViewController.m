//
//  TouchpadViewController.m
//  Troy
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#import "TouchpadViewController.h"
#import "TouchpadView.h"
#import "TACommand.h"
#import "CommunicationCenter.h"

@implementation TouchpadViewController

- (void)loadView {
    TouchpadView *touchpad = [[TouchpadView alloc] init];
    touchpad.delegate = self;
    [touchpad configure];
    self.view = touchpad;
}

- (void)dealloc
{
    [motionMonitor release];
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    motionMonitor = [[MotionMonitor alloc] init];
    
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark touch handling
- (void)touchpadDidBeginTouchPoint:(CGPoint)point {
    
    TACommand command = TACommandMake(TACommandTypePan, TACommandTouchStart, (point.x - 384), (point.y - 512));
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];

}


- (void)touchpadDidTouchPoint:(CGPoint)point {
    
    TACommand command = TACommandMake(TACommandTypePan, TACommandTouchMove, (point.x - 384), (point.y - 512));
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];
    
}

- (void)touchpadDidEndTouchPoint:(CGPoint)point {
    
    TACommand command = TACommandMake(TACommandTypePan, TACommandTouchEnd, (point.x - 384), (point.y - 512));
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];

}

#pragma mark pinch handling
- (void)touchpadDidBeginPinch {
    
    TACommand command = TACommandMake(TACommandTypeZoom, TACommandTouchStart, 0, 0);
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];
    
}

- (void)touchpadDidPinchWithScale:(float)scale {

    TACommand command = TACommandMake(TACommandTypeZoom, TACommandTouchMove, 0, scale);
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];

}

- (void)touchpadDidEndPinch {
    
    TACommand command = TACommandMake(TACommandTypeZoom, TACommandTouchEnd, 0, 0);
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];

}

@end
