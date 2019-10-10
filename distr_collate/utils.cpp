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


char* clone(char* orig){ //based on '\0'
    char* cl = (char *) malloc(BUFFER_SIZE*sizeof(char));
    int g = 0;
    while(orig[g] != '\0')
    {
        cl[g] = orig[g];
        g++;
    }
    cl[g]='\0';

    return cl;
}

char* clone3(string orig){
    char* cstr = (char *) malloc((orig.size())*sizeof(char));
    strcpy(cstr, orig.c_str());
    return cstr;
}

char* clone2(char* orig, int size){ //make sure size <=BUFFER_SIZE
    char* cl = (char *) malloc(BUFFER_SIZE*sizeof(char));
    for(int g=0; g<size; g++){
        cl[g] = orig[g];
        g++;
    }

    return cl;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

pair<string,int> split_chunks(string file_path, vector<chunk_info>& chunks) {

    ifstream inStream(file_path);
    if(!inStream)
      return make_pair("",-1);
    unique_ptr<char[]> buffer(new char[BUFFER_SIZE]);

    string result;
    int total_size=0;

    int i=1;
    do {
        chunk_info chunk;
        inStream.read(buffer.get(), BUFFER_SIZE);
        //unsigned char* hash = get_hash(buffer.get());
        string digest = get_hash_digest(buffer.get());

        result = result + digest;
        //cout << "digest: " << digest << endl;
        int *chunk_size = (int *) malloc(sizeof(int));
        *chunk_size=inStream.gcount();
        total_size=total_size + (*chunk_size);
        chunk.sha1=digest;
        chunk.size=chunk_size;
        chunk.data=clone2(buffer.get(),*chunk_size);
        chunks.push_back(chunk);
        
        
    } while (!inStream.eof()) ;
    return make_pair(result,total_size);
}

string get_hash_digest(char* str1){
  const unsigned char* str = (const unsigned char*)str1;
  unsigned char* hash = (unsigned char *) malloc(SHA_DIGEST_LENGTH);
  SHA1(str, sizeof(str) - 1, hash);
  char* mdString = (char *) malloc(SHA_DIGEST_LENGTH*2+1);
  for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)hash[i]);

  return mdString;
}