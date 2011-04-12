//
//  main.cpp
//  Abed
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#import "Server.h"
#import "CommandInterpreter.h"

int main ()
{
    Server server;
    server.initialize();
    
    CommandInterpreter interpreter;
    interpreter.initialize();
    
    server.setDelegate(interpreter);
    
    server.readData();
    
    return 0;
}