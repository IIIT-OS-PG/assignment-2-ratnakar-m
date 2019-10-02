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