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

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        motionMonitor = [[MotionMonitor alloc] init];

    }
    return self;
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
    // Do any additional setup after loading the view from its nib.

    TouchpadView *touchpad = [[TouchpadView alloc] initWithFrame:self.view.frame];
    touchpad.delegate = self;
    [self.view addSubview:touchpad];
    [touchpad configure];
    
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

- (void)touchpadDidPinchWithScale:(float)scale {

    TACommand command = TACommandMake(TACommandTypeZoom, TACommandTouchMove, 0, scale);
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];

}

@end
