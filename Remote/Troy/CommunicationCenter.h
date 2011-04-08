//
//  CommunicationCenter.h
//  Troy
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#import <Foundation/Foundation.h>
#import "AsyncSocket.h"

@protocol CommunicationCenterDelegate <NSObject>
- (void)didReceiveMessage:(NSData *)message;
@end

@interface CommunicationCenter : NSObject {
    
    AsyncSocket *socket;
    
}

- (void)connectToHost:(NSString *)hostAddress;
- (BOOL)sendMessage:(NSData *)message;

@end
