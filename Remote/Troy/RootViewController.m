//
//  RootViewController.m
//  Troy
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#import "RootViewController.h"
#import "TouchpadView.h"
#import "TACommand.h"
#import "CommunicationCenter.h"

@implementation RootViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        [CommunicationCenter sharedCommunicationCenter];
    }
    return self;
}

- (void)dealloc
{
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

- (void)touchpadDidTouchPoint:(CGPoint)point {
    
    NSLog(@"POINT: %@", NSStringFromCGPoint(point));
    TACommand command = TACommandMake(TACommandTypeRotate, (point.x - 384), (point.y - 512));
    NSLog(@"TACommand %@", NSStringFromTACommand(command));
    
    NSData *data = [NSData dataWithBytes:&command length:sizeof(command)];

    [[CommunicationCenter sharedCommunicationCenter] sendMessage:data];
    
}

@end
