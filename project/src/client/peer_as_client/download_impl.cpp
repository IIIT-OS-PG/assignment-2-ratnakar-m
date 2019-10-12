#include <assign2.h>
#include <client.h>

char* download_impl(char* group_id, char* file_name, char* dest_path, char* username){
	char* response = (char *) malloc(BUFFER_SIZE * sizeof(char * )) ;

	//download is a multi step process
	//step1: get the peer addresses where the file is available
		//interface in tracker to get the trackers having the file

	//1. get file_info from tracker
	//cout << "in dwnld impl" << endl;
	char* file_info = get_file_info(group_id, file_name, username);
	if(strcmp(file_info, "NOT_A_MEMBER")==0)
		response="user is not a member of the group";
	else if(strcmp(file_info, "NOT_EXIST")==0)
		response="file does not exist";
	else
	{
		Value file_info_root;
	    Reader reader;

	    bool parsing_status = reader.parse( file_info, file_info_root );
	    if(!parsing_status)
	    	return "error parsing the file_info content";

	    int total_pieces = file_info_root["total_pieces"].asInt();

	    if(file_info_root.isMember("seeders")){
	    	Value seeders = file_info_root["seeders"];
	    	vector<string> members = seeders.getMemberNames();
	    	cout << "Seeders Info: " << endl;
	    	int thread_count = members.size();
	    	int thread;
	    	pthread_t* thread_handles = (pthread_t*) malloc(thread_count*sizeof(pthread_t));

	    	piece_info_struct piece_info_ctx;
	    	piece_info_ctx.file_name=file_name;
	    	unordered_map<string, int*> piece_info_stats;
	    	piece_info_ctx.piece_info_stats = &piece_info_stats;

	    	unordered_map<string, Value*> pieces_roots;
	    	piece_info_ctx.pieces_roots = &pieces_roots;

	    	unordered_map<string, Value> pieces_roots_val;
	    	piece_info_ctx.pieces_roots_val = &pieces_roots_val;
	    	cout << "MEMBERS SIZE: " << members.size() << endl;
	    	for(int i=0; i<members.size(); i++)
	    	{
	    		//2. get chunks info from seeders (peers)
	    		//separate threads?
	    		piece_info_ctx.member=members[i];
	    		cout << "MEMBER: " << members[i] << endl;
	    		pthread_create(&thread_handles[thread], NULL, get_pieces_info_func, (void*) &piece_info_ctx);
	    		thread++;
	    	}

	    	for(thread=0; thread < thread_count; thread++)
				pthread_join(thread_handles[thread], NULL);

			for(int i=0; i<members.size(); i++)
	    	{
	    		//available pieces in the members
	    		cout << "size: " << (*piece_info_ctx.piece_info_stats).size() << endl;
	    		cout << members[i] << ": " << *((*piece_info_ctx.piece_info_stats)[members[i]])<<endl;
	    		cout << "file size" << ": " << (((*piece_info_ctx.pieces_roots_val)[members[i]]))["size"]<<endl;
	    	}	 

	    	char* peer_addr = (char*) members[0].c_str();
	    	int file_size = (((*piece_info_ctx.pieces_roots_val)[members[0]]))["size"].asInt();
	    	int num_pieces = (((*piece_info_ctx.pieces_roots_val)[members[0]]))["total_pieces"].asInt();

	    	FILE *file_ptr;
	    	string full_path = string("./resources/")+string(file_name);
   			file_ptr = fopen((char*)full_path.c_str(), "w");
   			fclose(file_ptr);

   			//piece selection algorithm
   			//maps pieces to the peers so that the download is distributed amaong peers
   			//piece_selection(members, )
   			string file_sha1=file_info_root["file_sha1"].asString();
   			build_initial_pieces_info_file(string(file_name), string(group_id), num_pieces, file_size, file_sha1);

	    	for(int i=0; i<num_pieces; i++){

	    		//cout << (((*piece_info_ctx.pieces_roots_val)[members[0]]))["pieces"][to_string(i)] << endl;
	    		int piece_size = (((*piece_info_ctx.pieces_roots_val)[members[0]]))["pieces"][to_string(i)]["piece_size"].asInt();
	    		string piece_sha1 = (((*piece_info_ctx.pieces_roots_val)[members[0]]))["pieces"][to_string(i)]["piece_sha1"].asString();
	    		//cout << i << "th index - piece size: " << piece_size << endl;
	    		download_and_write_piece_data(peer_addr, file_name, i, piece_size, piece_sha1);
	    	}

	    	char* res = update_seeders(file_name, "localhost:7777");

	    }
	}

		

	//step2: connect to those peers and get the meta info about the available chunks with them
		//does the chunks availability with the peers needs to be at tracker or at the peers?
	//step3: piece selection algorithm to select the peers for the pieces
	//step4: send request to those peers to get the pieces
	
	//step5: update the tracker with the piece availaility which are freshely downloaded

	return response;
}

