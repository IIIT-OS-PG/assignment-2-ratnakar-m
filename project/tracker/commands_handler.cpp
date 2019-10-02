#include <assign2.h>

char* serve_command(char* command_line) {

	char* from_client = strtok(command_line, "=>");
	char* command = strtok(NULL, "=>");
	command = strtok(command, " ");
	if(command==NULL)
		return "";
	cout << "command received: " << command << endl;
	if(strcmp(command, "create_user")==0) {
		char* username = strtok(NULL, " ");
		char* passwd = strtok(NULL, " ");
		if(username !=NULL && passwd !=NULL)
			return create_user(username, passwd);
	} 
	else if(strcmp(command, "login")==0) {
		char* username = strtok(NULL, " ");
		char* passwd = strtok(NULL, " ");
		if(username !=NULL && passwd !=NULL)
		{
			return login(username, passwd);
		}
	} 
	else if(strcmp(command, "create_group")==0) {
		char* group_id = strtok(NULL, " ");
		char* owner = strtok(NULL, " ");
		if(group_id !=NULL && owner !=NULL)
			return create_group(group_id, owner);
	} 
	else if(strcmp(command, "join_group")==0) {
		char* group_id = strtok(NULL, " ");
		char* username = strtok(NULL, " ");
		if(group_id !=NULL && username !=NULL)
			return join_group(group_id, username);
	}
	else if(strcmp(command, "leave_group")==0) {
		char* group_id = strtok(NULL, " ");
		char* username = strtok(NULL, " ");
		if(group_id !=NULL && username !=NULL)
			return leave_group(group_id, username);
	}  
	else if(strcmp(command, "list_requests")==0) {
		char* group_id = strtok(NULL, " ");
		if(group_id !=NULL)
			return list_requests(group_id);

	} 
	else if(strcmp(command, "accept_request")==0) {
		char* group_id = strtok(NULL, " ");
		char* username = strtok(NULL, " ");
		if(group_id !=NULL && username !=NULL)
			return accept_request(group_id, username);

	} 
	else if(strcmp(command, "list_groups")==0) {
		return list_groups();
	} 
	else if(strcmp(command, "list_files")==0) {
		char* group_id = strtok(NULL, " ");
		if(group_id !=NULL)
			return list_files(group_id);
	} 
	else if(strcmp(command, "upload_file")==0) {
		char* file_path = strtok(NULL, " ");
		char* group_id = strtok(NULL, " ");
		
		if(file_path != NULL && group_id !=NULL)
			return upload_file(file_path, group_id);
	} 
	else if(strcmp(command, "download_file")==0) {
		
		char* group_id = strtok(NULL, " ");
		char* file_name = strtok(NULL, " ");
		char* dest_path = strtok(NULL, " ");
		
		if(group_id !=NULL && file_name != NULL && dest_path!= NULL)
			return download_file(group_id,file_name,dest_path );
	} 
	else if(strcmp(command, "show_downloads")==0) {
		return show_downloads();
	} 
	else if(strcmp(command, "stop_share")==0) {
		char* group_id = strtok(NULL, " ");
		char* file_name = strtok(NULL, " ");
		
		if(group_id !=NULL && file_name != NULL)
			return stop_share(group_id,file_name);
	}
	else if(strcmp(command, "logout")==0) {
		char* username = strtok(NULL, " ");
		
		if(username !=NULL)
			return logout(username);
	} 
	else if(strcmp(command, "username")==0) {
		char* username = strtok(NULL, " ");
		return logout(username);
	} 
	char* bad_command = "Bad Command. Please type 'help' for more details";
	return bad_command;
}
