#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SIZE_BUF 255

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    char buffer[SIZE_BUF];
    if(argc < 3){
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(1);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        // error("error opening socket\n");
        printf("error opening socket\n");
    }
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr,"server not responding, or no such host\n");
        printf("server not responding, or no such host\n");
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr_list[0] , (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)
    {
        // error("connection failed");
        printf("connection failed\n");
    };
    while (1)
    {
        bzero(buffer, SIZE_BUF);
        fgets(buffer, SIZE_BUF, stdin);
        n = write(sockfd, buffer, strlen(buffer));
        if(n < 0){
            // error("error while writing");
            printf("error while writing\n");
        }
        bzero(buffer, SIZE_BUF);
        n = read(sockfd, buffer, SIZE_BUF);
        if(n < 0){
            // error("error while reading");
            printf("error while reading\n");
        }
        printf("Server: %s", buffer);
        int i = strncmp("Bye", buffer, 3);
        if(i == 0){
            printf("bye detected");
            // break;
    }
    
    close(sockfd);
    return 0;
}
}