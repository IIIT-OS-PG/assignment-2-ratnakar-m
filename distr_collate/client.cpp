#include<util.h>

int main(int argc, char *argv[])
{
    int port = 9999;
    int sockfd = connect_server("localhost", port);
    char* file_info_command = "get_file_info short.txt";
    char* command_buffer = clone(file_info_command);
    char* file_info_json = communicate_with_server(sockfd, command_buffer, BUFFER_SIZE);
    cout << "file info json: " << file_info_json << endl;
    Value file_info_root;
    Reader reader;

    bool parsing_status = reader.parse( file_info_json, file_info_root );


    //cout << "File Info: " << file_info << endl;
    Value pieces = file_info_root["pieces"];
    

    vector<string> names = pieces.getMemberNames();

    int destfd = open("new.txt", O_WRONLY | O_CREAT, 0777);
    if(destfd == -1){
      perror("open");
      return 2;
    }

    FILE *file_ptr;
     int iCount;
     char arr[6] = "hello";
 
     file_ptr = fopen("short_new2.txt", "w");
     

    for(int k=0; k<names.size(); k++){
    //for(int k=0; k<1; k++){
        cout << names[k] << endl;
        int size = pieces[names[k]]["piece_size"].asInt();
        
        string piece_data_command = "download_piece "+to_string(k)+string(" ")+to_string(size);
        command_buffer = clone((char*)piece_data_command.c_str());
        sockfd = connect_server("localhost", port);
        //char* piece_data = communicate_with_server(sockfd, command_buffer, size);
        char buffer [ BUFFER_SIZE] ; 
        //char piece_data[ BUFFER_SIZE];
        char* piece_data= communicate_with_server(sockfd, command_buffer, size);

        
        int offset = k*BUFFER_SIZE;
        cout << "size: " << size << ", offset: " << offset<< endl;
        if(lseek(destfd,offset,SEEK_SET) < 0) 
          {
            error("error on lseek");
            return NULL;
          }
        //int written_size = write (destfd, &piece_data, size);
           fseek(file_ptr, offset, SEEK_CUR);
        int iCount = fwrite(piece_data, 1, size, file_ptr);
        cout << "COUNT: " << iCount << endl;
        /*for(int g=0; g<size; g++){
            cout << piece_data[g];
        }*/
        //cout << "Piece Data: " << piece_data << endl;
    }    

     fclose(file_ptr);
    close(destfd);
}