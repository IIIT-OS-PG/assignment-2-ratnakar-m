#include <assign2.h>
#include <client.h>

/*
This file is an interface to the requests inbound to the peer
*/
void *listener_handler(void * peer_ctx_struct_ptr)
{
    struct peer_ctx ctx = *((peer_ctx*) peer_ctx_struct_ptr);
    int* port = ctx.portno;
    int* sockfd = ctx.sockfd;
    /*string log_file_path="logs/peer-"+to_string(port)+"_"+get_time_compact()+".log";
	int *logfd = (int *) malloc(sizeof(int));
	*logfd = open(log_file_path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);*/
	int* logfd = open_log_file(*port);	
	time_t my_time = time(NULL); 
	
    write_msg_line(*logfd, get_time()+"Peer Started...");
    while(true){

       struct sockaddr_in cli_addr;
       socklen_t clilen;
       int ret;

       clilen = sizeof(cli_addr);
       int *newsockfd = (int *) malloc(sizeof(int));
       *newsockfd = accept(*sockfd, (struct sockaddr *) &cli_addr, &clilen);
       if (*newsockfd < 0) 
       		write_msg_line(*logfd, string("ERROR on accept"));
       struct request_ctx ctx;
       ctx.newsockfd=newsockfd;
       ctx.cli_addr=cli_addr;
       ctx.clilen=clilen;
       ctx.logfd=logfd;


       string m = "server: got connection from "+ 
       string(inet_ntoa(cli_addr.sin_addr)) + 
       " port " + to_string(ntohs(cli_addr.sin_port));
       write_msg_line(*logfd, m);


       pthread_t my_thread;
       ret =  pthread_create(&my_thread, NULL, &handle_request, (void*)&ctx);
       if(ret != 0) {
       		write_msg_line(*logfd, string("Error: pthread_create() failed"));
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
    int logfd=*ctx.logfd;
    char buffer[256];
    bzero(buffer,256);
    int n = read(newsockfd,buffer,255);

    //cout << "echooing..." << endl;
    //cout << string(buffer) << endl;
    write_msg_line(logfd, string("echooing..."));
    write_msg_line(logfd, string(buffer));
    close(newsockfd);
    pthread_exit(NULL);
}