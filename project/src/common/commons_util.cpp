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

char* read_from_file(string dir_path, string file_name){
    cout << "reading from file: " << file_name<< endl;
    struct stat st = {0};
    if (stat(dir_path.c_str(), &st) == -1) {
        mkdir(dir_path.c_str(), 0777);
    }
    string file_path=dir_path+"/"+file_name;
    ifstream f(file_path);
    stringstream buffer;
    buffer << f.rdbuf();
    const string& tmp = buffer.str();   
    char* cstr = (char*)tmp.c_str();
    cout << cstr << endl;
    return clone(cstr);
}

char* read_piece_data_from_file(string file_path, int piece_idx, int piece_size){
    ifstream fl(file_path, ios::binary); 
    int seek_pos =  piece_idx*CHUNK_SIZE;
    char* piece_data = new char[piece_size];  
    fl.seekg(seek_pos,ios::beg);   
    fl.read(piece_data, piece_size); 
    cout << "PIECE IDX " << piece_idx << endl;
    cout << "PIECE SIZE " << piece_size << endl;
    cout << "SEEK POS " << seek_pos << endl;
    cout << "READ SIZE " << fl.gcount() << endl; 
    fl.close();  
    return piece_data;  
} 

void write_piece_data_to_file(string file_path, int piece_idx, int piece_size, char* piece_data){
    ofstream fl; 
    //fl.open(file_path, ios::out|ios::binary);
    fl.open(file_path, ios::binary);
    int seek_pos =  piece_idx*CHUNK_SIZE;
    fl.seekp(seek_pos,ios::beg);   
    cout << "----------------------------------------" << endl;
    cout << "idx :" << piece_idx << ", seek_pos: " << seek_pos << endl;
    /*char* mybuff = (char *)malloc(piece_size);
    bzero(mybuff,piece_size);
    memcpy(mybuff,piece_data, piece_size);
    cout << mybuff << endl;
    fl.write(mybuff, piece_size); 
    free(mybuff); */
    fl.write(piece_data, piece_size);
    fl.flush(); 

    cout << "PIECE SIZE: " << piece_size << " Filepath: " << file_path<< endl;
    cout << "piece_idx*CHUNK_SIZE: " << piece_idx*CHUNK_SIZE << endl;

    fl.close();   
} 

void write_piece_data_to_file2(string file_path, int piece_idx, int piece_size, char* piece_data){
    /*cout << "=====================================" << endl;
    cout << "SIZE: " << strlen(piece_data) << endl;
    cout << "IDX: " << piece_idx << endl;

    cout << "DOWNLOAD 2: " << endl;*/
    FILE *file_ptr;
    file_ptr = fopen(file_path.c_str(), "r+b"); 
    int offset =  piece_idx*CHUNK_SIZE;
    fseek(file_ptr, offset, SEEK_SET);

    char* mybuff = (char *)malloc(piece_size);
    bzero(mybuff,piece_size);
    memcpy(mybuff,piece_data, piece_size);

    cout << "PIECE SIZE: " << piece_size << " Filepath: " << file_path<< endl;
    int written_c = fwrite(mybuff, 1, piece_size, file_ptr);;
    //int written_c = fwrite(piece_data, 1, piece_size, file_ptr);
    cout << "WRITTEN SIZE: " << written_c << endl; 
    fflush(file_ptr);
    fclose(file_ptr);
} 

void write_piece_data_to_file3(string file_path, int piece_idx, int piece_size, char* piece_data){

} 


pair<int,char*> get_msg(string s){
    char* msg = clone((char*)s.c_str());
    return make_pair(s.size(),msg);
}

int write_msg(int* fd, string msg_str){
    pair<int,char*> msg = get_msg(msg_str);
    int written_size = write (*fd, msg.second, (ssize_t) msg.first);
    return written_size;
}

int write_msg_line(int* fd, string msg_str){
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

char* clone2(char* orig, int size){ //make sure size <=BUFFER_SIZE
    char* cl = (char *) malloc(BUFFER_SIZE*sizeof(char));
    for(int g=0; g<size; g++){
        cl[g] = orig[g];
        g++;
    }

    return cl;
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

bool does_file_exist(char* full_path){
    struct stat st = {0};
    if (stat(full_path, &st) == -1) {
        return false;
    }
    return true;
}
