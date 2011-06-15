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

@implementation TouchpadViewController

- (void)loadView {
    TouchpadView *touchpad = [[TouchpadView alloc] init];
    touchpad.delegate = self;
    [touchpad configure];
    self.view = touchpad;
 
    statusLight = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"StatusLightRed.png"]];
    [self.view addSubview:statusLight];
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        
        deviceScale = 2.0;
        statusLight.frame = CGRectMake(668, 904, 100, 100);

    } else {

        deviceScale = 1.0;
        statusLight.frame = CGRectMake(668, 904, 100, 100);

    }

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
    [[CommunicationCenter sharedCommunicationCenter] setDelegate:self];
    
    UIButton *connectionButton = [UIButton buttonWithType:UIButtonTypeCustom];
    connectionButton.frame = CGRectMake(0, CGRectGetHeight(self.view.frame) - 50, CGRectGetWidth(self.view.frame), 50);
    [connectionButton addTarget:[CommunicationCenter sharedCommunicationCenter] action:@selector(connectToDefaultHost) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:connectionButton];
    
        
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
    
    TACommand command = TACommandMake(TACommandTypeRotate, TACommandTouchStart, (point.x - 384), (point.y - 512), deviceScale, 0);
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];

}


- (void)touchpadDidTouchPoint:(CGPoint)point {
    
    TACommand command = TACommandMake(TACommandTypeRotate, TACommandTouchMove, (point.x - 384), (point.y - 512), deviceScale, 0);
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];
    
}

- (void)touchpadDidEndTouchPoint:(CGPoint)point {
    
    TACommand command = TACommandMake(TACommandTypeRotate, TACommandTouchEnd, (point.x - 384), (point.y - 512), deviceScale, 0);
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];

}

#pragma mark pinch handling
- (void)touchpadDidBeginPinch {
    
    TACommand command = TACommandMake(TACommandTypeZoom, TACommandTouchStart, 0, 0, deviceScale, 1);
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];
    
}

- (void)touchpadDidPinchWithScale:(float)scale {
    
    TACommand command = TACommandMake(TACommandTypeZoom, TACommandTouchMove, 0, 0, deviceScale, scale);
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];
    
}

- (void)touchpadDidEndPinch {
    
    TACommand command = TACommandMake(TACommandTypeZoom, TACommandTouchEnd, 0, 0, deviceScale, -1);
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];
    
}

- (void)touchpadDidBeginPan:(CGPoint)point {
    
    TACommand command = TACommandMake(TACommandTypePan, TACommandTouchStart, (point.x - 384), (point.y - 512), deviceScale, 0);
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];
    
}

- (void)touchpadDidPan:(CGPoint)point {
   //# 
    TACommand command = TACommandMake(TACommandTypePan, TACommandTouchMove, (point.x - 384), (point.y - 512), deviceScale, 0);
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];
    
}

- (void)touchpadDidEndPan:(CGPoint)point {
    
    TACommand command = TACommandMake(TACommandTypePan, TACommandTouchEnd, (point.x - 384), (point.y - 512), deviceScale, 0);
    [[CommunicationCenter sharedCommunicationCenter] sendCommand:command];
    
}

#pragma mark communication handling
- (void)didConnectToHost:(NSString *)host {
 
    statusLight.image = [UIImage imageNamed:@"StatusLightGreen.png"];

}

- (void)didDisconnect {
    
    statusLight.image = [UIImage imageNamed:@"StatusLightRed.png"];

}

- (void)didReceiveMessage:(NSData *)message {
    
}

@end
