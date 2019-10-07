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

char* get_file_info(char* group_id, char* file_name, char* user_name){
	string command = string("get_file_info ")+string(group_id)+string(" ")+string(file_name)+string(" ")+string(user_name);
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
    
    meta["total_pieces"] = (int)chunks.size();
    pair<string, int*> host_port = get_hostname_port();
    string host_port_str = host_port.first+string(":")+to_string(*host_port.second);
    Value seeders;

    seeders[host_port_str]="ACTIVE";
    meta["seeders"]=seeders;
    //commented below as pieces info is not required at tracker side
    /*meta["pieces"] = Value(arrayValue); 
    for(int i=0; i<chunks.size(); i++){
    	append_piece(meta,i,*chunks[i].size,chunks[i].sha1,host_port.first);
    }*/

    StyledWriter writer;
    string meta_str = writer.write( meta );
    //cout << root << endl; //printing using the root itself
    //cout << meta_str << endl; //printing using the string of root    
    char* ret =  clone((char*)meta_str.c_str());
    return ret;
}

char* build_metadata_for_self(string file_name, string group_id, pair<string,int> file_info, vector<chunk_info> chunks){
	Value meta; 
    meta["name"] = file_name;
    meta["group"] = group_id;
    meta["file_sha1"] = file_info.first;
    meta["size"] = file_info.second;
    meta["total_pieces"] = (int)chunks.size();
    meta["available_pieces"] = (int)chunks.size();
    meta["status"] = "COMPLETED";
    Value pieces;
    //meta["pieces"] = Value(arrayValue); //array of pieces
    //changing from array of pieces to dictionary of pieces with index as piece idx
    
    pair<string, int*> host_port = get_hostname_port();
    string from_peer=string(host_port.first)+string(":")+to_string(*host_port.second);

    for(int i=0; i<chunks.size(); i++){
    	Value piece;
	    piece["piece_no"] = i;
	    piece["piece_size"] = *chunks[i].size;
	    piece["piece_sha1"] = chunks[i].sha1;
	    piece["from_peer"] = from_peer;

	    pieces[to_string(i)] = piece;

    }
    meta["pieces"] = pieces;
    StyledWriter writer;
    string meta_str = writer.write( meta );
    //cout << root << endl; //printing using the root itself
    //cout << meta_str << endl; //printing using the string of root
    return (char*)meta_str.c_str();
}

void add_piece(Value& document, int idx, int size, string sha1, string from_peer){}
