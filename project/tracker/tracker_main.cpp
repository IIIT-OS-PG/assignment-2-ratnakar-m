#include <assign2.h>

void *handle_request(void * ctx_st);

int main(int argc, char **argv) {
	int sockfd = start_service("localhost",9999);
	cout << "tracker listening on port 9999" << endl;
	while(true){
        struct sockaddr_in cli_addr;
        socklen_t clilen;
        int ret;
        clilen = sizeof(cli_addr);
         int *newsockfd = (int *) malloc(sizeof(int));
         *newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
         struct request_ctx ctx;
         ctx.newsockfd=*newsockfd;
         ctx.cli_addr=cli_addr;
         ctx.clilen=clilen;
         printf("server: got connection from %s port %d\n",
                inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

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
    int newsockfd = ctx.newsockfd;
    int n;
    
     if (newsockfd < 0) 
          error("ERROR on accept");

     

     //FILE *fp = fopen ( "assign.pdf"  , "rb" );
     FILE *fp = fopen ( "the_terminal.mp4"  , "rb" );

     fseek ( fp , 0 , SEEK_END);
     int size = ftell ( fp );
     printf("file size: %d\n", size);
     rewind ( fp );

     send ( newsockfd , "Downloading file...\0", 20, 0);
     send ( newsockfd , &size, sizeof(size), 0);

     char buffer [ BUFFER_SIZE] ; 
     while ( ( n = fread( buffer , sizeof(char) , BUFFER_SIZE , fp ) ) > 0  && size > 0 ){
             send (newsockfd , buffer, n, 0 );
             memset ( buffer , '\0', BUFFER_SIZE);
             size = size - n ;
     }

    fclose ( fp );

    close(newsockfd);
    pthread_exit(NULL);
}
