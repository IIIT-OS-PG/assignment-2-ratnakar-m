/* The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#define BUFF_SIZE 256

void *handle_request(void * sockfd);
void error(const char *msg);
struct request_ctx 
{
    int newsockfd;
    struct sockaddr_in cli_addr;
    socklen_t clilen;
};



int main(int argc, char *argv[])
{
     int sockfd, portno;
     
     char buffer[256];
     struct sockaddr_in serv_addr;
     
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     // create a socket
     // socket(int domain, int type, int protocol)
     sockfd =  socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");

     // clear address structure
     bzero((char *) &serv_addr, sizeof(serv_addr));

     portno = atoi(argv[1]);

     /* setup the host_addr structure for use in bind call */
     // server byte order
     serv_addr.sin_family = AF_INET;  

     // automatically be filled with current host's IP address
     serv_addr.sin_addr.s_addr = INADDR_ANY;  

     // convert short integer value for port must be converted into network byte order
     serv_addr.sin_port = htons(portno);

     // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
     // bind() passes file descriptor, the address structure, 
     // and the length of the address structure
     // This bind() call will bind  the socket to the current IP address on port, portno
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");

     // This listen() call tells the socket to listen to the incoming connections.
     // The listen() function places all incoming connection into a backlog queue
     // until accept() call accepts the connection.
     // Here, we set the maximum size for the backlog queue to 5.
     listen(sockfd,5);

     while(true){

        struct sockaddr_in cli_addr;
         // The accept() call actually accepts an incoming connection
        socklen_t clilen;
        //int newsockfd;
        int ret;

        clilen = sizeof(cli_addr);

         // This accept() function will write the connecting client's address info 
         // into the the address structure and the size of that structure is clilen.
         // The accept() returns a new socket file descriptor for the accepted connection.
         // So, the original socket file descriptor can continue to be used 
         // for accepting new connections while the new socker file descriptor is used for
         // communicating with the connected client.
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

         char buffer [ BUFF_SIZE] ; 
         while ( ( n = fread( buffer , sizeof(char) , BUFF_SIZE , fp ) ) > 0  && size > 0 ){
                 send (newsockfd , buffer, n, 0 );
                 memset ( buffer , '\0', BUFF_SIZE);
                 size = size - n ;
         }

        fclose ( fp );

        close(newsockfd);
        pthread_exit(NULL);
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

char* get_hash(char* str){
    //const unsigned char str[] = "Original String";
    //unsigned char hash[SHA_DIGEST_LENGTH]; // == 20
    unsigned char* hash = (char *) malloc(SHA_DIGEST_LENGTH);

    SHA1(str, sizeof(str) - 1, hash);

    cout << "hash val = "<<hash<<endl;
    char mdString[SHA_DIGEST_LENGTH*2+1];
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)hash[i]);

    printf("SHA1 digest: %s\n", mdString);
    return hash;
}

char* clone(char* orig){
    char* cl = (char *) malloc(COMMAND_BUFFER);
    int g = 0;
    while(orig[g] != '\0')
    {
        cl[g] = orig[g];
        g++;
    }
    cl[g]='\0';

    return cl;
}