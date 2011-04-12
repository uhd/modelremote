//
//  Server.h
//  Abed
//
//  Created by Brian Holtkamp on 4/9/11.
//  UHD
//

#import <stdio.h>
#import <string.h>
#import <stdlib.h>
#import <unistd.h>
#import <sys/types.h>
#import <sys/socket.h>
#import <netinet/in.h>
#import <netdb.h>
#import "TACommand.h"
#import "CommandInterpreter.h"

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