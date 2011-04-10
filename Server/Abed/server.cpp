//
//  server.cpp
//  Abed
//
//  Created by Brian Holtkamp on 4/9/11.
//  UHD
//

#include "server.h"

void server::initialize()
{
    socketDesc = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDesc < 0)
    {
        closeServer("Failed to open socket.");
    }
    bzero((char*) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT_NUMBER);// PORT_NUMBER;
    if (bind(socketDesc, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
    {
        closeServer("Failure on port bind.");
    }
}

void server::connectClient()
{
    listen(socketDesc, 5);
    client = sizeof(clientAddress);
    newSocketDesc = accept(socketDesc, (struct sockaddr *) &clientAddress, &client);
    if(newSocketDesc < 0)
    {
        closeServer("Failure on accepting client.");
    }

}

int server::readData(TACommand command)
{
    return(read(newSocketDesc, &command, sizeof(command)));
}

void server::closeServer(string error)
{
    close(socketDesc);
    close(newSocketDesc);
    cout<<"Server closing: "<<error<<" Press enter to terminate.";
    cin.get(); cin.get();
    exit(1);
}