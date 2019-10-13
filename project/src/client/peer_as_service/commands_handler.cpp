#include <assign2.h>
#include <client.h>

pair<int, char*> serve_command(char* command_line, int* logfd) {
	char* from_client = strtok(command_line, "=>");
	char* command_part = strtok(NULL, "=>");
	if(command_part==NULL)
		return make_pair(0,(char*)"");

	char* command = strtok(command_part, " ");
	
	pair<int,char*> response;
	if(strcmp(command, "get_pieces_info")==0) {
		char* file_name = strtok(NULL, " ");
		
		char* response_str;
		string meta_file_name=strip_extn(file_name);
		string full_path = string("./pieces_info")+string("/")+string(meta_file_name)+string(string(".pieces_info"));	    
	    bool does_file_exist = piece_info_exists((char*)full_path.c_str());
	    if(!does_file_exist)
	    	return make_pair(0,(char*)"get_pieces_info: file does not exist");

		response_str = read_from_file_large_data(string("./pieces_info"), string(meta_file_name)+string(".pieces_info"));
		response = make_pair(strlen(response_str),response_str);
		//cout << "PIECES INFO: " << endl;
		//cout << response << endl;
		//cout << "PIECES INFO COMPLETE: " << endl;
	} 
	if(strcmp(command, "download_piece")==0) {
		char* file_name = strtok(NULL, " ");
		char* piece_idx_arr = strtok(NULL, " ");
		char* piece_size_arr = strtok(NULL, " ");
		int piece_idx = atoi(piece_idx_arr);
		int piece_size = atoi(piece_size_arr);

		string full_path = string("./resources/")+string(file_name);
		char* piece_data = read_piece_data_from_file(full_path, piece_idx, piece_size);
		
		//response = piece_data;
		response = make_pair(piece_size,piece_data);
		//cout << piece_data << endl;
	} 
	return response;
}