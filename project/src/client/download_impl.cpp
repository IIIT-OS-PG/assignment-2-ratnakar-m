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

	    if(file_info_root.isMember("seeders")){
	    	Value seeders = file_info_root["seeders"];
	    	vector<string> members = seeders.getMemberNames();
	    	cout << "Seeders Info: " << endl;
	    	for(int i=0; i<members.size(); i++)
	    	{
	    		cout << members[i] << endl;
	    		//2. get chunks info from seeders (peers)
	    		//separate threads?
	    		Value pieces_info = get_pieces_info((char*)members[i].c_str());
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