char* create_user(char* username, char* password);
char* login(char* username, char* password);
char* create_group(char* group_id, char* owner);
char* join_group(char* group_id, char* username);
char* leave_group(char* group_id, char* username);
char* list_requests(char* group_id);
char* accept_request( char* group_id, char* owner, char* subject);
char* list_groups();
char* list_files(char* group_id);
//char* upload_file(char* file_path, char* group_id, char* file_metadata);
char* upload_file(char* file_name, char* group_id, char* username, char* file_meta);
char* download_file(char* group_id, char* file_name, char* destination_path);
char* show_downloads();
char* stop_share(char* group_id, char* file_name);
char* logout(char* username);