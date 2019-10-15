#include <openssl/sha.h>
#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <iostream>  
#include <fstream>  

using namespace std;

unsigned char* get_hash(char* str);

int main()
{  
  cout << "SHA_DIGEST_LENGTH: " << SHA_DIGEST_LENGTH << endl;
  char str[] = "Hello Ratnakar";
  unsigned char* hash = get_hash(str);

  cout << "hash val = "<<hash<<endl;
  char mdString[SHA_DIGEST_LENGTH*2+1];
  for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
	    sprintf(&mdString[i*2], "%02x", (unsigned int)hash[i]);

  printf("SHA1 digest: %s\n", mdString);

  
  return 0;
}

unsigned char* get_hash(char* str1){
    const unsigned char* str = (const unsigned char*)str1;
    unsigned char* hash = (unsigned char *) malloc(SHA_DIGEST_LENGTH);

    SHA1(str, sizeof(str) - 1, hash);

    cout << "hash val = "<<hash<<endl;
    char mdString[SHA_DIGEST_LENGTH*2+1];
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)hash[i]);

    printf("SHA1 digest: %s\n", mdString);
    return hash;
}

char* readFileBytes(const char *name)  
{  
    ifstream fl(name);  
    fl.seekg( 0, ios::end );  
    size_t len = fl.tellg();  
    char *ret = new char[len];  
    fl.seekg(0, ios::beg);   
    fl.read(ret, len);  
    fl.close();  
    return ret;  
}  