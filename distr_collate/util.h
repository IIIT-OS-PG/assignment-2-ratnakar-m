#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <malloc.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include <openssl/sha.h>
#include <jsoncpp/json/json.h>
using namespace Json;

using namespace std;

#define BUFFER_SIZE 1024

typedef struct chunk_info
{
	char* data;
	string sha1;
	int* size; //size of data
};

pair<int,char*> get_msg(string);

int start_service(char* host, int portno);
int connect_server(char * server_host, int portno);
char* communicate_with_server(int sockfd, char *buffer, int buffersize);
char* respond_to_client(int newsockfd);
char* request_handler(int* newsockfd);
char* clone(char* orig);
char* clone2(char* orig, int size);
char* clone3(string orig);
void error(const char *msg);
char* download_piece(char* piece_idx_str, char* piece_size_str);
char* get_file_info(char* filename);
char* serve_command(char* command_line);
pair<string,int> split_chunks(string file_path, vector<chunk_info>& chunks);
string get_hash_digest(char* str1);
Value build_metadata_for_self(string file_name, pair<string,int> file_info, vector<chunk_info> chunks);