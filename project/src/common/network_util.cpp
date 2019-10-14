#include <assign2.h>

int start_service(char* host, int portno){
	char buffer[256];
    struct sockaddr_in serv_addr;
    int sockfd =  socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
       error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr)); //clear addr struct

    serv_addr.sin_family = AF_INET;  //byte order
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    serv_addr.sin_port = htons(portno); //short int to n/w byte order

    pair<string,string> hostname_ip = get_hostname_ip();
    cout << "hostname: " << hostname_ip.first << ", ip: " << hostname_ip.second << endl;

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
       error("error on binding");

    listen(sockfd,5);

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
    	//error("error connecting to server");
    	return -1;
    }
	return sockfd;
}

char* communicate_with_server(int sockfd, char *buffer, int buffersize) {
	//bzero(buffer, buffersize);
	int n = send(sockfd, buffer, buffersize,0);
	if (n < 0)
		perror("ERROR writing to socket");
	//printf("[%s]\n", buffer);
	bzero(buffer, buffersize);
	n = recv(sockfd, buffer, buffersize,0);

	if (n < 0)
		perror("ERROR reading from socket");
	//printf("[%s]\n", buffer);
	close (sockfd);

    return buffer;
}

char* communicate_with_server2(int sockfd, char *buffer, int buffersize,  int piece_size, int piece_idx) {
    //bzero(buffer, buffersize);
    int n = send(sockfd, buffer, buffersize,0);
    if (n < 0)
        perror("ERROR writing to socket");

    char payload_length [4]; 

    //printf("[%s]\n", buffer);
    bzero(payload_length, 4);
    n = recv(sockfd, payload_length, 4,0);

    int* pl = (int*)payload_length;
    printf("%d - %x\n", *pl, *pl);

    cout << "PAYLOAD LENGTH TO RECEIVE: " << *pl << endl;

    char* piece_data = (char *)malloc(piece_size);
    bzero(piece_data,piece_size);
    //size_t len = sizeof(piece_data);
    int len = *pl;
    char *p = piece_data;
    n=0;
    do{
        p += n; //move the pointer
        n=recv(sockfd,p,len,0);
        len = len - n;
    }while(len > 0 & n > 0);

    if ( len > 0 || n < 0 ) {
          cout << "something amiss: l = "<<len << ", n = " << n << endl;
    }
    //printf("[%s]\n", buffer);
    close (sockfd);
    cout << "BYTES RECEIVED: " << (*pl - len) << endl;
    write_to_file("./debug", to_string(piece_idx)+"_"+to_string((*pl - len))+"_of_"+to_string(piece_size)+string(".txt"), string(piece_data));
    if(piece_idx==1)
        cout << piece_data << endl;
    return piece_data;
}

char* communicate_with_server_ld(int sockfd, char *buffer, int buffersize) {
    //bzero(buffer, buffersize);
    int n = send(sockfd, buffer, buffersize,0);
    if (n < 0)
        perror("ERROR writing to socket");

    char payload_length [4]; 

    //printf("[%s]\n", buffer);
    bzero(payload_length, 4);
    n = recv(sockfd, payload_length, 4,0);

    int* pl = (int*)payload_length;
    printf("%d - %x\n", *pl, *pl);

    cout << "PAYLOAD LENGTH TO RECEIVE: " << *pl << endl;

    char* response_data = (char *)malloc(*pl);
    bzero(response_data,*pl);
    //size_t len = sizeof(piece_data);
    int len = *pl;
    char *p = response_data;
    n=0;
    do{
        p += n; //move the pointer
        n=recv(sockfd,p,len,0);
        len = len - n;
    }while(len > 0 & n > 0);

    if ( len > 0 || n < 0 ) {
          cout << "something amiss: l = "<<len << ", n = " << n << endl;
    }
    //printf("[%s]\n", buffer);
    close (sockfd);
    cout << "BYTES RECEIVED: " << (*pl - len) << endl;
    /*write_to_file("./debug", to_string(piece_idx)+"_"+to_string((*pl - len))+"_of_"+to_string(piece_size)+string(".txt"), string(piece_data));
    if(piece_idx==1)
        cout << piece_data << endl;*/
    return response_data;
}

char* communicate_with_server_one_way(int sockfd, char *buffer, int buffersize) {
    //bzero(buffer, buffersize);
    int n = send(sockfd, buffer, buffersize,0);
    if (n < 0)
        perror("ERROR writing to socket");
    //printf("[%s]\n", buffer);
    bzero(buffer, buffersize);
    /*n = recv(sockfd, buffer, buffersize-1,0);

    if (n < 0)
        perror("ERROR reading from socket");
    //printf("[%s]\n", buffer);
    close (sockfd);*/

    return buffer;
}

pair<string, string> get_hostname_ip(){
    char host_buffer[512]; 
    char *ip_buffer; 
    struct hostent *host_entry; 
    int host_name_ret; 
  
    host_name_ret = gethostname(host_buffer, sizeof(host_buffer)); 
    host_entry = gethostbyname(host_buffer); 
    /*if (host_entry == NULL|| host_name_ret == NULL) 
        error("gethost details");*/
  
    ip_buffer = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0])); 
    return make_pair(string(host_buffer), string(ip_buffer));
}



