#include <iostream>

using namespace std;

#include <fstream>
#include <memory>
#include <sstream>
#include <vector>
#include <openssl/sha.h>

unsigned char* get_hash(char* str1);
void print_hash(unsigned char* hash);
string get_hash_digest(char* str1);

const int UNIT_SIZE = 10*1024; //512KB

unique_ptr<ofstream> create_chunks(vector<string>& chunk_file_names) {
    stringstream filename;
    filename << "chunk" << (chunk_file_names.size() + 1) << ".part";
    chunk_file_names.push_back(filename.str());
    return make_unique<ofstream>(filename.str(), ios::trunc);
}

string split(istream& inStream, int max_units, vector<string>& chunk_file_names) {

    unique_ptr<char[]> buffer(new char[UNIT_SIZE]);
    int num_units = 1;

    string result;

    do {
        unique_ptr<ostream> pOutStream = create_chunks(chunk_file_names);
        inStream.read(buffer.get(), UNIT_SIZE);
        //unsigned char* hash = get_hash(buffer.get());
        string digest = get_hash_digest(buffer.get());
        result = result + digest;
        cout << "digest: " << digest << endl;
        pOutStream->write(buffer.get(), inStream.gcount());
        ++num_units;
        if (num_units >= (max_units)) 
            num_units = 0;
        
    } while (!inStream.eof()) ;
    return result;


}

void merge(vector<string>& chunk_file_names, ostream& outStream) {
    for (int n = 0; n < chunk_file_names.size(); ++n) {
        ifstream ifs(chunk_file_names[n]);
        outStream << ifs.rdbuf();
    }
}

void createTestFile(const string& filename) {
    ofstream ofs(filename, ios::trunc);

    unique_ptr<char[]> buffer(new char[UNIT_SIZE]);

    int i = 0;

    for (int n = 0; n < 1024; ++n) {
        for (int m = 0; m < UNIT_SIZE; ++m) {
            buffer[m] = 'a' + (i++ % 26);
        }

        ofs.write(buffer.get(), UNIT_SIZE);
    }
}

int main()
{

    // Create test file

    //string filenameBefore = "assign.pdf";
    //createTestFile(filenameBefore);

    // Split

    ifstream ifs("assign.pdf");
    vector<string> chunk_file_names;

    string filehash = split(ifs, 1, chunk_file_names);
    cout << "filehash: " << endl << filehash << endl;
    // merge

    string filenameAfter = "new_assign.pdf";

    ofstream ofs(filenameAfter, ios::trunc);
    merge(chunk_file_names, ofs);

    return 0;
}

unsigned char* get_hash(char* str1){
    const unsigned char* str = (const unsigned char*)str1;
    unsigned char* hash = (unsigned char *) malloc(SHA_DIGEST_LENGTH);
    SHA1(str, sizeof(str) - 1, hash);
    return hash;
}

string get_hash_digest(char* str1){
  const unsigned char* str = (const unsigned char*)str1;
  unsigned char* hash = (unsigned char *) malloc(SHA_DIGEST_LENGTH);
  SHA1(str, sizeof(str) - 1, hash);
  //cout << "hash: " << hash << endl;
  //char mdString[SHA_DIGEST_LENGTH*2+1];
  char* mdString = (char *) malloc(SHA_DIGEST_LENGTH*2+1);
  for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)hash[i]);

  return mdString;
}

void print_hash(unsigned char* hash){
  //cout << "hash: " << hash << endl;
  char mdString[SHA_DIGEST_LENGTH*2+1];
  for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)hash[i]);

  printf("SHA1 digest: %s\n", mdString);
}