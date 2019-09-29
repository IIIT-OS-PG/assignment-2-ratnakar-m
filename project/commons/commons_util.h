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
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctime>


struct request_ctx 
{
    int newsockfd;
    struct sockaddr_in cli_addr;
    socklen_t clilen;
};


#define BUFFER_SIZE 256
#define PROMPT "peer>"


using namespace std;

char* clone(char* orig);
void error(const char *msg);
string get_time();
string get_time_compact();

#endif //COMMONS_H
