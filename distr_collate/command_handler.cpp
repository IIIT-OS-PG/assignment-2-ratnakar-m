#include <util.h>

char* get_file_info(char* filename){

	int srcfd = open ("moby_dick.txt", O_RDONLY);
	if (srcfd == -1) {
		perror ("open");
		return NULL;
	}
	char buffer[BUFFER_SIZE];	
	int read_size;	
	while((read_size = read (srcfd, &buffer, BUFFER_SIZE)) > 0){
        
	}

	close(srcfd);
    vector<chunk_info> chunks;
    pair<string,int> file_info = split_chunks(filename, chunks);
    char* response = build_metadata_for_self(filename, file_info, chunks);

   //return clone("this is file info");
    return clone(response);
}

char* build_metadata_for_self(string file_name, pair<string,int> file_info, vector<chunk_info> chunks){
	Value meta; 
    meta["name"] = file_name;
    meta["file_sha1"] = file_info.first;
    meta["size"] = file_info.second;
    meta["total_pieces"] = (int)chunks.size();
    meta["available_pieces"] = (int)chunks.size();
    meta["status"] = "COMPLETED";
    Value pieces;
    //meta["pieces"] = Value(arrayValue); //array of pieces
    //changing from array of pieces to dictionary of pieces with index as piece idx
    
    for(int i=0; i<chunks.size(); i++){
    	Value piece;
	    piece["piece_no"] = i;
	    piece["piece_size"] = *chunks[i].size;
	    piece["piece_sha1"] = chunks[i].sha1;
	    piece["piece_data"] = chunks[i].data;
	    pieces[to_string(i)] = piece;

    }
    meta["pieces"] = pieces;
    StyledWriter writer;
    string meta_str = writer.write( meta );
    //cout << root << endl; //printing using the root itself
    //cout << meta_str << endl; //printing using the string of root
    pair<int, char*> meta_msg = get_msg(meta_str);
    return meta_msg.second;
}

char* download_piece(char* piece_idx_str, char* piece_size_str){
  return clone("this is piece data");
}

pair<int,char*> get_msg(string s){
    char* msg = clone((char*)s.c_str());
    return make_pair(s.size(),msg);
}