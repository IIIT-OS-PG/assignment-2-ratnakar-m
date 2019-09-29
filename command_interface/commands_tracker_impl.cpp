#include "commons.h"

char* create_user(char* username, char* password){
	cout << "username: " << string(username) << ", password: "<< string(password) << endl;
	cout << "user created" << endl;
	string username_str=string(username);
	string password_str=string(password);
	ofstream outfile;
	outfile.open("users.txt", ios::out | ios::app);
	outfile << username_str+":"+password_str<<endl;
	outfile.close();
	return NULL;
}
char* login(char* username, char* password){
	cout << "username: " << username << ", password: "<< password << endl;
	cout << "logged in" << endl;

	ifstream infile("users.txt");
	std::string line;
	bool login_success = false;
	while (std::getline(infile, line))
	{
		cout << "HERE" << endl;
	    istringstream iss(line);
	    char* existing_user = strtok((char*)line.c_str(), ":");
	    char* existing_password = strtok(NULL, ":");
	    if(existing_user != NULL && existing_password != NULL)
	    {
	    	cout << "exist_user: " << existing_user << ", exist_pass: "<<existing_password << endl;
	    	if(strcmp(existing_user, username)==0 && strcmp(existing_password, password)==0)
	    	{
	    		login_success=true;	
	    		break;
	    	}
	    }
	}
	if(login_success)
		cout << "Login Successful" << endl;
	else
		cout << "Login Failed" << endl;
	return NULL;
}
char* create_group(char* group_id, char* owner){
	cout << "group_id: " << group_id << ", owner: "<< owner << endl;
	cout << "group created" << endl;
	return NULL;
}
char* join_group(char* group_id, char* username){
	cout << "group_id: " << group_id << ", username: "<< username << endl;
	cout << "group joined" << endl;
	return NULL;
}
char* leave_group(char* group_id, char* username){
	cout << "group_id: " << group_id << ", username: "<< username << endl;
	cout << "group left" << endl;
	return NULL;
}
char* list_requests(char* group_id){
	cout << "group_id: " << group_id << endl;
	cout << "requested listed" << endl;
	return NULL;
}
char* accept_request( char* group_id, char* username){
	cout << "group_id: " << group_id << ", username: "<< username << endl;
	cout << "request accepted" << endl;
	return NULL;
}
char* list_groups(){
	cout << "groups listed" << endl;
	return NULL;
}
char* list_files(char* group_id){
	cout << "group_id: " << group_id << endl;
	cout << "files listed" << endl;
	return NULL;
}
char* upload_file(char* file_path, char* group_id){
	cout << "file_path: " << file_path << ", group_id: "<< group_id << endl;
	cout << "uploaded file" << endl;
	return NULL;
}
char* download_file(char* group_id, char* file_name, char* destination_path){
	cout << "group_id: " << group_id << "file_name: " << file_name << ", destination_path: "<< destination_path << endl;
	cout << "downloaded file" << endl;
	return NULL;
}
char* show_downloads(){
	cout << "downloads shown..." << endl;
	return NULL;
}
char* stop_share(char* group_id, char* file_name){
	cout << "group_id: " << group_id << "file_name: " << file_name << endl;
	cout << "stopped sharing" << endl;
	return NULL;
}
char* logout(){
	cout << "logged out" << endl;
	return NULL;
}
char* clone(char* orig){
    char* cl = (char *) malloc(100);
    int g = 0;
    while(orig[g] != '\0')
    {
        cl[g] = orig[g];
        g++;
    }
    cl[g]='\0';

    return cl;
}