#include "commons.h"

string create_user(string username, string password){
	cout << "user created" << endl;
}
string login(string username, string password){
	cout << "logged in" << endl;
}
string create_group(string group_id, string owner){
	cout << "group created" << endl;
}
string join_group(string group_id, string username){
	cout << "group joined" << endl;
}
string leave_group(string group_id, string username){
	cout << "group left" << endl;
}
string list_requests(string group_id){
	cout << "requested listed" << endl;
}
string accept_request( string group_id, string username){
	cout << "request accepted" << endl;
}
string list_groups(){
	cout << "groups listed" << endl;
}
string list_files(string group_id){
	cout << "files listed" << endl;
}
string upload_file(string file_path, string group_id){
	cout << "uploaded file" << endl;
}
string download_file(string group_id, string file_name, string destination_path){
	cout << "downloaded file" << endl;
}
string show_downloads(){
	cout << "downloads shown..." << endl;
}
string stop_share(string group_id, string file_name){
	cout << "stopped sharing" << endl;
}
string logout(){
	cout << "logged out" << endl;
}