#include <assign2.h>
#include <client.h>

vector<tracker> extract_tracker_info(char* tracker_info){

	cout << "tracker file: " << tracker_info << endl;
	//vector<tracker>* trackers = new std::vector<tracker>;
	vector<tracker> trackers;

	ifstream infile(tracker_info);
	string line;
	bool login_success = false;
	while (getline(infile, line))
	{

	    istringstream iss(line);
	    tracker tr;
	    char* tracker_host = strtok((char*)line.c_str(), ":");
	    char* tracker_port = strtok(NULL, ":");
	    int portno = atoi(tracker_port);
	    if(tracker_host != NULL && tracker_port != NULL)
	    {
	    	tr.host=clone(tracker_host);
	    	tr.port= (int *) malloc(sizeof(int));
	    	*tr.port=portno;
	    	trackers.push_back(tr);
	    }
	}

	return trackers;
}

void print_tracker_info(vector<tracker> trackers){
	cout << "No. of trackers: " << trackers.size() << endl;
	for(int i=0; i<trackers.size(); i++)
		cout << trackers[i].host << ", " <<trackers[i].port << endl;
}

connected_tracker connect_tracker(vector<tracker> trackers){

	connected_tracker ct;
	ct.sockfd=(int *) malloc(sizeof(int));
	ct.port=(int *) malloc(sizeof(int));
	ct.host = (char *) malloc(20);
	bzero((char *) &ct.host, sizeof(char));

	int *sockfd = (int *) malloc(sizeof(int));
	*sockfd = -1;
	for(int i=0; i<trackers.size(); i++){
		char* host = trackers[i].host;
		int* port = trackers[i].port;
		*sockfd = connect_server(host,*port);
		if (*sockfd < 0) {
			//string msg = string("Tracker-")+to_string(i)+string(" is Down, Trying other tracker");
			//cout << msg<< endl;
			continue;
		}
		else
		{
			ct.host=host;
			ct.sockfd=sockfd;
			ct.port=port;

			break;
		}
	}

	if (*sockfd < 0) {
			
			*ct.sockfd=-1;
			*ct.host=NULL;
			*ct.port=-1;
		}
	return ct;
}

char* send_cmd_to_tracker(char* command) {

	connected_tracker tracker_context= connect_tracker(trackers);
	char* response = NULL;
	
	if(*tracker_context.sockfd > 0){
		char buffer[BUFFER_SIZE];
    	sprintf(buffer, "[%s:%d]=>%s", peer_context.host,*peer_context.portno, command);
    	cout << "command sent: " << buffer << endl;
		response = communicate_with_server(*tracker_context.sockfd, buffer, BUFFER_SIZE);
	}
	else
		cout << "Both the trackers are down. Please ensure at least one is running." << endl;    
}