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

vector<tracker> extract_tracker_info(char* tracker_info);
void print_tracker_info(vector<tracker> trackers);
connected_tracker connect_tracker(vector<tracker> trackers);
extern vector<tracker> trackers;
extern struct peer_ctx peer_context;

void manage_prompt(vector<tracker> trackers);
void reset_prompt();
char * manage_menu();
void help();
void *listener_handler(void * peer_ctx_struct_ptr);
void *handle_request(void * ctx_st);

extern char* current_user;



#endif //CLIENT_H