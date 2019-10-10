#include <fstream>

using namespace std;

int main () {

   std::ofstream outfile;
   /*outfile.open ("tutorialspoint.txt");

   outfile.write ("This is an apple",16);
   long pos = outfile.tellp();
   outfile.seekp (pos-7);
   //outfile.seekp(0,ios::beg);   
   outfile.write (" sai",4);

   outfile.close();*/

   /*outfile.open ("tutorialspoint.txt", ios::binary);

   outfile.seekp(0,ios::end); 
   outfile.write ("ra",2);
   outfile.close();

   outfile.open ("tutorialspoint.txt", ios::out);
   outfile.seekp(2,ios::end);
   outfile.write ("tn",2);
   outfile.close();

   outfile.open ("tutorialspoint.txt", ios::out);
   outfile.seekp(4,ios::end);
   outfile.write ("a",1);
   
   outfile.close();*/

   FILE *file_ptr;
   file_ptr = fopen("tutorialspoint.txt", "w");
   fclose(file_ptr); 


   //FILE *file_ptr;
   file_ptr = fopen("tutorialspoint.txt", "r+b"); 
   int offset =  0;
   fseek(file_ptr, offset, SEEK_SET);
   int written_c = fwrite("ra", 1, 2, file_ptr);;
   fclose(file_ptr);

   file_ptr = fopen("tutorialspoint.txt", "r+b"); 
   offset =  2;
   fseek(file_ptr, offset, SEEK_SET);
   written_c = fwrite("tn", 1, 2, file_ptr);;
   fclose(file_ptr);

   file_ptr = fopen("tutorialspoint.txt", "r+b"); 
   offset =  4;
   fseek(file_ptr, offset, SEEK_SET);
   written_c = fwrite("a", 1, 1, file_ptr);;
   fclose(file_ptr);

   return 0;
}