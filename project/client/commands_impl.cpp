#include <assign2.h>

char* create_user(char* username, char* password){
	cout << "username: " << string(username) << ", password: "<< string(password) << endl;
	cout << "user created" << endl;
	return NULL;
}
bool login(char* username, char* password){
	cout << "username: " << username << ", password: "<< password << endl;
	cout << "logged in" << endl;
	return true;
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
