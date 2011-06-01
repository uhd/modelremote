//
//  main.cpp
//  Abed
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#include "Server.h"

int main (int argv, char *windowID[])
{
    Server server;
    server.initialize();
    
    CommandInterpreter interpreter;
    interpreter.grabWindowID(*windowID);
	
    server.setDelegate(interpreter);
    
    server.readData();
    
    return 0;
}