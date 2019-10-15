#include <assign2.h>
#include <tracker.h>

void *handle_request(void * ctx_st);

int main(int argc, char **argv) {

    if (argc < 3) {
       cout << "Usage: tracker tracker_file tracker_no" << endl;
       exit(1);
    }

    char* tracker_path = argv[1];
    char* tracker_no_str = argv[2];
    int tracker_no = atoi(tracker_no_str);

    pair<char*,int> ti = get_tracker_info(tracker_path,tracker_no);

    char* host = ti.first;
    int port = ti.second;

    int *tracker_portno = (int *) malloc(sizeof(int));
    *tracker_portno = port;
	//int sockfd = start_service("localhost",*tracker_portno);
    int sockfd = start_service(host,*tracker_portno);
	cout << "tracker listening on port: " << *tracker_portno << endl;
	while(true){
        struct sockaddr_in cli_addr;
        socklen_t clilen;
        int ret;
        clilen = sizeof(cli_addr);
         int *newsockfd = (int *) malloc(sizeof(int));
         *newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
         struct request_ctx ctx;
         ctx.newsockfd=newsockfd;
         ctx.cli_addr=cli_addr;
         ctx.clilen=clilen;
         //printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

        pthread_t my_thread;
        ret =  pthread_create(&my_thread, NULL, &handle_request, (void*)&ctx);
        if(ret != 0) {
                printf("Error: pthread_create() failed\n");
                exit(EXIT_FAILURE);
        }

     }
     
     close(sockfd);
     return 0; 
}

void *handle_request(void * ctx_st)
{
    request_ctx ctx = *((request_ctx*) ctx_st);
    int newsockfd = *ctx.newsockfd;
    sockaddr_in cli_addr = ctx.cli_addr;
    char* client_ip = inet_ntoa(cli_addr.sin_addr);

    int n;
    
     if (newsockfd < 0) 
          error("ERROR on accept");

     
     char buffer [ BUFFER_SIZE] ; 
     recv ( newsockfd , buffer, BUFFER_SIZE, 0);
     char* command_response = serve_command(buffer);
     //printf("CONNECT:[%s:%d:%d] => %s\n", inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port),*ctx.newsockfd,buffer);
     send ( newsockfd , command_response, BUFFER_SIZE, 0);

    //close(newsockfd);
    pthread_exit(NULL);
}
