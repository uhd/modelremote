//
//  CommandInterpreter.cpp
//  Abed
//
//  Created by Max Goedjen on 4/10/11.
//  UHD
//

#include "CommandInterpreter.h"

void CommandInterpreter::initialize()
{
    
    

}

void CommandInterpreter::handleCommand(TACommand command)
{
    
    printf("COMMAND: %i, %i, %i, %i\n", command.type, command.touch, command.xDifference, command.yDifference);

}