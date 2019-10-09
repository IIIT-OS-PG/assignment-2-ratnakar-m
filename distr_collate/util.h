#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_SIZE 512*1024

int start_service(char* host, int portno);
int connect_server(char * server_host, int portno);
char* communicate_with_server(int sockfd, char *buffer, int buffersize);
char* respond_to_client(int newsockfd);