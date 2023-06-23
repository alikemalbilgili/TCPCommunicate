#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>

#define MAX 80
#define SA struct sockaddr

// Function prototypes
int createSocket();
bool isPortBusy(int port);
void setPort(int *port);
void setTimeout(int *timeout);
void startServer(int sockfd, int port, int timeout);
void acceptClient(int sockfd, struct sockaddr_in *cli);
void chat(int connfd);
void printUsedPorts();
int waitForResponseFromDevice(int timeout);

int main()
{
    int sockfd;
    int port = 0;
    int timeout = 60;

    printf("====== Console UI ======\n");

    while (1)
    {
        printf("\n");
        printf("┏────────────────────────────┓\n");
        printf("┃ 1. Set Port                ┃\n");
        printf("┃ 2. Set Session Timeout     ┃\n");
        printf("┃ 3. Start Server            ┃\n");
        printf("┃ 4. Print Used Ports        ┃\n");
        printf("┃ 5. Exit                    ┃\n");
        printf("┃                            ┃\n");
        printf("┗────────────────────────────┛\n");
        printf("\nEnter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            setPort(&port);
            break;

        case 2:
            setTimeout(&timeout);
            break;

        case 3:
            if (port == 0)
            {
                printf("Error: Port is not set. Please set the port first.\n");
            }
            else
            {
                sockfd = createSocket();
                startServer(sockfd, port, timeout);
                close(sockfd);
            }
            break;

        case 4:
            printUsedPorts();
            break;

        case 5:
            printf("Exiting...\n");
            exit(EXIT_SUCCESS);

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }

    return 0;
}

// Function to create a socket
int createSocket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Socket successfully created..\n");
    }

    return sockfd;
}

// Function to set the port
void setPort(int *port)
{
    printf("Enter the port number: ");
    scanf("%d", port);

    if (*port < 1 || *port > 65535)
    {
        printf("Error: Invalid port number. Please enter a value between 1 and 65535.\n");
        *port = 0; // Reset port value
        return;
    }

    if (isPortBusy(*port))
    {
        printf("Error: Port %d is already in use or couldn't bind the port. Please select a different port.\n", *port);
        *port = 0; // Reset port value
    }
    else
    {
        printf("Port set to %d.\n", *port);
    }
}

// Function to check if a port is busy
bool isPortBusy(int port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    // if port is used or couldnt bind the port
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        // Port is busy
        close(sockfd);
        return true;
    }

    close(sockfd);
    return false;
}

// Function to set the session timeout
void setTimeout(int *timeout)
{
    printf("Enter the timeout value in seconds (default: 60): ");
    scanf("%d", timeout);
    printf("Timeout set to %d seconds.\n", *timeout);
}

void printUsedPorts()
{
    printf("List of used ports:\n");
    system("lsof -i -P | grep LISTEN");
}

// Function to start the server
void startServer(int sockfd, int port, int timeout)
{
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Socket successfully binded..\n");
    }

    if (waitForResponseFromDevice(timeout) || (listen(sockfd, 5)) != 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Server listening..\n");
    }

    struct sockaddr_in cli;
    int len = sizeof(cli);
    int connfd = accept(sockfd, (SA *)&cli, (socklen_t *)&len);
    if (connfd < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Server accept the client...\n");
    }

    chat(connfd);

    close(connfd);
}

// Function to handle the chat between client and server
void chat(int connfd)
{
    char buff[MAX];

    for (;;)
    {
        bzero(buff, MAX);
        read(connfd, buff, sizeof(buff));
        printf("From client: %s\t To client: ", buff);
        bzero(buff, MAX);
        int n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;

        write(connfd, buff, sizeof(buff));

        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exit...\n");
            break;
        }
    }
}
int waitForResponseFromDevice(int timeout)
{
    time_t start = time(NULL);
    while (time(NULL) - start < timeout)
    {
        if (check_device_ready())
        {
            return 1;
        }
    }
    return 0;
}
