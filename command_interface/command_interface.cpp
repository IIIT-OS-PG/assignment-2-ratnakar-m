#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

#define PROMPT "peer>"

void managePrompt();
void resetPrompt();
char * manageMenu();
void help();

string current_user="";

int main(){
	managePrompt();
}

void managePrompt() {
	resetPrompt();
	while(strcmp(manageMenu(),"exit") != 0) {
		resetPrompt();
	}
}

void resetPrompt() {
	cout << "peer"+current_user+">";
	fflush(stdin);
}

char * manageMenu() {
	char input[500];
	fgets(input, 500, stdin);
	char * command;
	char tempInput[500];
	strcpy(tempInput, input);
	command = strtok(input, "\n");
	command = strtok(input, " ");
	if(strcmp(command, "create_user")==0) {
		cout << "create_user command" << endl;
	} 
	else if(strcmp(command, "login")==0) {
		cout << "login command" << endl;
	} 
	else if(strcmp(command, "create_group")==0) {
		cout << "create_group command" << endl;
	} 
	else if(strcmp(command, "join_group")==0) {
		cout << "join_group command" << endl;
	}
	else if(strcmp(command, "leave_group")==0) {
		cout << "leave_group command" << endl;
	}  
	else if(strcmp(command, "list_requests")==0) {
		cout << "list_requests command" << endl;
	} 
	else if(strcmp(command, "accept_request")==0) {
		cout << "accept_request command" << endl;
	} 
	else if(strcmp(command, "list_groups")==0) {
		cout << "list_groups command" << endl;
	} 
	else if(strcmp(command, "list_files")==0) {
		cout << "list_files command" << endl;
	} 
	else if(strcmp(command, "upload_file")==0) {
		cout << "upload_file command" << endl;
	} 
	else if(strcmp(command, "download_file")==0) {
		cout << "download_file command" << endl;
	} 
	else if(strcmp(command, "show_downloads")==0) {
		cout << "show_downloads command" << endl;
	} 
	else if(strcmp(command, "stop_share")==0) {
		cout << "stop_share command" << endl;
	} 
	else if(strcmp(command, "logout")==0) {
		cout << "logout command" << endl;
	} 
	else if(strcmp(command, "help")==0) {
		help();
	}
	else if(strcmp(command, "whoami")==0) {
		
	}  
	else {
		cout << "bad command, type 'help' to get list of commands\n" << endl;
	}
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
