#include <assign2.h>
#include <client.h>

void* get_pieces_info_func2(void* member_ptr);

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
	    int file_size = file_info_root["size"].asInt();
	    string file_sha1 = file_info_root["file_sha1"].asString();

	    if(file_info_root.isMember("seeders")){
	    	Value seeders = file_info_root["seeders"];
	    	vector<string> members = seeders.getMemberNames();
	    	cout << "Seeders Info: " << endl;
	    	int thread_count = members.size();
	    	int curr_thread = 0;
	    	pthread_t* thread_handles = (pthread_t*) malloc(thread_count*sizeof(pthread_t));

	    	
	    	//piece_info_struct *piece_info_ctx_ptr = (piece_info_struct*)malloc(sizeof(piece_info_struct)); 
	    	//piece_info_struct piece_info_ctx = *piece_info_ctx_ptr;
	    	piece_info_struct piece_info_ctx;
	    	piece_info_ctx.file_name=file_name;
	    	unordered_map<string, int*> piece_info_stats;
	    	piece_info_ctx.piece_info_stats = &piece_info_stats;

	    	unordered_map<string, Value> pieces_roots;
	    	//piece_info_ctx.pieces_roots = &pieces_roots;

	    	unordered_map<string, Value> pieces_roots_val;
	    	unordered_map<string, Value> seeders_pieces_map;
	    	piece_info_ctx.pieces_roots_val = &pieces_roots_val;
	    	cout << "MEMBERS SIZE: " << members.size() << endl;
	    	//vector<pair<char*,piece_info_struct*>> thread_inputs;
	    	vector<pair<char*,char*>> thread_inputs;
	    	for(string member : members){
	    		string data = member+string("$")+string(file_name);
	    		char* pi = (char *)malloc(BUFFER_SIZE);
    			bzero(pi,BUFFER_SIZE);
	    		pair<char*,char*> p = make_pair(clone((char*)data.c_str()), pi);
	    		thread_inputs.push_back(p);
	    	}
	    	for(int i=0; i<members.size(); i++)
	    	{
	    		//2. get chunks info from seeders (peers)
	    		//separate threads?
	    		piece_info_ctx.member=string(members[i]);
	    		cout << "MEMBER: " << members[i] << endl;
	    		//pthread_create(&thread_handles[curr_thread], NULL, get_pieces_info_func2, (void*) (members[i].c_str()));
	    		pthread_create(&thread_handles[curr_thread], NULL, get_pieces_info_func2, (void*) (&thread_inputs[i]));

	    		//info_threads.ad 
	    		curr_thread++;
	    	}

	    	//char** thread_returns = (char*) malloc(thread_count*sizeof(char*));
	    	cout << "returned from threads" << endl;
	    	//unordered_map<string, Value>* thread_returns = (int*) malloc(thread_count*sizeof(int));

	    	for(curr_thread=0; curr_thread < thread_count; curr_thread++)
			{
				pthread_join(thread_handles[curr_thread], NULL);
				//cout << "thread_inputs[curr_thread].first: " << thread_inputs[curr_thread].first << endl;
				//cout << "thread_inputs[curr_thread].second: " << thread_inputs[curr_thread].second << endl;
				char* seeder = thread_inputs[curr_thread].first;
				char* piece_info_str = thread_inputs[curr_thread].second;

				Value piece_root = parseJson(piece_info_str);
				seeders_pieces_map[string(seeder)]=piece_root;
				//cout << thread_returns[curr_thread] << endl;
			}
			FILE *file_ptr;
	    	string full_path = string("./resources/")+string(file_name);
   			file_ptr = fopen((char*)full_path.c_str(), "w");
   			fclose(file_ptr);
   			build_initial_pieces_info_file(string(file_name), string(group_id), total_pieces, file_size, file_sha1);


			unordered_map<string, string>  piece_seeder_select_map = piece_selection(seeders_pieces_map);
			for ( auto it = piece_seeder_select_map.begin(); it != piece_seeder_select_map.end(); ++it )
			{
				string piece_idx = it->first;
				string peer_addr = it->second;
				Value piece_root = seeders_pieces_map[peer_addr];
				int piece_size = piece_root["pieces"][piece_idx]["piece_size"].asInt();
				string piece_sha1 = piece_root["pieces"][piece_idx]["piece_sha1"].asString();

				cout << piece_idx <<", " << piece_size << ", " << piece_sha1 << endl;
				download_and_write_piece_data((char*)peer_addr.c_str(), file_name, atoi((char*)piece_idx.c_str()), piece_size, piece_sha1);
			}
			pair<string, int*> host_port=get_hostname_port();
	        string my_addr= host_port.first+string(":")+to_string(*host_port.second);

			char* res = update_seeders(file_name, (char*)my_addr.c_str());
	    }
	}

		

	//step2: connect to those peers and get the meta info about the available chunks with them
		//does the chunks availability with the peers needs to be at tracker or at the peers?
	//step3: piece selection algorithm to select the peers for the pieces
	//step4: send request to those peers to get the pieces
	
	//step5: update the tracker with the piece availaility which are freshely downloaded

	return response;
}

