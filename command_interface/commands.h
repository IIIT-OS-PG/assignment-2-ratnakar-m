#include "commons.h"
string create_user(string username, string password);
string login(string username, string password);
string create_group(string group_id, string owner);
string join_group(string group_id, string username);
string leave_group(string group_id, string username);
string list_requests(string group_id);
string accept_request( string group_id, string username);
string list_groups();
string list_files(string group_id);
string upload_file(string file_path, string group_id);
string download_file(string group_id, string file_name, string destination_path);
string show_downloads();
string stop_share(string group_id, string file_name);
string logout();