#include <assign2.h>
#include <tracker.h>

char* create_user(char* username, char* password){
	if(user_exists(username))
		return "user already exists";
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
	string line;
	char* login_msg = "login failed";
	while (getline(infile, line))
	{
	    istringstream iss(line);
	    char* existing_user = strtok((char*)line.c_str(), ":");
	    char* existing_password = strtok(NULL, ":");
	    if(existing_user != NULL && existing_password != NULL)
	    {
	    	if(strcmp(existing_user, username)==0 && strcmp(existing_password, password)==0)
	    	{
	    		login_msg="login successful";	
	    		break;
	    	}
	    }
	}
	return login_msg;
}
char* create_group(char* group_id, char* owner){
	if(group_exists(group_id))
		return "group already exists";
	cout << "group_id: " << group_id << ", owner: "<< owner << endl;
	string group_id_str=string(group_id);
	string owner_str=string(owner);
	ofstream outfile;
	outfile.open("groups.txt", ios::out | ios::app);
	outfile << group_id_str+":"+owner_str<<endl;
	outfile.close();

	ofstream memberfile;
	memberfile.open("membership.txt", ios::out | ios::app);
	memberfile << group_id_str+":"+owner_str<<endl;
	memberfile.close();

	string response = "group created";
	return (char*)response.c_str();
}
char* join_group(char* group_id, char* username){
	if(request_exists(group_id,username))
		return "You have already raised a join request for this group. It is still pending acceptance.";
	ofstream outfile;
	outfile.open("join_requests.txt", ios::out | ios::app);
	string group_id_str=string(group_id);
	string username_str=string(username);
	outfile << group_id_str+":"+username_str<<endl;
	outfile.close();

	return "Sent a join request to the group owner. Please wait for acceptance.";
}
char* leave_group(char* group_id, char* username){
	string deleteline = string(group_id)+":"+string(username);
	delete_line("groups.txt",deleteline);

	return "user left from the group";
}
char* list_requests(char* group_id){
	char* requests = get_requests();
	return requests;
}
char* accept_request( char* group_id, char* owner, char* username){ 

	bool isowner = is_owner(group_id, owner);
	if(!isowner)
		return "You are not the owner of this group. You must be owner to accept requests";

	string group_id_str=string(group_id);
	string username_str=string(username);

	//add user to the membership list
	ofstream outfile;
	outfile.open("membership.txt", ios::out | ios::app);
	outfile << group_id_str+":"+username_str<<endl;
	cout << "accepting membership "  << group_id_str+":"+username_str<<endl;
	outfile.close();

	//remove from pending requests
	string deleteline = group_id_str+":"+username_str;
	delete_line("join_requests.txt",deleteline);

	return "join request has been accepted";
}
char* list_groups(){
	return get_groups();
}
char* list_files(char* group_id){
	cout << "group_id: " << group_id << endl;
	cout << "files listed" << endl;
	return SUCCESS_MSG;
}
char* upload_file(char* file_name, char* group_id, char* file_meta){
	cout << "file_name: " << file_name << ", group_id: "<< group_id << ", file_meta: " << file_meta << endl;
	string meta_file_name=strip_extn(file_name);
	write_to_file(string("./metadata"), string(meta_file_name+".meta"), string(file_meta));
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
	cout << string(username) << " logged out" << endl;
	return "logout successful";
}
