#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include "webfiles.h"

int main( )
{
    struct sockaddr_in serverAddr, clientAddr;
    int serverFd, clientFd, clientAddrLen, numBytesFromClient, numBytesToClient;
    char clientBuffer[1000];
    char serverBuffer[100];
    struct Webfile *idx;

    printf("Webserver!\n\n");

    memset(&serverAddr, 0, sizeof (struct sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(8080);

    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd >= 0) {
        printf("Acquired socket file descriptor.\n");
    }
    else {
        printf("Failed to get socket file descriptor.\n");

        return 1;
    }

    if (bind(serverFd, (struct sockaddr *)&serverAddr, sizeof (struct sockaddr_in)) == 0) {
        printf("Assigned address to socket file descriptor.\n");
    }
    else {
        printf("Failed to assign address to socket file descriptor.\n");

        return 1;
    }

    if (listen(serverFd, 0) == 0) {
        printf("Marked socket file descriptor as accepting connections.\n");
    }
    else {
        printf("Failed to mark socket file descriptor as accepting connections.\n");

        return 1;
    }

    printf("Waiting for client connection...\n");
    clientFd = accept(serverFd, (struct sockaddr *)&clientAddr, (socklen_t *)&clientAddrLen);
    if (clientFd >= 0) {
        printf("Connection accepted and client file descriptor created.\n");
    }
    else {
        printf("Failed to accept connection.\n");

        return 1;
    }

    numBytesFromClient = read(clientFd, clientBuffer, 1000);
    if (numBytesFromClient >= 0) {
        printf("Bytes read from client: %d\n", numBytesFromClient);
    }
    else {
        printf("Failed to read from client.\n");

        return 1;
    }

    printf("--- From Client ----------------------------------------------------\n");
    printf("%s", clientBuffer);
    printf("--------------------------------------------------------------------\n");

    getIndex(&idx);

    snprintf(serverBuffer, 100, "%s%d%s", "HTTP/1.1 200 OK\r\nContent-Length: ",
                        idx->len, "\r\nContent-Type: text/html\r\n\r\n");

    numBytesToClient  = write(clientFd, serverBuffer, strlen(serverBuffer));
    numBytesToClient += write(clientFd, idx->content, idx->len);

    if (numBytesToClient >= 0) {
        printf("Bytes written to client: %d\n", numBytesToClient);
    }
    else {
        printf("Failed to write to client.\n");

        return 1;
    }
     
    return 0;
}
