//
//  Server.h
//  Abed
//
//  Created by Brian Holtkamp on 4/9/11.
//  UHD
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "CommandInterpreter.h"

using namespace std;

const int PORT_NUMBER = 1254;

class Server
{
    public:
    void initialize();
    void connectClient();
    void setDelegate(CommandInterpreter dataDelegate);
    void readData();
    void closeServer(string);
    
    private:
    int socketDesc;
    int newSocketDesc;
    socklen_t client;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;    
    CommandInterpreter delegate;
    
};