unordered_map<string, string> piece_selection(unordered_map<string, Value> seeders_pieces_map){
	unordered_map<string, vector<int>> seeders_avl_pieces_map;
	for ( auto it = seeders_pieces_map.begin(); it != seeders_pieces_map.end(); ++it )
	{
		string seeder = it->first;
		Value pieces_root  = it->second;
		cout << "FROM ADDRESS: " << pieces_root["address"] << endl;

		Value piece_info = pieces_root["pieces"];
		vector<string> pieces_idx = piece_info.getMemberNames();
		vector<int> pieces_idx_int;
		for(string piece_str : pieces_idx){
			pieces_idx_int.push_back(atoi(piece_str.c_str()));
		}
		seeders_avl_pieces_map[seeder]=pieces_idx_int;
	}

	unordered_set <int> pieces_set ; 
	unordered_map<int,int> count_map; //piece_id & count mapusesfule to find rarest pieces
	unordered_map<int,set<string>> piece_avl_seeders_map;//piece_id and available seeders

	for ( auto it = seeders_avl_pieces_map.begin(); it != seeders_avl_pieces_map.end(); ++it )
	{
		string seeder = it->first;
		vector<int> available_pieces = it->second;

		for (int i=0; i<available_pieces.size(); i++) 
        {
        	pieces_set.insert(available_pieces[i]); 
        	if (count_map.find(available_pieces[i]) == count_map.end()){ //if not found; set count to 1
        		count_map[available_pieces[i]]=1;
        	}
        	else{ //if found increment count
        		count_map[available_pieces[i]]=count_map[available_pieces[i]]+1;
        	}
        	if (piece_avl_seeders_map.find(available_pieces[i]) == piece_avl_seeders_map.end()){ //if not found; set add seeder
        		set<string> sdrs_set;
        		sdrs_set.insert(seeder);
        		piece_avl_seeders_map[available_pieces[i]]=sdrs_set;
        	}
        	else{ //if found appened to seeders list
        		piece_avl_seeders_map[available_pieces[i]].insert(seeder);
        	}
        }
		
		/*cout << "*************printing available pieces in seeder: " << seeder << "****************" << endl;
		for (vector<int>::iterator it = available_pieces.begin() ; it != available_pieces.end(); ++it)
				cout << *it << " ";
		cout << endl;*/
	}
	cout << "SET SIZE: " << pieces_set.size() << endl; 

	// construct pairs with the rare piece first
	// <piece_id,count>
	set<pair<int,int>, mycomp_struct> rare_first_set(count_map.begin(), count_map.end());
	cout << "RAREST ORDER SET SIZE: " << rare_first_set.size() << endl; 

	//choose the pieces by rarest first
	//choose the seeders with less load
	//min heap of seeders 	: seeders with less load so far will come on top
	//heap will have seeders and the count of pieces allocated so far
	//seeder with less allocation of pieces will come on top

	priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>> > min_load_heap;
	for ( auto it = seeders_avl_pieces_map.begin(); it != seeders_avl_pieces_map.end(); ++it )
	{
		string seeder = it->first;
		vector<int> available_pieces = it->second;
		pair<int, string> p = make_pair(0,seeder);
		min_load_heap.push(p);
	}

	cout << "SIZE of min heap: " << min_load_heap.size() << endl; 
	set<pair<int,int>, mycomp_struct> :: iterator itr;
	unordered_map<string, string> psm;
	for (itr = rare_first_set.begin(); itr != rare_first_set.end(); ++itr) 
    { 
    	pair<int,int> item = *itr;
    	int next_rare_piece = item.first;

    	cout << item.first << " -> " << item.second << endl;
    	pair<int, string> p = min_load_heap.top();
    	min_load_heap.pop();
    	string probable_seeder_for_this_piece = p.second;
    	vector<int> avl_pieces = seeders_avl_pieces_map[probable_seeder_for_this_piece];
    	if (count(avl_pieces.begin(), avl_pieces.end(), next_rare_piece))
    	{
    		cout << "found " << next_rare_piece << endl;
    		psm[to_string(next_rare_piece)]=probable_seeder_for_this_piece;
    		p.first = p.first + 1;
    		min_load_heap.push(p); //push back after incrementing
    	}
    }

    cout << "ASSIGNED SEEDERS" << endl;
	for ( auto it = psm.begin(); it != psm.end(); ++it )
	{
		string piece_idx = it->first;
		string seeder = it->second;
		cout << "piece idx: " << piece_idx << " -> " << "seeder: " << seeder << endl;
	}
	return psm;
}

