#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define BUFF_SIZE 512*1024

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int port = 8888;
    int sockfd = connect_server("localhost", int portno);
    char* file_info = communicate_with_server(sockfd, char *buffer, int buffersize);

}