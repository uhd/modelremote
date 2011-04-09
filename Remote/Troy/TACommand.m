//
//  TACommand.m
//  Troy
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#import "TACommand.h"

TACommand TACommandMake(TACommandType commandType, int x, int y) {
    
    TACommand newCommand;
    newCommand.type = commandType;
    newCommand.xDifference = x;
    newCommand.yDifference = y;
    
    return newCommand;
}

NSString *NSStringFromTACommand(TACommand command) {
    return [NSString stringWithFormat:@"%i, %i, %i", command.type, command.xDifference, command.yDifference];
}
