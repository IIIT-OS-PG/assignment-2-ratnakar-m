#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctime>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>

using namespace std;

void write_file()
{
// SIZE TO BE WRITTEN
long lSizeOfArr = 10000000;

//prepare char buffer
char *buf;
buf = (char *)malloc(lSizeOfArr);

// fill buffer
for(long l = 0; l < lSizeOfArr; l++ )
{
buf[l] = 'A';
}

// write by means of ofstream
ofstream MyFile;
MyFile.open(".//file1.dat",ios::binary );
MyFile.write(buf,lSizeOfArr);
MyFile.close();

// write by means of FILE
FILE *dst;
dst = fopen(".//file2.dat", "wb");
long lWritten = fwrite(buf, 1, lSizeOfArr, dst);
fclose(dst);

// free buffer
free(buf);
}

int main(){
	write_file();
}