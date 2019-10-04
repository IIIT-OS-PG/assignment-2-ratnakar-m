#include <iostream>
#include <string>

using namespace std;

string get_base_name(string file_path);

int main(int argc, char** argv){
   if(argc <1)
	cout << "usage: base_name <file_path_FQ>" << endl;

   cout << "base name: " << get_base_name(argv[1]) << endl;
}

string get_base_name(string file_path){
    string base_filename = file_path.substr(file_path.find_last_of("/") + 1);
    return base_filename;
}
