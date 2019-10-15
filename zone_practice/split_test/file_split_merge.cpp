#include <iostream>

using namespace std;

#include <fstream>
#include <memory>
#include <sstream>
#include <vector>

const int UNIT_SIZE = 10*1024; //512KB

unique_ptr<ofstream> create_chunks(vector<string>& chunk_file_names) {
    stringstream filename;
    filename << "chunk" << (chunk_file_names.size() + 1) << ".part";
    chunk_file_names.push_back(filename.str());
    return make_unique<ofstream>(filename.str(), ios::trunc);
}

void split(istream& inStream, int max_units, vector<string>& chunk_file_names) {

    unique_ptr<char[]> buffer(new char[UNIT_SIZE]);
    int num_units = 0;

    unique_ptr<ostream> pOutStream = create_chunks(chunk_file_names);

    while (!inStream.eof()) {
        inStream.read(buffer.get(), UNIT_SIZE);
        pOutStream->write(buffer.get(), inStream.gcount());
        ++num_units;
        if (num_units >= max_units) {
            pOutStream = create_chunks(chunk_file_names);
            num_units = 0;
        }
    }

}

void merge(vector<string>& chunk_file_names, ostream& outStream) {
    for (int n = 0; n < chunk_file_names.size(); ++n) {
        ifstream ifs(chunk_file_names[n]);
        outStream << ifs.rdbuf();
    }
}

void createTestFile(const string& filename) {
    ofstream ofs(filename, ios::trunc);

    unique_ptr<char[]> buffer(new char[UNIT_SIZE]);

    int i = 0;

    for (int n = 0; n < 1024; ++n) {
        for (int m = 0; m < UNIT_SIZE; ++m) {
            buffer[m] = 'a' + (i++ % 26);
        }

        ofs.write(buffer.get(), UNIT_SIZE);
    }
}

int main()
{

    // Create test file

    //string filenameBefore = "assign.pdf";
    //createTestFile(filenameBefore);

    // Split

    ifstream ifs("assign.pdf");
    vector<string> chunk_file_names;

    split(ifs, 1, chunk_file_names);

    // merge

    string filenameAfter = "new_assign.pdf";

    ofstream ofs(filenameAfter, ios::trunc);
    merge(chunk_file_names, ofs);

    return 0;
}