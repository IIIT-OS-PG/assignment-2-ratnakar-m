#include <assign2.h>
#include <client.h>

char* download_impl(char* group_id, char* file_name, char* dest_path, char* username){
	char* response = (char *) malloc(BUFFER_SIZE * sizeof(char * )) ;

	//download is a multi step process
	//step1: get the peer addresses where the file is available
		//interface in tracker to get the trackers having the file

	//1. get file_info from tracker
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
	    	for(int i=0; i<members.size(); i++)
	    	{
	    		//2. get chunks info from seeders (peers)
	    		//separate threads?
	    		piece_info_ctx.member=members[i];
	    		pthread_create(&thread_handles[thread], NULL, get_pieces_info_func, (void*) &piece_info_ctx);
	    	}

	    	for(thread=0; thread < thread_count; thread++)
				pthread_join(thread_handles[thread], NULL);

			for(int i=0; i<members.size(); i++)
	    	{
	    		//available pieces in the members
	    		cout << "size: " << (*piece_info_ctx.piece_info_stats).size() << endl;
	    		cout << members[i] << ": " << *((*piece_info_ctx.piece_info_stats)[members[i]])<<endl;
	    	}	    	
	    }
	}

		

	//step2: connect to those peers and get the meta info about the available chunks with them
		//does the chunks availability with the peers needs to be at tracker or at the peers?
	//step3: piece selection algorithm to select the peers for the pieces
	//step4: send request to those peers to get the pieces
	//step5: update the tracker with the piece availaility which are freshely downloaded

	return response;
}

void* get_pieces_info_func(void* piece_info_holder){
	piece_info_struct piece_info_ctx = *((piece_info_struct*) piece_info_holder);
	unordered_map<string, int*> piece_info_stats = *(piece_info_ctx.piece_info_stats);
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
}