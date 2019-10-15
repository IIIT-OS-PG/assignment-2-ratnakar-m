#include <assign2.h>
#include <client.h>

/*
this file represents the operations of a peer as a requestor to another peer
outbound requests
*/
Value get_pieces_info(char* peer_addr, char* file_name){
	string command_str = string("get_pieces_info ") + string(file_name);
	cout << "sending request: " << command_str << endl;
	pair<int,char*> command_msg = get_msg(command_str);
	char* pieces_info_str = send_cmd_to_peer(peer_addr, command_msg.second);
	Value pieces_info_root;
	Reader reader;
	bool parsing_status = reader.parse( pieces_info_str, pieces_info_root );
    if(!parsing_status)
    	return "issues on parsing pieces info";
	return pieces_info_root;
}

char* get_pieces_info_str(char* peer_addr, char* file_name){
	string command_str = string("get_pieces_info ") + string(file_name);
	cout << "sending request: " << command_str << endl;
	pair<int,char*> command_msg = get_msg(command_str);
	//char* pieces_info_str = send_cmd_to_peer(peer_addr, command_msg.second);
	char* pieces_info_str = send_cmd_to_peer_ld(peer_addr, command_msg.second);
	return pieces_info_str;
}

char* download_piece(char* peer_addr, char* file_name, int piece_idx, int piece_size){
	string command_str = string("download_piece ") + string(file_name) + string(" ") + to_string(piece_idx) + string(" ") + to_string(piece_size);
	pair<int,char*> command_msg = get_msg(command_str);
	char* piece_data = send_cmd_to_peer2(peer_addr, command_msg.second,piece_size,piece_idx);
	char* mybuff = (char *)malloc(piece_size);
    bzero(mybuff,piece_size);
    memcpy(mybuff,piece_data, piece_size);
	//return clone2(piece_data, piece_size);
	if(piece_idx==1)
    {
    	cout << "********************peer_com.download_piece()************************** " << endl;
    	cout << "************************************************************************ " << endl;
    	cout << mybuff << endl;
    }
	return piece_data;
}

char* send_cmd_to_peer2(char* peer_addr, char* command, int piece_size, int piece_idx) {
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
		response = communicate_with_server2(*peer_addr_struct.sockfd, buffer, BUFFER_SIZE, piece_size, piece_idx);
	}
	else
		sprintf(response, "Unable to connect to the peer: [%s:%d]. Make sure it is up.", host, *portno); 

	char* mybuff = (char *)malloc(piece_size);
    bzero(mybuff,piece_size);
    memcpy(mybuff,response, piece_size);
    if(piece_idx==1)
    {
    	cout << "****************************peer_com.send_cmd_to_peer2()**************************** " << endl;
    	cout << "************************************************************************ " << endl;
    	cout << mybuff << endl;
    }
	return mybuff;   
}

char* send_cmd_to_peer_ld(char* peer_addr, char* command) {
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
		response = communicate_with_server_ld(*peer_addr_struct.sockfd, buffer, BUFFER_SIZE);
	}
	else
		sprintf(response, "Unable to connect to the peer: [%s:%d]. Make sure it is up.", host, *portno); 

	/*char* mybuff = (char *)malloc(piece_size);
    bzero(mybuff,piece_size);
    memcpy(mybuff,response, piece_size);
    if(piece_idx==1)
    {
    	cout << "****************************peer_com.send_cmd_to_peer2()**************************** " << endl;
    	cout << "************************************************************************ " << endl;
    	cout << mybuff << endl;
    }
	return mybuff;  */
	cout << "(client) FILE INFO" << endl;
      cout << response << endl;
	return response; 
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
	//cout <<" connecting to peer: " << host << ":" << to_string(*port) << endl;
	*peer_addr.sockfd = connect_server(host,*port);
	//cout <<" sockfd: " << *peer_addr.sockfd << endl;
	return peer_addr;
}
