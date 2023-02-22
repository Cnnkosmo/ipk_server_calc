#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define SIZE_BUF 255


void error(const char *msg)
{
    perror(msg);
    exit(1);
}


int main(int argc, char *argv[])
{
    if(argc < 2){
        fprintf(stderr,"Port not provided.Program terminated\n");
        exit(1);
    }
    int sockfd, newsockfd, portno, n;
    char buffer[SIZE_BUF];

    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("error openning socket\n");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);//taking port number from argv line

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("binding failed\n");
    }
    listen(sockfd, 2);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if(newsockfd < 0){
        // error("error on accept\n");
    }
    while(1)
    {
        bzero(buffer, SIZE_BUF);
        n = read(newsockfd, buffer, SIZE_BUF);
        if(n < 0){
            // error("error while reading\n");
        }
        printf("Client : %s", buffer);
        bzero(buffer, SIZE_BUF);
        fgets(buffer, SIZE_BUF, stdin);

        n = write(newsockfd, buffer, strlen(buffer));
        if(n < 0){
            // error("error while writing\n");
        }
        int i = strncmp("Bye", buffer, 3);
        printf("%d",i);
        if(i == 0){
            printf("bye detected");
            // break;
        }
    }
    close(newsockfd);
    close(sockfd);
    return 0;

}