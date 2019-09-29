#include <assign2.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

string get_time(){
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    string ts = 
               to_string(now->tm_mday) + "-"
               + to_string((now->tm_mon + 1))+ "-" 
               + to_string((now->tm_year + 1900)) + " " 
               + to_string(now->tm_hour) + ":"
               + to_string(now->tm_min) + ":"
               + to_string(now->tm_sec) + " ";

    return ts; 
}

string get_time_compact(){
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    string ts = to_string((now->tm_mon + 1))+ "-"
               + to_string(now->tm_mday) + "-"
               + to_string((now->tm_year + 1900)) + "-" 
               + to_string(now->tm_hour) + "-"
               + to_string(now->tm_min);
    return ts; 
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