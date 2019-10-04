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

pair<int,char*> get_msg(string s){
    char* msg = clone((char*)s.c_str());
    return make_pair(s.size(),msg);
}

int* open_log_file(int port){
    struct stat st = {0};
    if (stat("logs", &st) == -1) {
        mkdir("logs", 0777);
    }
    string log_file_path="logs/peer-"+to_string(port)+"_"+get_time_compact()+".log";
    int *logfd = (int *) malloc(sizeof(int));
    *logfd = open(log_file_path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
    return logfd;
}
int write_msg(int fd, string msg_str){
    pair<int,char*> msg = get_msg(msg_str);
    int written_size = write (fd, msg.second, (ssize_t) msg.first);
    return written_size;
}

int write_msg_line(int fd, string msg_str){
    msg_str=msg_str+"\n";
    return write_msg(fd,msg_str);
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
