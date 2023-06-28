#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> // Winsock library

#define MAX 80
#define SA struct sockaddr

void func(SOCKET sockfd);
void setClientPort(int *port);
void setClientIp(char *ip);
int validateIP(char *buffer);
char ip[50];

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("Failed to initialize winsock.\n");
        return 1;
    }

    int port;
    SOCKET sockfd;
    struct sockaddr_in servaddr, cli;

    setClientPort(&port);
    setClientIp(ip);

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET)
    {
        printf("Socket creation failed...\n");
        WSACleanup();
        return 1;
    }
    else
        printf("Socket successfully created..\n");

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(port);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Connection with the server failed...\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    else
        printf("Connected to the server..\n");

    // function for chat
    func(sockfd);

    // close the socket
    closesocket(sockfd);
    WSACleanup();
    return 0;
}

void func(SOCKET sockfd)
{
    char buff[MAX];
    int n;
    for (;;)
    {
        memset(buff, 0, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        send(sockfd, buff, sizeof(buff), 0);
        memset(buff, 0, sizeof(buff));
        recv(sockfd, buff, sizeof(buff), 0);
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0)
        {
            printf("Client Exit...\n");
            break;
        }
    }
}

void setClientPort(int *port)
{
    for (;;)
    {
        printf("Please enter the server port for connection: ");
        scanf("%d", port);

        if (*port < 1 || *port > 65535)
        {
            printf("Error: Invalid port number. Please enter a value between 1 and 65535.\n");
            *port = 0;
        }
        else
        {
            break;
        }
    }
}

void setClientIp(char *ip)
{
    char buffer[50];

    for (;;)
    {
        printf("Please enter the server IP for connection: ");
        fgets(buffer, 50, stdin);

        size_t len = strcspn(buffer, "\n"); // Find the index of the newline character
        if (buffer[len] == '\n')
            buffer[len] = '\0';

        if (validateIP(buffer))
        {
            strcpy(ip, buffer);
            break;
        }
        else
        {
            printf("Error: Please enter a valid IP address.\n");
        }
    }
}

int validateIP(char *buffer)
{
    struct sockaddr_in sa;
    return inet_addr(buffer) != INADDR_NONE;
}