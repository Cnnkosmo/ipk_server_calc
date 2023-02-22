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
    const char buffer[BUFSIZ];
    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_socket <= 0){
        perror("ERROR: socket");
        exit(EXIT_FAILURE);
    }
    struct hostent *server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR: no such host %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(argv[2]);

    memcpy(&server_address.sin_addr.s_addr, server->h_name, server->h_length);
    struct sockaddr *addr = (struct sockaddr*) &argv[1];
    int addr_size = sizeof(argv[1]);
    struct sockaddr *addres = (struct sockaddr *) &server_address;
    int adress_size = sizeof(server_address);
    int bytes_tx = sendto(client_socket, buffer, strlen(buffer), 0, addr, addr_size);
    if(bytes_tx < 0) perror("ERROR: sendto");

    int bytes_rx = recvfrom(client_socket, buffer, BUFSIZ, 0, addr, &argv[1]);
    if(bytes_rx < 0) perror("ERROR: recvfrom"); 
}