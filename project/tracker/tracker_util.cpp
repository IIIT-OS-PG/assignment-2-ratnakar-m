#include <assign2.h>

bool user_exists(char* username){
	ifstream infile("users.txt");
	string line;
	bool user_exists = false;
	while (getline(infile, line))
	{
	    istringstream iss(line);
	    char* existing_user = strtok((char*)line.c_str(), ":");
	    if(existing_user != NULL && strcmp(existing_user, username)==0)
	    {
	    	user_exists = true;
	    	break;
	    }
	}
	return user_exists;
}

bool group_exists(char* group_id){
	ifstream infile("groups.txt");
	string line;
	bool group_exists = false;
	while (getline(infile, line))
	{
	    istringstream iss(line);
	    char* existing_group = strtok((char*)line.c_str(), ":");
	    if(existing_group != NULL && strcmp(existing_group, group_id)==0)
	    {
	    	group_exists = true;
	    	break;
	    }
	}
	return group_exists;
}

bool request_exists(char* group_id, char* username){
	ifstream infile("join_requests.txt");
	string line;
	bool request_exists = false;
	while (getline(infile, line))
	{
	    istringstream iss(line);
	    char* existing_group = strtok((char*)line.c_str(), ":");
	    char* existing_user = strtok(NULL, ":");
	    if(existing_group != NULL && existing_user != NULL)
	    {
	    	if(strcmp(existing_group, group_id)==0 && strcmp(existing_user, username)==0){
	    		request_exists = true;
	    		break;
	    	}
	    }
	}
	return request_exists;
}

char* get_groups(){
	ifstream infile("groups.txt");
	string line;
	string groups_list = string("");
	while (getline(infile, line))
	{
	    istringstream iss(line);
	    char* existing_group = strtok((char*)line.c_str(), ":");
	    if(existing_group != NULL)
	    {
	    	groups_list = groups_list + existing_group + "\n";	
	    }
	}
	return clone((char*)groups_list.c_str());
}

char* get_requests(){
	ifstream infile("join_requests.txt");
	string line;
	string requests_list = string("");
	while (getline(infile, line))
	{
	    istringstream iss(line);
	    char* existing_group = strtok((char*)line.c_str(), ":");
	    char* existing_user = strtok(NULL, ":");
	    if(existing_group != NULL)
	    {
	    	requests_list = requests_list + existing_group + ":" + existing_user;	
	    }
	}
	return clone((char*)requests_list.c_str());
}

void delete_line(string old_file, string deleteline) {
	string line;
	ifstream infile;
	infile.open(old_file);
	ofstream tmp;
	tmp.open("tmp.txt");
	while (getline(infile, line)) {
	    if (line != deleteline)
	        tmp << line << endl;
	}
	infile.close();
	tmp.close();
	const char * olf = old_file.c_str();
	remove(olf);
	rename("tmp.txt", olf);
}