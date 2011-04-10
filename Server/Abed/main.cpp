//
//  main.cpp
//  Abed
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//
//Port: 1254

#include "server.h"

int main ()
{
    server server;
    
    server.initialize();
    server.connectClient();
    
    TACommand command;
    while (server.readPort(command)) 
    {
        printf("COMMAND: %i, %i, %i, %i\n", command.type, command.touch, command.xDifference, command.yDifference);
    }
    
    server.closeServer("Successful close.");
    return 0;
}