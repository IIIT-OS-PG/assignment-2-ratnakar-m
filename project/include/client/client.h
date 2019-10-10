#ifndef CLIENT_H
#define CLIENT_H

struct peer_ctx 
{
    char* host;
    int* portno;
    int* sockfd;
};

typedef struct
{
	char* host;
	int* port;

} tracker;

typedef struct
{
	char* host;
	int* port;
	int *sockfd;

} connected_tracker;

typedef struct
{
	string member;
	unordered_map<string, int*>* piece_info_stats;
	unordered_map<string, Value*>* pieces_roots;
	unordered_map<string, Value>* pieces_roots_val;
	char* file_name;
} piece_info_struct;

extern bool INFER_IP;

vector<tracker> extract_tracker_info(char* tracker_info);
void print_tracker_info(vector<tracker> trackers);
connected_tracker connect_tracker(vector<tracker> trackers);
void tracker_status_check();
extern vector<tracker> trackers;

extern struct peer_ctx peer_context; //"peer_context" stores peer_ctx of self
peer_ctx connect_peer(char* host, int* port); //connect to other peers and get their context
char* send_cmd_to_peer(char* peer_addr, char* command);
Value get_pieces_info(char* peer_addr, char* file_name);
char* download_piece(char* peer_addr, char* file_name, int piece_idx, int piece_size);

void* get_pieces_info_func(void* piece_info_holder);
void download_and_write_piece_data(char* peer_addr, char* file_name, int piece_idx, int piece_size, string sha1);


char* serve_command(char* command_line, int* logfd);
bool piece_info_exists(char* full_path);

//extern connected_tracker tracker_context;
extern vector<tracker> trackers;
char* build_metadata_for_tracker(string file_name, string group_id, pair<string,int> file_info, vector<chunk_info> chunks);
char* build_metadata_for_self(string file_name, string group_id, pair<string,int> file_info, vector<chunk_info> chunks);
void add_piece(Value& document, int idx, int size, string sha1, string from_peer);
char* download_impl(char* group_id, char* file_name, char* dest_path, char* username);

void manage_prompt();
void reset_prompt();
char * manage_menu();
void help();
void *listener_handler(void * peer_ctx_struct_ptr);
void *handle_request(void * ctx_st);
char* send_cmd_to_tracker(char* command);
pair<string, int*> get_hostname_port();


extern char* current_user;

#define INVALID_ARGS "invalid args. type 'help' for more details."



#endif //CLIENT_H