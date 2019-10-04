#include<assign2.h>

string get_base_name(string file_path){
    string base_filename = file_path.substr(file_path.find_last_of("/") + 1);
    return base_filename;
}

//return list of sha1s and the data of each piece
string split_chunks(string file_path, vector<chunk_info>& chunks) {

    ifstream inStream(file_path);
    unique_ptr<char[]> buffer(new char[CHUNK_SIZE]);

    string result;
    int i=1;
    do {
        chunk_info chunk;
        inStream.read(buffer.get(), CHUNK_SIZE);
        //unsigned char* hash = get_hash(buffer.get());
        string digest = get_hash_digest(buffer.get());

        result = result + digest;
        cout << "digest: " << digest << endl;
        int *size = (int *) malloc(sizeof(int));
        *size=inStream.gcount();
        chunk.sha1=digest;
        chunk.size = size;
        chunk.data=buffer.get();
        chunks.push_back(chunk);
        
        
    } while (!inStream.eof()) ;
    return result;
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