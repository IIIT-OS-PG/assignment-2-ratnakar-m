#include <iostream>
#include <string>

using namespace std;
int  hash_code(string text);

int main(int argc, char **argv){

  cout << "ascii of A " << (int)'A' << endl;
  cout << "ascii of a " << (int)'a' << endl;
  cout << "cricket_code.pdf " << hash_code("cricket_code.pdf") << endl;	
  if(argc >0)
   for(int k=1; k<argc; k++)
	cout << argv[k] << " " <<  hash_code(argv[k]) << endl;

}

int  hash_code(string text){
    int hash = 0, strlen = text.length(), i;
    char character;
    if (strlen == 0)
        return hash;
    for (i = 0; i < strlen; i++) {
        character = text.at(i);
        hash = (31 * hash) + ((int)character);
    }
    return hash; 
}
