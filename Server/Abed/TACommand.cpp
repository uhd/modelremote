//
//  TACommand.cpp
//  Abed
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#include "TACommand.h"

TACommand TACommandMake(TACommandType commandType, int x, int y) {
    
    TACommand newCommand;
    newCommand.type = commandType;
    newCommand.xCoordinate = x;
    newCommand.yCoordinate = y;
    
    return newCommand;
}

string StringFromTACommand(TACommand command) {
    
    //return [NSString stringWithFormat:@"%i, %i, %i", command.type, command.xCoordinate, command.yCoordinate];
}
