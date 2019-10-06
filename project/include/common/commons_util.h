#ifndef COMMONS_H
#define COMMONS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
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

using namespace std;

#define BUFFER_SIZE 512*1024
#define CHUNK_SIZE 512*1024 //512 KB
//const int CHUNK_SIZE = 512*1024; //512 KB
#define PROMPT "peer>"
#define SUCCESS_MSG "Command Successful"
#define HEADER_AND_BODY_SEPARATOR "$$"

#include <jsoncpp/json/json.h>
using namespace Json;



struct request_ctx 
{
    int* newsockfd;
    struct sockaddr_in cli_addr;
    socklen_t clilen;
    int* logfd;
};

typedef struct chunk_info
{
	char* data;
	string sha1;
	int* size; //size of data
};

pair<int,char*> get_msg(string);
int write_msg(int, string);
int write_msg_line(int fd, string msg_str);
char* clone(char* orig);
void error(const char *msg);
string get_time();
string get_time_compact();
int* open_log_file(int port);
string get_base_name(string file_path);
string strip_extn(string basename);
pair<string,int> split_chunks(string file_path, vector<chunk_info>& chunks);
string get_hash_digest(char* str1);
int* open_file(string dir_path, string file_name);
void write_to_file(string dir_path, string file_name, string content);

#endif //COMMONS_H