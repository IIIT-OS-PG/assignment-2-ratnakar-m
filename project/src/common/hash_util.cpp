#include<assign2.h>

//returns file sha1 and size
//populates chunk info in the input structure: list of sha1s and the data of each piece
pair<string,int> split_chunks(string file_path, vector<chunk_info>& chunks) {

    ifstream inStream(file_path);
    if(!inStream)
      return make_pair("",-1);
    unique_ptr<char[]> buffer(new char[CHUNK_SIZE]);

    string result;
    int total_size=0;

    int i=1;
    do {
        chunk_info chunk;
        inStream.read(buffer.get(), CHUNK_SIZE);
        //unsigned char* hash = get_hash(buffer.get());
        string digest = get_hash_digest(buffer.get());

        result = result + digest;
        //cout << "digest: " << digest << endl;
        int *chunk_size = (int *) malloc(sizeof(int));
        *chunk_size=inStream.gcount();
        total_size=total_size + (*chunk_size);
        chunk.sha1=digest;
        chunk.size=chunk_size;
        chunk.data=buffer.get();
        chunks.push_back(chunk);
        
        
    } while (!inStream.eof()) ;
    return make_pair(result,total_size);
}

string get_hash_digest(char* str1){
  const unsigned char* str = (const unsigned char*)str1;
  unsigned char* hash = (unsigned char *) malloc(SHA_DIGEST_LENGTH);
  SHA1(str, sizeof(str) - 1, hash);
  char* mdString = (char *) malloc(SHA_DIGEST_LENGTH*2+1);
  for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)hash[i]);

  return mdString;
}