#include "commons.h"

string create_user(char* username, char* password){
	cout << "username: " << string(username) << ", password: "<< string(password) << endl;
	cout << "user created" << endl;
	return "";
}
string login(string username, string password){
	cout << "username: " << username << ", password: "<< password << endl;
	cout << "logged in" << endl;
}
string create_group(string group_id, string owner){
	cout << "group_id: " << group_id << ", owner: "<< owner << endl;
	cout << "group created" << endl;
}
string join_group(string group_id, string username){
	cout << "group_id: " << group_id << ", username: "<< username << endl;
	cout << "group joined" << endl;
}
string leave_group(string group_id, string username){
	cout << "group_id: " << group_id << ", username: "<< username << endl;
	cout << "group left" << endl;
}
string list_requests(string group_id){
	cout << "group_id: " << group_id << endl;
	cout << "requested listed" << endl;
}
string accept_request( string group_id, string username){
	cout << "group_id: " << group_id << ", username: "<< username << endl;
	cout << "request accepted" << endl;
}
string list_groups(){
	cout << "groups listed" << endl;
}
string list_files(string group_id){
	cout << "group_id: " << group_id << endl;
	cout << "files listed" << endl;
}
string upload_file(string file_path, string group_id){
	cout << "file_path: " << file_path << ", group_id: "<< group_id << endl;
	cout << "uploaded file" << endl;
}
string download_file(string group_id, string file_name, string destination_path){
	cout << "group_id: " << group_id << "file_name: " << file_name << ", destination_path: "<< destination_path << endl;
	cout << "downloaded file" << endl;
}
string show_downloads(){
	cout << "downloads shown..." << endl;
}
string stop_share(string group_id, string file_name){
	cout << "group_id: " << group_id << "file_name: " << file_name << endl;
	cout << "stopped sharing" << endl;
}
string logout(){
	cout << "logged out" << endl;
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