void* get_pieces_info_func(void* pieces_meta_holder){
	piece_info_struct piece_info_ctx = *((piece_info_struct*) pieces_meta_holder);
	string member_str = piece_info_ctx.member;
	char* filename = piece_info_ctx.file_name;
	char* member = (char*)member_str.c_str();
	//3. connects to peer and gets the pieces info
	cout << "filename: " << filename << endl;
	cout << "member: " << member << endl;
	Value pieces_info = get_pieces_info(clone(member), clone(filename));
	int* available_pieces = (int*) malloc(1*sizeof(int));
	*available_pieces = pieces_info["available_pieces"].asInt();
	cout << "available pieces: " << *available_pieces << endl;
	(*piece_info_ctx.piece_info_stats)[member_str]=available_pieces;
	(*piece_info_ctx.pieces_roots)[member_str]=&pieces_info;
	(*piece_info_ctx.pieces_roots_val)[member_str]=pieces_info;
}

void download_and_write_piece_data(char* peer_addr, char* file_name, int piece_idx, int piece_size, string sha1){
	//cout << "peer addr: " << peer_addr << endl;
	char* piece_data = 
		download_piece(clone(peer_addr), file_name,piece_idx,piece_size);
	
	

	string sha1_of_download_piece =  get_hash_digest(piece_data);

	/*cout << "-----------------------------" << endl;
	cout << sha1 << endl;
	cout << sha1_of_download_piece << endl;
	cout << "-----------------------------" << endl;*/
	//cout << piece_data << endl;
	string full_path = string("./resources/")+string(file_name);
	
	write_piece_data_to_file2(full_path, piece_idx, piece_size, piece_data);

	update_pieces_info(string(file_name), piece_idx, piece_size, sha1, string(peer_addr));
}

void update_pieces_info(string file_path, int piece_idx, int piece_size, string piece_sha1, string from_peer){
	string base_name = get_base_name(string(file_path));

	string full_path = string("./piece_info/")+string(base_name)+string(".pieces_info");
	string pieces_info_str = read_from_file(string("./pieces_info"), string(base_name+".pieces_info"));
	Value pieces_info_root;
	Reader reader;

	bool parsing_status = reader.parse( pieces_info_str, pieces_info_root );
	/*if(!parsing_status)
	    	return "error parsing pieces info content";*/

	int available_pieces = pieces_info_root["available_pieces"].asInt();
	available_pieces++;
	pieces_info_root["available_pieces"]=available_pieces;

	Value piece;
	piece["piece_no"] = piece_idx;
    piece["piece_size"] = piece_size;
    piece["piece_sha1"] = piece_sha1;
    piece["from_peer"] = from_peer;

	pieces_info_root["pieces"][to_string(piece_idx)] = piece;
	StyledWriter writer;
    pieces_info_str = writer.write( pieces_info_root );
	write_to_file(string("./pieces_info"), string(base_name+".pieces_info"), pieces_info_str);

	//1. if file not available create file
		//add a dummy json Value
		//save

	//2. if available, load the file
		//update the json as required.
		//save the file

	//3. communicate with tracker to update the seeders list of this file


}

void build_initial_pieces_info_file(string file_name, string group_id, int& total_pieces, int& file_size, string file_sha1){
	
	Value pieces_info; 
    pieces_info["name"] = file_name;
    pieces_info["group"] = group_id;
    pieces_info["file_sha1"] = file_sha1;
    pieces_info["size"] = file_size;
    pieces_info["total_pieces"] = total_pieces;
    pieces_info["available_pieces"] = 0;
    pieces_info["status"] = "PROGRESS";
    Value pieces;
    pieces_info["pieces"]=objectValue;

    StyledWriter writer;
    string pieces_info_str = writer.write( pieces_info );

    string base_name = get_base_name(string(file_name));
    write_to_file(string("./pieces_info"), string(base_name+".pieces_info"), pieces_info_str);

}
