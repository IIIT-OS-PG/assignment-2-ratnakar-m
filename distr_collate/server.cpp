#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>

using namespace std;

#define BUFFER_SIZE 512*1024 //512 KB

char* command_handler(char* request);
char* get_piece_info(char* file_name);
char* get_piece_data(int piece_idx, int piece_size);

int main(){
	int sockfd = start_service("localhost",9999);
  cout << "tracker listening on port 9999" << endl;
  while(true){
    struct sockaddr_in cli_addr;
    socklen_t clilen;
    int ret;
    clilen = sizeof(cli_addr);
     int *newsockfd = (int *) malloc(sizeof(int));
     *newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     //printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

    respond_to_client(newsockfd);
  }     
 close(sockfd);
 return 0; 
}

char* request_handler(char* request){
	cout << "request received: " << request << endl;
}
char* get_piece_info(char* file_name);
char* get_piece_data(int piece_idx, int piece_size);