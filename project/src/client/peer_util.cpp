#include <assign2.h>

bool piece_info_exists(char* full_path){
	struct stat st = {0};
    if (stat(full_path, &st) == -1) {
        return false;
    }
	return true;
}

bool does_file_exist(char* full_path){
	struct stat st = {0};
    if (stat(full_path, &st) == -1) {
        return false;
    }
	return true;
}