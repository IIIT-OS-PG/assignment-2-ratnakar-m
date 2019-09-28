#include <openssl/sha.h>
#include <iostream>
#include <stdio.h>
#include <malloc.h>

using namespace std;

unsigned char* get_hash(char* str);

int main()
{  
  char str[] = "Original String";
  unsigned char* hash = get_hash(str);
  /*const unsigned char str[] = "Original String";
  unsigned char hash[SHA_DIGEST_LENGTH]; // == 20

  SHA1(str, sizeof(str) - 1, hash);*/

  cout << "hash val = "<<hash<<endl;
  char mdString[SHA_DIGEST_LENGTH*2+1];
  for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
	    sprintf(&mdString[i*2], "%02x", (unsigned int)hash[i]);

  printf("SHA1 digest: %s\n", mdString);

  /*const unsigned char str2[] = "Original Strinl";
  unsigned char hash2[SHA_DIGEST_LENGTH]; // == 20

  SHA1(str2, sizeof(str2) - 1, hash2);

  cout << "hash val = "<<hash2<<endl;
  char mdString2[SHA_DIGEST_LENGTH*2+1];
  for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
	    sprintf(&mdString2[i*2], "%02x", (unsigned int)hash2[i]);

  printf("SHA1 digest: %s\n", mdString2);*/

  // do some stuff with the hash

  return 0;
}

unsigned char* get_hash(char* str1){
    //const unsigned char str[] = "Original String";
    //unsigned char hash[SHA_DIGEST_LENGTH]; // == 20
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