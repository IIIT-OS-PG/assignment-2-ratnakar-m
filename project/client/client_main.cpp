#include <assign2.h>
#include <client.h>

char* current_user=NULL;
vector<tracker> trackers;

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
	struct peer_ctx ctx;
	ctx.host=clone(host);
	ctx.portno=*portno;
	ctx.sockfd=*sockfd;


	pthread_t listener_thread;
    int ret =  pthread_create(&listener_thread, NULL, &listener_handler, (void*)&ctx);
    //pthread_detach(listener_thread);
    if(ret != 0) {
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);
    }
	manage_prompt(trackers);
}




