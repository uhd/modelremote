//
//  CommunicationCenter.h
//  Troy
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#import <Foundation/Foundation.h>
#import "AsyncSocket.h"
#import "TACommand.h"

@protocol CommunicationCenterDelegate <NSObject>
- (void)didReceiveMessage:(NSData *)message;
@end

@interface CommunicationCenter : NSObject {
    
    AsyncSocket *socket;
    id delgate;
    
}

+ (CommunicationCenter *)sharedCommunicationCenter;
- (void)connectToHost:(NSString *)hostAddress;
- (BOOL)sendMessage:(NSData *)message;
- (BOOL)sendCommand:(TACommand)command;

@property (nonatomic, retain) id<CommunicationCenterDelegate> delegate;

@end
