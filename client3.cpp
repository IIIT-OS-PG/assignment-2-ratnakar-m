#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define BUFF_SIZE 256

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[BUFF_SIZE];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    

    bzero(buffer,256);
    recv(sockfd, &buffer, 20, 0);
    printf("%s\n", buffer);

    int file_size;
    recv(sockfd, &file_size, sizeof(file_size), 0);
    printf("file size: %d\n", file_size);

    FILE *fp = fopen ( "downloaded.pdf"  , "wb" );
    bzero(buffer,256);

    while ( ( n = recv( sockfd , buffer ,   BUFF_SIZE, 0) ) > 0  &&  file_size > 0){
    
        fwrite (buffer , sizeof (char), n, fp);
        memset ( buffer , '\0', BUFF_SIZE);
        file_size = file_size - n;
    } 



    close( sockfd);
    fclose ( fp );

    close(sockfd);
    return 0;
}