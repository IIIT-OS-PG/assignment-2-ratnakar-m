#include <assign2.h>
#include <client.h>

char* current_user=NULL;
vector<tracker> trackers;
struct peer_ctx peer_context;

int main(int argc, char **argv) {
	if (argc < 3) {
       cout << "Usage: client <ip> <port> <tracker_info_file>" << endl;
       exit(1);
    }
    char* host = argv[1];
	int *sockfd = (int *) malloc(sizeof(int));
	int *portno = (int *) malloc(sizeof(int));
	char * tracker_info = argv[3];
	*portno = atoi(argv[2]);

	*sockfd = start_service(host,*portno);
	trackers = extract_tracker_info(tracker_info);
	//print_tracker_info(trackers);

	int *sockfd_ptr = (int *) malloc(sizeof(int));
	//struct peer_ctx peer_context;
	peer_context.host=clone(host);
	peer_context.portno=portno;
	peer_context.sockfd=sockfd;
	cout << "peer_context.host: " << peer_context.host << endl;
	cout << "peer_context.portno: " << *peer_context.portno << endl;


	pthread_t listener_thread;
    int ret =  pthread_create(&listener_thread, NULL, &listener_handler, (void*)&peer_context);
    //pthread_detach(listener_thread);
    if(ret != 0) {
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);
    }
	manage_prompt();
}

void send_cmd_to_tracker(char* command, int sockfd) {
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "[%s:%d] %s", peer_context.host,*peer_context.portno, command);
    communicate_with_server(sockfd, buffer, BUFFER_SIZE);
}




