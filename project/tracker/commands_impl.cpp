#include <assign2.h>

char* create_user(char* username, char* password){
	cout << "username: " << string(username) << ", password: "<< string(password) << endl;
	cout << "user created" << endl;
	string username_str=string(username);
	string password_str=string(password);
	ofstream outfile;
	outfile.open("users.txt", ios::out | ios::app);
	outfile << username_str+":"+password_str<<endl;
	outfile.close();
	return SUCCESS_MSG;
}
char* login(char* username, char* password){
	ifstream infile("users.txt");
	std::string line;
	char* login_msg = "Login Failed";
	while (std::getline(infile, line))
	{
	    istringstream iss(line);
	    char* existing_user = strtok((char*)line.c_str(), ":");
	    char* existing_password = strtok(NULL, ":");
	    if(existing_user != NULL && existing_password != NULL)
	    {
	    	if(strcmp(existing_user, username)==0 && strcmp(existing_password, password)==0)
	    	{
	    		login_msg="Login Successful";	
	    		break;
	    	}
	    }
	}
	return login_msg;
}
char* create_group(char* group_id, char* owner){
	cout << "group_id: " << group_id << ", owner: "<< owner << endl;
	string group_id_str=string(group_id);
	string owner_str=string(owner);
	ofstream outfile;
	outfile.open("groups.txt", ios::out | ios::app);
	outfile << group_id_str+":"+owner_str<<+":"+owner_str<<endl;
	outfile.close();
	return SUCCESS_MSG;
}
char* join_group(char* group_id, char* username){
	cout << "group_id: " << group_id << ", username: "<< username << endl;
	cout << "group joined" << endl;
	return SUCCESS_MSG;
}
char* leave_group(char* group_id, char* username){
	cout << "group_id: " << group_id << ", username: "<< username << endl;
	cout << "group left" << endl;
	return SUCCESS_MSG;
}
char* list_requests(char* group_id){
	cout << "group_id: " << group_id << endl;
	cout << "requested listed" << endl;
	return SUCCESS_MSG;
}
char* accept_request( char* group_id, char* username){
	cout << "group_id: " << group_id << ", username: "<< username << endl;
	cout << "request accepted" << endl;
	return SUCCESS_MSG;
}
char* list_groups(){
	cout << "groups listed" << endl;
	return SUCCESS_MSG;
}
char* list_files(char* group_id){
	cout << "group_id: " << group_id << endl;
	cout << "files listed" << endl;
	return SUCCESS_MSG;
}
char* upload_file(char* file_path, char* group_id){
	cout << "file_path: " << file_path << ", group_id: "<< group_id << endl;
	cout << "uploaded file" << endl;
	return SUCCESS_MSG;
}
char* download_file(char* group_id, char* file_name, char* destination_path){
	cout << "group_id: " << group_id << "file_name: " << file_name << ", destination_path: "<< destination_path << endl;
	cout << "downloaded file" << endl;
	return NULL;
}
char* show_downloads(){
	cout << "downloads shown..." << endl;
	return SUCCESS_MSG;
}
char* stop_share(char* group_id, char* file_name){
	cout << "group_id: " << group_id << "file_name: " << file_name << endl;
	cout << "stopped sharing" << endl;
	return SUCCESS_MSG;
}
char* logout(char* username){
	cout << "logged out" << endl;
	return SUCCESS_MSG;
}
