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
char* accept_request( char* group_id, char* owner, char* subject){
	string command = string("accept_request ")+string(group_id)+string(" ")+string(owner)+string(" ")+string(subject);
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
char* upload_file(char* file_name, char* group_id, char* username, char* file_meta){
	string command = string("upload_file ")+string(file_name)+string(" ")+string(group_id)+string(" ")+string(username)+string("\n")+string(HEADER_AND_BODY_SEPARATOR)+string("\n")+file_meta;
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

char* build_metadata_for_tracker(string file_name, string group_id, pair<string,int> file_info, vector<chunk_info> chunks){
	Value meta; 
    meta["name"] = file_name;
    meta["group"] = group_id;
    meta["file_sha1"] = file_info.first;
    meta["size"] = file_info.second;
    meta["pieces"] = Value(arrayValue);
    meta["num_pieces"] = (int)chunks.size();
    pair<string,string> hostname_ip = get_hostname_ip();
	string ip = hostname_ip.second;
    for(int i=0; i<chunks.size(); i++){
    	append_piece(meta,i,*chunks[i].size,chunks[i].sha1,ip);
    }
    StyledWriter writer;
    string meta_str = writer.write( meta );
    //cout << root << endl; //printing using the root itself
    //cout << meta_str << endl; //printing using the string of root
    return (char*)meta_str.c_str();
}

char* build_metadata_for_self(string file_name, string group_id, pair<string,int> file_info, vector<chunk_info> chunks){
	Value meta; 
    meta["name"] = file_name;
    meta["group"] = group_id;
    meta["file_sha1"] = file_info.first;
    meta["size"] = file_info.second;
    meta["num_pieces"] = (int)chunks.size();
    meta["status"] = "COMPLETED";
    meta["pieces"] = Value(arrayValue);
    pair<string,string> hostname_ip = get_hostname_ip();
	string ip = hostname_ip.second;
    for(int i=0; i<chunks.size(); i++){
    	append_piece(meta,i,*chunks[i].size,chunks[i].sha1,ip);
    }
    StyledWriter writer;
    string meta_str = writer.write( meta );
    //cout << root << endl; //printing using the root itself
    //cout << meta_str << endl; //printing using the string of root
    return (char*)meta_str.c_str();
}

void append_piece(Value& document, int idx, int size, string sha1, string ip){
    Value piece;
    piece["piece_no"] = idx;
    piece["piece_size"] = size;
    piece["piece_sha1"] = sha1;
    piece["peers"] = Value(arrayValue);
    string peer_addr = ip + string(":") + to_string(*(peer_context.portno));
    piece["peers"].append(peer_addr);
    document["pieces"].append(piece);
}
