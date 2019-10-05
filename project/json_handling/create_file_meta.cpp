#include <jsoncpp/json/json.h>
#include <iostream>

using namespace std;
using namespace Json;
 
void append_piece(Value& document, int idx, int size, string sha1);

int main() {
    Value root; 
    root["name"] = "assign.pdf";
    root["size"] = 799522;
    root["group"] = "os";
    root["file_sha1"] = "";
    root["pieces"] = Value(arrayValue);
    append_piece(root,1,512000,"");
    append_piece(root,2,299522,"");
    StyledWriter writer;
    // Make a new JSON document for the configuration. Preserve original comments.
    string outputConfig = writer.write( root );
    cout << root << endl; //printing using the root itself
    cout << outputConfig << endl; //printing using the string of root
}

void append_piece(Value& document, int idx, int size, string sha1){
    Value piece;
    piece["piece_no"] = idx;
    piece["piece_size"] = size;
    piece["piece_sha1"] = "";
    piece["peers"] = Value(arrayValue);
    document["pieces"].append(piece);
}
