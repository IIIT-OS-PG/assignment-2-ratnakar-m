#ifndef NETWORK_UTIL_H
#define NETWORK_UTIL_H

int start_service(char* hostname, int port); //listen as server
int connect_server(char * server_ip, int server_port); //connect to another server
char* communicate_with_server(int sockfd, char *buffer, int buffer_size); //round trip communication (send and recv)
char* communicate_with_server2(int sockfd, char *buffer, int buffersize,  int piece_size, int piece_idx);
char* communicate_with_server_ld(int sockfd, char *buffer, int buffersize);
char* communicate_with_server_one_way(int sockfd, char *buffer, int buffersize);
pair<string, string> get_hostname_ip();

#endif //NETWORK_UTIL_H