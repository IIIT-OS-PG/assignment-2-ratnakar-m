#include <assign2.h>
#include <client.h>

char* create_user(char* username, char* password){
	
	string command = string("create_user ")+string(username)+string(" ")+string(password);
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}

char* login(char* username, char* password){
	string command = string("login ")+string(username)+string(" ")+string(password);
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}
char* create_group(char* group_id, char* owner){
	string command = string("create_group ")+string(group_id)+string(" ")+string(owner);
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}
char* join_group(char* group_id, char* username){
	string command = string("join_group ")+string(group_id)+string(" ")+string(username);
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}
char* leave_group(char* group_id, char* username){
	string command = string("leave_group ")+string(group_id)+string(" ")+string(username);
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}
char* list_requests(char* group_id){
	string command = string("list_requests ")+string(group_id);
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}
char* accept_request( char* group_id, char* username){
	string command = string("accept_request ")+string(group_id)+string(" ")+string(username);
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}
char* list_groups(){
	string command = string("list_groups ");
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}
char* list_files(char* group_id){
	string command = string("list_files ")+string(group_id);
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}
char* upload_file(char* file_path, char* group_id){
	string command = string("upload_file ")+string(file_path)+string(" ")+string(group_id);
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}
char* download_file(char* group_id, char* file_name, char* destination_path){
	string command = string("download_file ")+string(group_id)+string(" ")+string(file_name)+string(" ")+string(destination_path);
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}
char* show_downloads(){
	string command = string("show_downloads ");
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}
char* stop_share(char* group_id, char* file_name){
	string command = string("stop_share ")+string(group_id)+string(" ")+string(file_name);
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}
char* logout(char* username){
	string command = string("logout ")+string(username);
	char* response = send_cmd_to_tracker((char*)command.c_str());
	return response;
}
