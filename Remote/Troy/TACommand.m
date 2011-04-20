//
//  TACommand.m
//  Troy
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#import "TACommand.h"

TACommand TACommandMake(TACommandType commandType, TACommandTouch touchType, int x, int y, float scale) {
    
    TACommand newCommand;
    newCommand.type = commandType;
    newCommand.touch = touchType;
    newCommand.xDifference = x * scale;
    newCommand.yDifference = y * scale;
    
    return newCommand;
}

NSString *NSStringFromTACommand(TACommand command) {
    return [NSString stringWithFormat:@"%i, %i, %i, %i", command.type, command.touch, command.xDifference, command.yDifference];
}
