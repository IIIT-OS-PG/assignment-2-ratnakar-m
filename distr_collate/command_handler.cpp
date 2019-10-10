#include <util.h>

char* get_file_info(char* filename){
    vector<chunk_info> chunks;
    pair<string,int> file_info = split_chunks(filename, chunks);
    cout << chunks.size() << endl;
    Value response = build_metadata_for_self(filename, file_info, chunks);
    //cout << response << endl;
    StyledWriter writer;
    string meta_str = writer.write( response );

    //cout << buffer << endl;
    //pair<int, char*> meta_msg = get_msg(meta_str);
    //cout << (char*)meta_str.c_str() << endl;
    //return clone2((char*)meta_str.c_str(),meta_str.length());

    //cout << meta_msg.second << endl;
    //return meta_msg.second;
    return clone3(meta_str);
}

Value build_metadata_for_self(string file_name, pair<string,int> file_info, vector<chunk_info> chunks){
	Value meta; 
    meta["name"] = file_name;
    meta["file_sha1"] = file_info.first;
    meta["size"] = file_info.second;
    meta["total_pieces"] = (int)chunks.size();
    meta["available_pieces"] = (int)chunks.size();
    meta["status"] = "COMPLETED";
    Value pieces;
    
    
    for(int i=0; i<chunks.size(); i++){
    	Value piece;
	    piece["piece_no"] = i;
	    piece["piece_size"] = *chunks[i].size;
	    piece["piece_sha1"] = chunks[i].sha1;
	    //piece["piece_data"] = chunks[i].data;
	    pieces[to_string(i)] = piece;

    }
    meta["pieces"] = pieces;
    return meta;
}

char* download_piece(char* piece_idx_str, char* piece_size_str){
  int srcfd = open ("short.txt", O_RDONLY);
  if (srcfd == -1) {
     perror ("open");
     return NULL;
  }
  char buffer[BUFFER_SIZE];   
  int read_size;  
  int offset = atoi(piece_idx_str)*BUFFER_SIZE;
  int size = atoi(piece_size_str);
  cout << "offset: " << offset << ", " << "size: " << size << endl;
  if(lseek(srcfd,offset,SEEK_SET) < 0) 
  {
    error("error on lseek");
    return NULL;
  }

  read_size = read (srcfd, &buffer, BUFFER_SIZE);

  //close(srcfd);
  cout << buffer << endl;
  return clone(buffer);
}

pair<int,char*> get_msg(string s){
    char* msg = clone((char*)s.c_str());
    return make_pair(s.size(),msg);
}