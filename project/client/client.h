#ifndef CLIENT_H
#define CLIENT_H

struct peer_ctx 
{
    char* host;
    int portno;
    int sockfd;
};

void manage_prompt();
void reset_prompt();
char * manage_menu();
void help();
void *listener_handler(void * peer_ctx_struct_ptr);
void *handle_request(void * ctx_st);

extern char* current_user;



#endif //CLIENT_H