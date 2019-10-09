#include <util.h>

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
     request_handler(newsockfd);
    
  }     
 close(sockfd);
 return 0; 
}


char* request_handler(int* newsockfd) {
    char buffer [ BUFFER_SIZE] ; 
    recv ( *newsockfd , buffer, BUFFER_SIZE, 0);
    //cout << "Server: Received command: " << buffer << endl;
    char* response = serve_command(buffer);
    send ( *newsockfd , response, BUFFER_SIZE, 0);
}

char* serve_command(char* command_line){
  cout << "RECEIVED: " << command_line << endl;

  char* command = strtok(command_line, " ");
  if(command==NULL)
    return "";
  
  if(strcmp(command, "get_file_info")==0) {
    char* filename = strtok(NULL, " ");
    return get_file_info(filename);
  } 
  else if(strcmp(command, "download_piece")==0){
    char* piece_idx_str = strtok(NULL, " ");
    char* piece_size_str = strtok(NULL, " ");
    cout << "piece_idx_str: " << piece_idx_str << endl;
    cout << "piece_size_str: " << piece_size_str << endl;
    return download_piece(piece_idx_str, piece_size_str);
  }

}
