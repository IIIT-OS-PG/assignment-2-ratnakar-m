#include <assign2.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

unsigned char* get_hash(char* str1){
    const unsigned char* str = (const unsigned char*) str1;
    //unsigned char hash[SHA_DIGEST_LENGTH]; // == 20
    unsigned char* hash = (unsigned char *) malloc(SHA_DIGEST_LENGTH);

    SHA1(str, sizeof(str) - 1, hash);

    cout << "hash val = "<<hash<<endl;
    char mdString[SHA_DIGEST_LENGTH*2+1];
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)hash[i]);

    printf("SHA1 digest: %s\n", mdString);
    return hash;
}

char* clone(char* orig){
    char* cl = (char *) malloc(BUFFER_SIZE);
    int g = 0;
    while(orig[g] != '\0')
    {
        cl[g] = orig[g];
        g++;
    }
    cl[g]='\0';

    return cl;
}