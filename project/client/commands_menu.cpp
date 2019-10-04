#include <assign2.h>
#include <client.h>


void manage_prompt() {
		
	tracker_status_check();

	reset_prompt();
	bzero((char *) &current_user, sizeof(char));

	while(strcmp(manage_menu(),"exit") != 0) {
		reset_prompt();
	}
}

void reset_prompt() {
	if(current_user==NULL)
		cout << "peer>";
	else
		cout << "peer~"+string(current_user)+">";
	fflush(stdin);
}

char * manage_menu() {
	char input[500];
	fgets(input, 500, stdin);
	char * command;
	char tempInput[500];
	strcpy(tempInput, input);
	command = strtok(input, "\n");
	command = strtok(input, " ");
	char* response = (char *) malloc(BUFFER_SIZE * sizeof(char * )) ;
	bzero(response,BUFFER_SIZE);
	if(strcmp(command, "create_user")==0) {
		char* username = strtok(NULL, " ");
		char* passwd = strtok(NULL, " ");
		if(username !=NULL && passwd !=NULL)
		{
			response = create_user(username, passwd);
		}
		else
			cout << "invalid args. type 'help' for more details." << endl;
	} 
	else if(strcmp(command, "login")==0) {
		char* username = strtok(NULL, " ");
		char* passwd = strtok(NULL, " ");
		if(username !=NULL && passwd !=NULL)
		{
			response = login(username, passwd);
			if(strcmp(response, "login successful")==0)
				current_user = clone(username);
		}
		else
			cout << "invalid args. type 'help' for more details." << endl;

	} 
	else if(strcmp(command, "create_group")==0) {
		if(current_user!=NULL)
		{
			char* group_id = strtok(NULL, " ");
		
			if(group_id !=NULL)
				response = create_group(group_id,current_user);
			else
				cout << "invalid args. type 'help' for more details." << endl;
		}
		else
			cout << "You need to login to create a group" << endl;

		
	} 
	else if(strcmp(command, "join_group")==0) {
		char* group_id = strtok(NULL, " ");
		
		if(group_id !=NULL)
			join_group(group_id,current_user);
		else
			cout << "invalid args. type 'help' for more details." << endl;

	}
	else if(strcmp(command, "leave_group")==0) {
		char* group_id = strtok(NULL, " ");
		
		if(group_id !=NULL)
			response = leave_group(group_id, current_user);
		else
			cout << "invalid args. type 'help' for more details." << endl;

	}  
	else if(strcmp(command, "list_requests")==0) {
		char* group_id = strtok(NULL, " ");
		
		if(group_id !=NULL)
			response = list_requests(group_id);
		else
			cout << "invalid args. type 'help' for more details." << endl;

	} 
	else if(strcmp(command, "accept_request")==0) {

		if(current_user == NULL)
			response="You must be logged in to accept requests";
		else{
			char* group_id = strtok(NULL, " ");
			char* username = strtok(NULL, " ");
			
			if(group_id !=NULL && username != NULL)
				response=accept_request(group_id,current_user,username);
			else
				cout << "invalid args. type 'help' for more details." << endl;
		}
	} 
	else if(strcmp(command, "list_groups")==0) {
		response = list_groups();
	} 
	else if(strcmp(command, "list_files")==0) {
		char* group_id = strtok(NULL, " ");
		
		if(group_id !=NULL)
			list_files(group_id);
		else
			cout << "invalid args. type 'help' for more details." << endl;
	} 
	else if(strcmp(command, "upload_file")==0) {
		char* file_path = strtok(NULL, " ");
		char* group_id = strtok(NULL, " ");
		
		if(file_path != NULL && group_id !=NULL)
		{
			string base_name = get_base_name(string(file_path));
			vector<chunk_info> chunks;
			string file_sha1 = split_chunks(file_path, chunks);
			response = upload_file(file_path, group_id, (char*) file_sha1.c_str());
		}
		else
			cout << "invalid args. type 'help' for more details." << endl;

	} 
	else if(strcmp(command, "download_file")==0) {
		
		char* group_id = strtok(NULL, " ");
		char* file_name = strtok(NULL, " ");
		char* dest_path = strtok(NULL, " ");
		
		if(group_id !=NULL && file_name != NULL && dest_path!= NULL)
			response = download_file(group_id,file_name,dest_path );
		else
			cout << "invalid args. type 'help' for more details." << endl;

	} 
	else if(strcmp(command, "show_downloads")==0) {
		response = show_downloads();
	} 
	else if(strcmp(command, "stop_share")==0) {
		char* group_id = strtok(NULL, " ");
		char* file_name = strtok(NULL, " ");
		
		if(group_id !=NULL && file_name != NULL)
			response = stop_share(group_id,file_name);
		else
			cout << "invalid args. type 'help' for more details." << endl;

	} 
	else if(strcmp(command, "logout")==0) {
		if(current_user == NULL)
			response="not logged in yet";
		else
		{
			response=logout(current_user);
			if(strcmp(response, "logout successful")==0){
				current_user = NULL;
			}
		}
	} 
	else if(strcmp(command, "help")==0) {
		help();
	}
	else if(strcmp(command, "whoami")==0) {
		if(current_user!=NULL)
			cout << string(current_user) << endl;
	}  
	else {
		cout << "bad command, type 'help' to get list of commands\n" << endl;
	}

	cout << response << endl;
	return command;
}

void help(){
	cout << "Following is the list of commands..." << endl;
	cout << endl;
	cout << "1. create_user <user_id> <passwd>" << endl;
	cout << "2. login <user_id> <passwd>" << endl;
	cout << "3. create_group <group_id>" << endl;
	cout << "4. join_group <group_id>" << endl;
	cout << "5. leave_group <group_id>" << endl;
	cout << "6. list_requests <group_id>" << endl;
	cout << "7. list_requests <group_id>" << endl;
	cout << "8. list_groups" << endl;
	cout << "9. list_files <group_id>" << endl;
	cout << "10. upload_file <file_path> <group_id>" << endl;
	cout << "11. download_file <group_id> <file_name> <destination_path>" << endl;
	cout << "12. show_downloads" << endl;
	cout << "13. stop_share <group_id> <file_name>" << endl;
	cout << "14. logout" << endl;
	cout << endl;
}