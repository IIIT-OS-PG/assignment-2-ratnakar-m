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
#include <malloc.h>
#include <iostream>

using namespace std;

#define BUFFER_SIZE 512*1024

int start_service(char* host, int portno);
int connect_server(char * server_host, int portno);
char* communicate_with_server(int sockfd, char *buffer, int buffersize);
char* respond_to_client(int newsockfd);
char* request_handler(int* newsockfd);
char* clone(char* orig);
void error(const char *msg);
char* download_piece(char* piece_idx_str, char* piece_size_str);
char* get_file_info(char* filename);
char* serve_command(char* command_line);