#include <assign2.h>
#include <client.h>

/*
this file represents the operations of a peer as a requestor to another peer
outbound requests
*/
Value get_pieces_info(char* peer_addr, char* file_name){
	stringstream command_stream;
	command_stream << "get_pieces_info " << file_name;
	char* command = (char*) command_stream.str().c_str();
	char* pieces_info_str = send_cmd_to_peer(peer_addr, clone(command));
	Value pieces_info_root;
	Reader reader;
	bool parsing_status = reader.parse( pieces_info_str, pieces_info_root );
    if(!parsing_status)
    	return "issues on parsing pieces info";
	return pieces_info_root;
}

char* send_cmd_to_peer(char* peer_addr, char* command) {
	char* host = strtok(peer_addr, ":");
	char* port_str = strtok(NULL, ":");

	int* portno=(int *) malloc(sizeof(int));
	*portno = atoi(port_str);

	peer_ctx peer_addr_struct = connect_peer(host, portno);
	char* response = (char *) malloc(BUFFER_SIZE * sizeof(char * )) ;
	bzero(response,BUFFER_SIZE);
	char buffer[BUFFER_SIZE];
	pair<string, int*> host_port = get_hostname_port(); //extract info from self context
	if(*peer_addr_struct.sockfd > 0){
    	sprintf(buffer, "[%s:%d]=>%s",host_port.first.c_str() ,*host_port.second, command);
    	//send command to other peer
		response = communicate_with_server(*peer_addr_struct.sockfd, buffer, BUFFER_SIZE);
	}
	else
		sprintf(response, "Unable to connect to the peer: [%s:%d]. Make sure it is up.", host, *portno); 

	return response;   
}

peer_ctx connect_peer(char* host, int* port){

	peer_ctx peer_addr;

	peer_addr.sockfd=(int *) malloc(sizeof(int));
	peer_addr.portno=(int *) malloc(sizeof(int));
	peer_addr.host = (char *) malloc(20);
	bzero((char *) &peer_addr.host, sizeof(char));

	int *sockfd = (int *) malloc(sizeof(int));
	*sockfd = -1;
	cout <<" connecting to peer: " << host << ":" << to_string(*port) << endl;
	*peer_addr.sockfd = connect_server(host,*port);
	cout <<" sockfd: " << *peer_addr.sockfd << endl;
	return peer_addr;
}

