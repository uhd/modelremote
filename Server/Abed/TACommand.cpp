//
//  TACommand.cpp
//  Abed
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#include "TACommand.h"

TACommand TACommandMake(TACommandType commandType, TACommandTouch touchType, int x, int y, float scale, float zoomValue) {
    
    TACommand newCommand;
    newCommand.type = commandType;
    newCommand.touch = touchType;
    newCommand.xDifference = x;
    newCommand.yDifference = y;
	newCommand.zoomValue = zoomValue;
    
    return newCommand;
}