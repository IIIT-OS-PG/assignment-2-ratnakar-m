#ifndef COMMONS_H
#define COMMONS_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>
#include <openssl/sha.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctime>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define PROMPT "peer>"

using namespace std;

struct request_ctx 
{
    int* newsockfd;
    struct sockaddr_in cli_addr;
    socklen_t clilen;
    int* logfd;
};

pair<int,char*> get_msg(string);
int write_msg(int, string);
int write_msg_line(int fd, string msg_str);
char* clone(char* orig);
void error(const char *msg);
string get_time();
string get_time_compact();
int* open_log_file(int port);

#endif //COMMONS_H
