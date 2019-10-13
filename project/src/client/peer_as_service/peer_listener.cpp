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
       //fcntl(*newsockfd, F_SETFL, O_NONBLOCK);
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
       ret =  pthread_create(&my_thread, NULL, &handle_request, (void*)&ctx);
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

    char buffer [ BUFFER_SIZE*2] ; 
    recv ( newsockfd , buffer, BUFFER_SIZE*2, 0);

    write_msg_line(ctx.logfd, string("echooing..."));
    write_msg_line(ctx.logfd, string(buffer));
    
    pair<int,char*> command_response = serve_command(buffer,ctx.logfd);
    //cout << "PIECES INFO: " << endl;
    ///cout << command_response << endl;
    //cout << "PIECES INFO COMPLETE: " << endl;
    //cout << "*****************" << endl;
    
    //char* res_to_send = clone3(command_response.second, BUFFER_SIZE*2);

    char* res_to_send = clone3(command_response.second, command_response.first);
    //free(command_response.second);
    cout << "PIECES INFO: " << endl;
    cout << res_to_send << endl;
    cout << "PIECES INFO COMPLETE: " << endl;
    cout << "*****************" << endl;
    cout << "BUFFERSIZE*2= " << BUFFER_SIZE*2 << endl;
    int* size_ptr = (int *) malloc(sizeof(int));
    *size_ptr=command_response.first;
    //cout << strlen(res_to_send) << endl;
    send ( newsockfd , size_ptr, sizeof(int), 0);
    send ( newsockfd , res_to_send, command_response.first, 0);

    //close(newsockfd);
    pthread_exit(NULL);
}