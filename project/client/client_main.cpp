#include <assign2.h>

void manage_prompt();
void reset_prompt();
char * manage_menu();
void help();
void *listener_handler(void * peer_ctx_struct_ptr);
void *handle_request(void * ctx_st);


char* current_user=NULL;
struct peer_ctx 
{
    char* host;
    int portno;
    int sockfd;
};

int main(int argc, char **argv) {
	if (argc < 3) {
       cout << "Usage: client <ip> <port> <tracker_info_file>" << endl;
       exit(1);
    }
    char* host = argv[1];
	int *sockfd = (int *) malloc(sizeof(int));
	int *portno = (int *) malloc(sizeof(int));
	*portno = atoi(argv[2]);

	*sockfd = start_service(host,*portno);
	int *sockfd_ptr = (int *) malloc(sizeof(int));
	struct peer_ctx ctx;
	ctx.host=clone(host);
	ctx.portno=*portno;
	ctx.sockfd=*sockfd;

	pthread_t listener_thread;
    int ret =  pthread_create(&listener_thread, NULL, &listener_handler, (void*)&ctx);
    if(ret != 0) {
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);
    }
	manage_prompt();
}

void *listener_handler(void * peer_ctx_struct_ptr)
{
    struct peer_ctx ctx = *((peer_ctx*) peer_ctx_struct_ptr);
    int port = ctx.portno;
    int sockfd = ctx.sockfd;
    ofstream log_file;
    string log_file_name="peer-"+to_string(port)+"_"+get_time_compact()+".log";
	log_file.open("logs/"+log_file_name, ios::out | ios::app);
	time_t my_time = time(NULL); 
	log_file << get_time() << "Peer Started..." << endl;
	log_file << get_time() << "listening on port "<<port<<endl;
    
    while(true){

       struct sockaddr_in cli_addr;
       socklen_t clilen;
       int ret;

       clilen = sizeof(cli_addr);
       int *newsockfd = (int *) malloc(sizeof(int));
       *newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
       if (*newsockfd < 0) 
       		log_file << "ERROR on accept" << endl;
       struct request_ctx ctx;
       ctx.newsockfd=*newsockfd;
       ctx.cli_addr=cli_addr;
       ctx.clilen=clilen;
       log_file << "server: got connection from "<<
       inet_ntoa(cli_addr.sin_addr) << " port " <<
       ntohs(cli_addr.sin_port) << endl;

       pthread_t my_thread;
       ret =  pthread_create(&my_thread, NULL, &handle_request, (void*)&ctx);
       if(ret != 0) {
            log_file << "Error: pthread_create() failed" << endl;
            exit(EXIT_FAILURE);
        }

     }

    log_file.close();
    close(sockfd);
    pthread_exit(NULL);
}

void *handle_request(void * ctx_st)
{
    request_ctx ctx = *((request_ctx*) ctx_st);
    int newsockfd = ctx.newsockfd;
    int n;

    //

    close(newsockfd);
    pthread_exit(NULL);
}

void manage_prompt() {
	reset_prompt();
	bzero((char *) &current_user, sizeof(char));

	while(strcmp(manage_menu(),"exit") != 0) {
		reset_prompt();
	}
}

void reset_prompt() {
	if(current_user==NULL)
		cout << "peer>";
	else
		cout << "peer~"+string(current_user)+">";
	fflush(stdin);
}

