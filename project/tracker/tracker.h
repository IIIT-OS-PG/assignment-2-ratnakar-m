char* serve_command(char* command_line);
bool user_exists(char* username);
bool group_exists(char* group_id);
char* get_groups();
bool request_exists(char* group_id, char* username);
char* get_requests();
void delete_line(string old_file, string deleteline);
bool is_owner(char* group_id, char* username);