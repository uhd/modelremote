//
//  main.cpp
//  Abed
//
//  Created by Max Goedjen on 4/8/11.
//  UHD
//

//Port: 1254

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

const int PORT_NUMBER = 1254;
const int BUFFER_SIZE = 100;

int main ()
{
    int socketDesc, newsocket;
    socklen_t client;
    int buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddress, clientAddress;
    int data;
    
    socketDesc = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDesc < 0)
    {
        cout<<"Failed to open socket.  Ending.";
        return 1;
    }
    bzero((char*) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = PORT_NUMBER;
    if (bind(socketDesc, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
    {
        cout<<"Failure on port bind.  Ending.";
        return 1;
    }
    listen(socketDesc, 5);
    client = sizeof(clientAddress);
    newsocket = accept(socketDesc, (struct sockaddr *) &clientAddress, &client);
    if(newsocket < 0)
    {
        cout<<"Failed to accept client.  Ending.";
        return 1;
    }
    bzero(buffer, BUFFER_SIZE);
    data = read(newsocket, buffer, BUFFER_SIZE);
    if (data < 0)
    {
        cout<<"Failed to read data from client.";
    }
    cout<<data;
    
    close(newsocket);
    close(socketDesc);
    return 0;
}