char * manage_menu() {
	char input[500];
	fgets(input, 500, stdin);
	char * command;
	char tempInput[500];
	strcpy(tempInput, input);
	command = strtok(input, "\n");
	command = strtok(input, " ");
	if(strcmp(command, "create_user")==0) {
		char* username = strtok(NULL, " ");
		char* passwd = strtok(NULL, " ");
		if(username !=NULL && passwd !=NULL)
			create_user(username, passwd);
		else
			cout << "invalid args. type 'help' for more details." << endl;
	} 
	else if(strcmp(command, "login")==0) {
		char* username = strtok(NULL, " ");
		char* passwd = strtok(NULL, " ");
		if(username !=NULL && passwd !=NULL)
		{
			bool login_success = login(username, passwd);
			if(login_success)
			{
				cout << "You are now logged in" << endl;
				current_user=clone(username);
			}
			else
				cout << "Login Failed" << endl;
		}
		else
			cout << "invalid args. type 'help' for more details." << endl;

	} 
	else if(strcmp(command, "create_group")==0) {
		if(current_user!=NULL)
		{
			char* group_id = strtok(NULL, " ");
		
			if(group_id !=NULL)
				create_group(group_id,current_user);
			else
				cout << "invalid args. type 'help' for more details." << endl;
		}
		else
			cout << "You need to login to create a group" << endl;

		
	} 
	else if(strcmp(command, "join_group")==0) {
		char* group_id = strtok(NULL, " ");
		
		if(group_id !=NULL)
			join_group(group_id,current_user);
		else
			cout << "invalid args. type 'help' for more details." << endl;

	}
	else if(strcmp(command, "leave_group")==0) {
		char* group_id = strtok(NULL, " ");
		
		if(group_id !=NULL)
			leave_group(group_id, current_user);
		else
			cout << "invalid args. type 'help' for more details." << endl;

	}  
	else if(strcmp(command, "list_requests")==0) {
		char* group_id = strtok(NULL, " ");
		
		if(group_id !=NULL)
			list_requests(group_id);
		else
			cout << "invalid args. type 'help' for more details." << endl;

	} 
	else if(strcmp(command, "accept_request")==0) {
		char* group_id = strtok(NULL, " ");
		char* username = strtok(NULL, " ");
		
		if(group_id !=NULL && username != NULL)
			accept_request(group_id,username);
		else
			cout << "invalid args. type 'help' for more details." << endl;

	} 
	else if(strcmp(command, "list_groups")==0) {
		list_groups();
	} 
	else if(strcmp(command, "list_files")==0) {
		char* group_id = strtok(NULL, " ");
		
		if(group_id !=NULL)
			list_files(group_id);
		else
			cout << "invalid args. type 'help' for more details." << endl;
	} 
	else if(strcmp(command, "upload_file")==0) {
		char* file_path = strtok(NULL, " ");
		char* group_id = strtok(NULL, " ");
		
		if(file_path != NULL && group_id !=NULL)
			upload_file(file_path, group_id);
		else
			cout << "invalid args. type 'help' for more details." << endl;

	} 
	else if(strcmp(command, "download_file")==0) {
		
		char* group_id = strtok(NULL, " ");
		char* file_name = strtok(NULL, " ");
		char* dest_path = strtok(NULL, " ");
		
		if(group_id !=NULL && file_name != NULL && dest_path!= NULL)
			download_file(group_id,file_name,dest_path );
		else
			cout << "invalid args. type 'help' for more details." << endl;

	} 
	else if(strcmp(command, "show_downloads")==0) {
		show_downloads();
	} 
	else if(strcmp(command, "stop_share")==0) {
		char* group_id = strtok(NULL, " ");
		char* file_name = strtok(NULL, " ");
		
		if(group_id !=NULL && file_name != NULL)
			stop_share(group_id,file_name);
		else
			cout << "invalid args. type 'help' for more details." << endl;

	} 
	else if(strcmp(command, "logout")==0) {
		current_user=NULL;
	} 
	else if(strcmp(command, "help")==0) {
		help();
	}
	else if(strcmp(command, "whoami")==0) {
		if(current_user!=NULL)
			cout << string(current_user) << endl;
	}  
	else {
		cout << "bad command, type 'help' to get list of commands\n" << endl;
	}
	return command;
}

void help(){
	cout << "Following is the list of commands..." << endl;
	cout << endl;
	cout << "1. create_user <user_id> <passwd>" << endl;
	cout << "2. login <user_id> <passwd>" << endl;
	cout << "3. create_group <group_id>" << endl;
	cout << "4. join_group <group_id>" << endl;
	cout << "5. leave_group <group_id>" << endl;
	cout << "6. list_requests <group_id>" << endl;
	cout << "7. list_requests <group_id>" << endl;
	cout << "8. list_groups" << endl;
	cout << "9. list_files <group_id>" << endl;
	cout << "10. upload_file <file_path> <group_id>" << endl;
	cout << "11. download_file <group_id> <file_name> <destination_path>" << endl;
	cout << "12. show_downloads" << endl;
	cout << "13. stop_share <group_id> <file_name>" << endl;
	cout << "14. logout" << endl;
	cout << endl;
}
