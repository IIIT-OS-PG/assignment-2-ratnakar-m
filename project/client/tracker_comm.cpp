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
	    cout << "host: " <<tracker_host << ", port: " << portno << endl;
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

int* connect_tracker(vector<tracker> trackers){

	int *sockfd = (int *) malloc(sizeof(int));
	*sockfd = -1;
	for(int i=0; i<trackers.size(); i++){
		char* host = trackers[i].host;
		int* port = trackers[i].port;
		cout << "host: " <<host<< endl;
		*sockfd = connect_server(host,*port);
		if (sockfd < 0) {
			string msg = string("Tracker-")+to_string(i)+string(" is Down, Trying other tracker");
			cout << msg<< endl;;
		}
		else
			break;
	}

	return sockfd;
}