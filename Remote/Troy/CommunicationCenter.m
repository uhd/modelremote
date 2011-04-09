//
//  CommunicationCenter.m
//  Troy
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#import "CommunicationCenter.h"

@implementation CommunicationCenter

@synthesize  delegate;

static CommunicationCenter *instance;

//Static host/port for now
const NSUInteger kPortNumber = 1254;
const NSString *kHostName = @"192.168.0.200";

+ (CommunicationCenter *)sharedCommunicationCenter {
	
	if (instance == nil) {
		
        instance = [[CommunicationCenter alloc] init];
		
    }
    
    return instance;
    
}

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
        
        socket = [[AsyncSocket alloc] initWithDelegate:self];    
        [self connectToHost:kHostName];

    }
    
    return self;
}

- (void)dealloc
{
    [socket dealloc];
    [super dealloc];
}


#pragma mark control
- (void)connectToHost:(NSString *)hostAddress {
    
    NSError *error;
    [socket connectToHost:hostAddress onPort:kPortNumber error:&error];
    
}

- (BOOL)sendMessage:(NSData *)message {
    
    if ([socket isConnected]) {
        [socket writeData:message withTimeout:30 tag:0];
    } else {
        NSLog(@"Not connected");
        //[self connectToHost:kHostName];
    }
    return YES;
    
}


#pragma mark socket delegate methods

- (void)onSocket:(AsyncSocket *)sock didConnectToHost:(NSString *)host port:(UInt16)port {
    
    NSLog(@"Connected to %@ (%i)", host, port);
    
    //[socket writeData:[command tranportableCommandData] withTimeout:60 tag:0];
    
}


@end
