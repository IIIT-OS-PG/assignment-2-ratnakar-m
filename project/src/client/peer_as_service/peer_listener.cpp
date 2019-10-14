#include <assign2.h>
#include <client.h>

/*
This file is an interface to the requests inbound to the peer
Peer as a service
*/
void *listener_handler(void * peer_ctx_struct_ptr)
{
    struct peer_ctx ctx = *((peer_ctx*) peer_ctx_struct_ptr);
    int* port = ctx.portno;
    int* sockfd = ctx.sockfd;
    /*string log_file_path="logs/peer-"+to_string(port)+"_"+get_time_compact()+".log";
	int *logfd = (int *) malloc(sizeof(int));
	*logfd = open(log_file_path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);*/
  //int *logfd = (int *) malloc(sizeof(int));
	int* logfd = open_log_file(*port);	
	time_t my_time = time(NULL); 
	
    write_msg_line(logfd, get_time()+"Peer Started...");
    while(true){

       struct sockaddr_in cli_addr;
       socklen_t clilen;
       int ret;

       clilen = sizeof(cli_addr);
       int *newsockfd = (int *) malloc(sizeof(int));
       *newsockfd = accept(*sockfd, (struct sockaddr *) &cli_addr, &clilen);
       if (*newsockfd < 0) 
       		write_msg_line(logfd, string("ERROR on accept"));
       struct request_ctx ctx;
       ctx.newsockfd=newsockfd;
       ctx.cli_addr=cli_addr;
       ctx.clilen=clilen;
       ctx.logfd=logfd;


       string m = "server: got connection from "+ 
       string(inet_ntoa(cli_addr.sin_addr)) + 
       " port " + to_string(ntohs(cli_addr.sin_port));
       write_msg_line(logfd, m);


       pthread_t my_thread;
       ret =  pthread_create(&my_thread, NULL, &handle_request2, (void*)&ctx);
       if(ret != 0) {
       		write_msg_line(logfd, string("Error: pthread_create() failed"));
            exit(EXIT_FAILURE);
        }

     }

    close(*sockfd);
    pthread_exit(NULL);
}

void *handle_request(void * ctx_st)
{
    request_ctx ctx = *((request_ctx*) ctx_st);
    int newsockfd = *ctx.newsockfd;
    int* logfd;
    logfd = ctx.logfd;

    char buffer [ BUFFER_SIZE] ; 
    recv ( newsockfd , buffer, BUFFER_SIZE, 0);

    write_msg_line(ctx.logfd, string("echooing..."));
    write_msg_line(ctx.logfd, string(buffer));
    
    char* command_response = serve_command(buffer,ctx.logfd);
    cout << "PIECE INFO SENT (len): "<< strlen(command_response) << endl;
    cout << command_response << endl;
    int n=send ( newsockfd , command_response, BUFFER_SIZE, 0);
    cout << "Bytes sent: " << n << endl;
    //close(newsockfd);
    pthread_exit(NULL);
}

void *handle_request2(void * ctx_st)
{
    request_ctx ctx = *((request_ctx*) ctx_st);
    int newsockfd = *ctx.newsockfd;
    int* logfd;
    logfd = ctx.logfd;

    char inp_buffer [ BUFFER_SIZE] ; 
    recv ( newsockfd , inp_buffer, BUFFER_SIZE, 0);

    write_msg_line(ctx.logfd, string("echooing..."));
    write_msg_line(ctx.logfd, string(inp_buffer));
    
    char* from_client = strtok(inp_buffer, "=>");
    char* command_part = strtok(NULL, "=>");
    if(command_part==NULL)
      return (void*)"No command sent";

    char* command = strtok(command_part, " ");

    char* command_response = "";
    int response_length = 0;
    if(strcmp(command, "get_pieces_info")==0) {
      char* file_name = strtok(NULL, " ");
      command_response = get_pieces_info_serv(file_name);
    }
    else if(strcmp(command, "download_piece")==0) {
      char* file_name = strtok(NULL, " ");
      char* piece_idx_arr = strtok(NULL, " ");
      char* piece_size_arr = strtok(NULL, " ");
      int piece_idx = atoi(piece_idx_arr);
      int piece_size = atoi(piece_size_arr);
      char* command = strtok(command_part, " ");
      cout << "BEFORE getting pieces from file" << endl;
      command_response = download_piece_serv(file_name, piece_idx, piece_size);
      cout << "AFTER getting pieces from file" << endl;
      response_length=piece_size;
    }

    if(strcmp(command, "download_piece")==0) {
        cout << "*************SPECIAL ROUTE: *******************" << endl;
        char payload_size[4];
        memcpy(payload_size, &response_length, sizeof(response_length));
        //int x;
        //char bytes[sizeof x];
        //static_cast<char*>(static_cast<void*>(&x));
        int n=send ( newsockfd , payload_size, 4, 0);
        cout << "Paylod Bytes Sent: " << n << endl;
        cout << "Response Size Declaration: " << payload_size << endl;
        size_t len = response_length;
        char *p = command_response;
        n=0;
        do{
          p += n;
          n=send ( newsockfd , p, len, 0);
          len = len - n;

        }while(len>0 && n>0);

        if ( len > 0 || n < 0 ) {
          cout << "something amiss: l = "<<len << ", n = " << n << endl;
        }
        //cout << command_response << endl;
        //int n=send ( newsockfd , command_response, BUFFER_SIZE, 0);
        cout << "Total Bytes sent: " << (response_length-len) << " of " << response_length << endl;
    }
    else{
      cout << "*************REGULAR ROUTE: *******************" << endl;
      cout << "PIECE INFO SENT (len): "<< strlen(command_response) << endl;
      cout << command_response << endl;
      int n=send ( newsockfd , command_response, BUFFER_SIZE, 0);
      cout << "Bytes sent: " << n << endl;
    }
    //close(newsockfd);
    pthread_exit(NULL);
}