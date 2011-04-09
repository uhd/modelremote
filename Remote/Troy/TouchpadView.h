//
//  TouchpadView.h
//  Troy
//
//  Created by Max Goedjen on 4/8/11.
//  Copyright 2011 Clink Apps. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol TouchpadDelegate <NSObject>

- (void)touchpadDidMoveToPoint:(CGPoint)point;

@end

@interface TouchpadView : UIImageView {
    
    id delegate;
    
}

@property (nonatomic, retain) id<TouchpadDelegate> delegate;

- (void)configure;

@end
