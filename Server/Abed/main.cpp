//
//  main.cpp
//  Abed
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

#include "server.h"

int main ()
{
    Server server;
    
    server.initialize();
    server.readData();
    
    return 0;
}