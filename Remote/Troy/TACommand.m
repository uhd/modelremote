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
    newCommand.xCoordinate = x;
    newCommand.yCoordinate = y;
    
    return newCommand;
}

NSString *NSStringFromTACommand(TACommand command) {
    return [NSString stringWithFormat:@"%i, %i, %i", command.type, command.xCoordinate, command.yCoordinate];
}
