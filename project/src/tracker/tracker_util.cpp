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

bool file_exists(char* group_id, char* filename){
	ifstream infile("files.txt");
	string line;
	bool does_file_exist = false;
	while (getline(infile, line))
	{
	    istringstream iss(line);
	    char* existing_file = strtok((char*)line.c_str(), ":");
	    char* existing_group = strtok(NULL, ":");
	    if(existing_file != NULL && existing_group != NULL)
	    {
	    	if(strcmp(existing_file, filename)==0 && strcmp(existing_group, group_id)==0){
	    		does_file_exist = true;
	    		break;
	    	}
	    }
	}
	return does_file_exist;
}

void append_file(string file_name, string group_id, int file_size, string file_sha1){
	ofstream outfile;
	outfile.open("files.txt", ios::out | ios::app);
	outfile << file_name+":"+group_id+":"+to_string(file_size)+":"+file_sha1<<endl;
	outfile.close();
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

bool tracker_file_exists(char* full_path){
	struct stat st = {0};
    if (stat(full_path, &st) == -1) {
        return false;
    }
	return true;
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

char* get_files_by_group(char* group_id){
	ifstream infile("files.txt");
	string line;
	string files_list = string("");
	while (getline(infile, line))
	{
	    istringstream iss(line);
	    char* file_name = strtok((char*)line.c_str(), ":");
	    char* existing_group_id = strtok(NULL, ":");
	    char* size = strtok(NULL, ":");
	    char* sha1 = strtok(NULL, ":");
	    if(existing_group_id != NULL && strcmp(existing_group_id, group_id)==0)
	    {
	    	string entry = string(file_name) +", " + string(size) + ", " + string(sha1);
	    	files_list = files_list + entry + "\n";	
	    }
	}
	return clone((char*)files_list.c_str());
}

bool is_owner(char* group_id, char* username){
	ifstream infile("groups.txt");
	string line;
	bool isowner = false;
	while (getline(infile, line))
	{
	    istringstream iss(line);
	    char* existing_group = strtok((char*)line.c_str(), ":");
	    char* existing_owner = strtok(NULL, ":");
	    if(existing_group != NULL && existing_owner != NULL)
	    {
	    	if(strcmp(existing_group, group_id)==0 && strcmp(existing_owner, username)==0)
	    		isowner=true;	
	    }
	}
	return isowner;
}

bool is_member(char* group_id, char* username){
	ifstream infile("membership.txt");
	string line;
	bool ismember = false;
	while (getline(infile, line))
	{
	    istringstream iss(line);
	    char* existing_group = strtok((char*)line.c_str(), ":");
	    char* existing_user = strtok(NULL, ":");
	    if(existing_group != NULL && existing_user != NULL)
	    {
	    	if(strcmp(existing_group, group_id)==0 && strcmp(existing_user, username)==0)
	    		ismember=true;	
	    }
	}
	return ismember;
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
	    	requests_list = requests_list + existing_group + ":" + existing_user + "\n";	
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

int  hash_code(string text){
    int hash_val = 0;
    int len = text.length();
    int k;
    char ch;
    if (len == 0)
        return hash_val;
    for (k = 0; k < len; k++) {
        ch = text.at(k);
        hash_val = (31 * hash_val) + ((int)ch);
    }
    return hash_val; 
}