void* get_pieces_info_func2(void* p_ptr){
	pair<char*,char*> p = *(pair<char*,char*>*)p_ptr;
	char* peer_addr = strtok(p.first,"$");
	char* file_name = strtok(NULL,"$");
	char* pieces_info_str = get_pieces_info_str(clone(peer_addr), clone(file_name));
    //cout << "RECEIVED len: " << strlen(pieces_info_str) << endl; 
	//cout << pieces_info_str << endl;;
    memcpy(p.second,pieces_info_str,strlen(pieces_info_str));
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
	cout << "available pieces: (" <<member << ") " <<*available_pieces << endl;
	(*piece_info_ctx.piece_info_stats)[member_str]=available_pieces;
	(*piece_info_ctx.pieces_roots)[member_str]=&pieces_info;
	(*piece_info_ctx.pieces_roots_val)[member_str]=pieces_info;

	//return (void*) pieces_info;
}

void download_and_write_piece_data(char* peer_addr, char* file_name, int piece_idx, int piece_size, string sha1){
	char* piece_data = download_piece(clone(peer_addr), file_name,piece_idx,piece_size);
	//cout << "PIECE DATA RECEIVED: " << piece_data << endl;
	string sha1_of_download_piece =  get_hash_digest(piece_data);
	string full_path = string("./resources/")+string(file_name);
	string piece_file_name = strip_extn(file_name);
	write_piece_data_to_file2(full_path, piece_idx, piece_size, piece_data);
	update_pieces_info(string(piece_file_name), piece_idx, piece_size, sha1, string(peer_addr));
}

void update_pieces_info(string file_path, int piece_idx, int piece_size, string piece_sha1, string from_peer){
	string base_name = get_base_name(string(file_path));
	string piece_file_name = strip_extn(base_name);

	string full_path = string("./piece_info/")+string(piece_file_name)+string(".pieces_info");
	string pieces_info_str = read_from_file(string("./pieces_info"), string(piece_file_name)+string(".pieces_info"));
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
}

void build_initial_pieces_info_file(string file_name, string group_id, int& total_pieces, int& file_size, string file_sha1){
	
	Value pieces_info; 
    pieces_info["name"] = file_name;
    pieces_info["group"] = group_id;
    pieces_info["file_sha1"] = file_sha1;
    pieces_info["size"] = file_size;
    pieces_info["total_pieces"] = total_pieces;
    pieces_info["available_pieces"] = 0;
    pair<string, int*> host_port=get_hostname_port();
    pieces_info["address"]= host_port.first+string(":")+to_string(*host_port.second);
    pieces_info["status"] = "PROGRESS";
    Value pieces;
    pieces_info["pieces"]=objectValue;

    StyledWriter writer;
    string pieces_info_str = writer.write( pieces_info );

    string base_name = get_base_name(string(file_name));
    string piece_file_name = strip_extn(base_name);
    write_to_file(string("./pieces_info"), string(piece_file_name+".pieces_info"), pieces_info_str);

}
