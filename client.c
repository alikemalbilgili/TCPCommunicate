#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include <regex.h>  // regex validation

#define MAX 80
#define SA struct sockaddr

void func(int sockfd);
void setClientPort(int *port);
void setClientIp(char *ip);
int validateIP(char *buffer);
char ip[50];

int main()
{
    int port;
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    setClientPort(&port);
    setClientIp(ip);

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.2.194");
    servaddr.sin_port = htons(port);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}

void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;)
    {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
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
        printf("Please enter to server port for connection: ");
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
        printf("Please enter to server ip for connection: ");
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
            printf("Error: Please enter a valid ip adress.\n");
        }
    }
}

int validateIP(char *buffer)
{
    struct sockaddr_in sa;
    return inet_pton(AF_INET, buffer, &(sa.sin_addr));
}