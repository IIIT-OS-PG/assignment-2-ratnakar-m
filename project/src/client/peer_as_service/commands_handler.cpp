#include <assign2.h>
#include <client.h>

char* serve_command(char* command_line, int* logfd) {
	char* from_client = strtok(command_line, "=>");
	char* command_part = strtok(NULL, "=>");
	if(command_part==NULL)
		return "";

	char* command = strtok(command_part, " ");
	
	char* response = "";
	if(strcmp(command, "get_pieces_info")==0) {
		char* file_name = strtok(NULL, " ");
		
		string meta_file_name=strip_extn(file_name);
		string full_path = string("./pieces_info")+string("/")+string(meta_file_name)+string(string(".meta"));	    
	    bool does_file_exist = piece_info_exists((char*)full_path.c_str());
	    if(!does_file_exist)
	    	response = "get_pieces_info: file does not exist";

		response = read_from_file(string("./pieces_info"), string(meta_file_name)+string(".meta"));
	} 
	if(strcmp(command, "download_piece")==0) {
		char* file_name = strtok(NULL, " ");
		char* piece_idx_arr = strtok(NULL, " ");
		char* piece_size_arr = strtok(NULL, " ");
		int piece_idx = atoi(piece_idx_arr);
		int piece_size = atoi(piece_size_arr);

		string full_path = string("./resources/")+string(file_name);
		char* piece_data = read_piece_data_from_file(full_path, piece_idx, piece_size);
		
		response = piece_data;
	} 
	return response;
}