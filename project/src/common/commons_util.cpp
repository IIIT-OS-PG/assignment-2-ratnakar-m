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

string get_base_name(string file_path){
    string base_filename = file_path.substr(file_path.find_last_of("/") + 1);
    return base_filename;
}

string strip_extn(string basename){
    string file_name_wo_extn = basename.substr(0,basename.find_last_of("."));
    return file_name_wo_extn;
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

int* open_file(string dir_path, string file_name){
    struct stat st = {0};
    if (stat(dir_path.c_str(), &st) == -1) {
        mkdir(dir_path.c_str(), 0777);
    }
    string file_path=dir_path+"/"+file_name;
    int *fd = (int *) malloc(sizeof(int));
    //*fd = open(file_path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
    *fd = open(file_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    return fd;
}

void write_to_file(string dir_path, string file_name, string content){
    struct stat st = {0};
    if (stat(dir_path.c_str(), &st) == -1) {
        mkdir(dir_path.c_str(), 0777);
    }
    string file_path=dir_path+"/"+file_name;
    ofstream outfile;
    outfile.open(file_path.c_str(), ios::out | ios::trunc);
    outfile << content << endl;
    outfile.close();
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
