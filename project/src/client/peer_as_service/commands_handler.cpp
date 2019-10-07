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
	return response;
}