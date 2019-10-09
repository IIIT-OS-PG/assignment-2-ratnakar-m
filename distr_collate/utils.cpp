#include <util.h>

int start_service(char* host, int portno){
	char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr;
    int sockfd =  socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
       error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr)); //clear addr struct

    serv_addr.sin_family = AF_INET;  //byte order
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    serv_addr.sin_port = htons(portno); //short int to n/w byte order

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
       error("error on binding");

    listen(sockfd,5);

    cout << "sockfd: " << sockfd << endl;

    return sockfd;
}

int connect_server(char * server_host, int portno) {
	int len, result, ssockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
	//create a socket for client
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); //open a socket at client
	server = gethostbyname(server_host);

	bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    result = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if(result<0) 
    {
    	error("error connecting to server");
    	return -1;
    }
	return sockfd;
}

char* communicate_with_server(int sockfd, char *buffer, int buffersize) {
	//bzero(buffer, buffersize);
    cout << "sockfd: " << sockfd << endl;
	int n = send(sockfd, buffer, buffersize,0);
	if (n < 0)
		perror("ERROR writing to socket");
	//printf("[%s]\n", buffer);
	bzero(buffer, buffersize);
	n = recv(sockfd, buffer, buffersize-1,0);

	if (n < 0)
		perror("ERROR reading from socket");
	//printf("[%s]\n", buffer);
	close (sockfd);

    return buffer;
}


char* clone(char* orig){
    char* cl = (char *) malloc(BUFFER_SIZE);
    int g = 0;
    while(orig[g] != '\0')
    {
        cl[g] = orig[g];
        g++;
    }
    cl[g]='\0';

    return cl;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}