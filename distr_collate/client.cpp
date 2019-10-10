#include<util.h>

int main(int argc, char *argv[])
{
    int port = 9999;
    int sockfd = connect_server("localhost", port);
    char* src_file = "3d_drawing.mp4";
    char* file_info_command = "get_file_info 3d_drawing.mp4";
    char* command_buffer = clone(file_info_command);
    char* file_info_json = communicate_with_server(sockfd, command_buffer, BUFFER_SIZE);
    cout << "file info json: " << file_info_json << endl;
    Value file_info_root;
    Reader reader;

    bool parsing_status = reader.parse( file_info_json, file_info_root );


    //cout << "File Info: " << file_info << endl;
    Value pieces = file_info_root["pieces"];
    

    vector<string> names = pieces.getMemberNames();

    /*int destfd = open("new.txt", O_WRONLY | O_CREAT, 0777);
    if(destfd == -1){
      perror("open");
      return 2;
    }*/

    FILE *file_ptr;
     int iCount;
     char arr[6] = "hello";
 
     file_ptr = fopen("3d_new.mp4", "wb");
     

    for(int k=0; k<names.size(); k++){
    //for(int k=0; k<1; k++){
        cout << names[k] << endl;
        int size = pieces[names[k]]["piece_size"].asInt();
        
        string piece_data_command = "download_piece 3d_drawing.mp4 "+to_string(k)+string(" ")+to_string(size);
        command_buffer = clone((char*)piece_data_command.c_str());
        sockfd = connect_server("localhost", port);
        char buffer [BUFFER_SIZE] ; 
        char* piece_data= communicate_with_server(sockfd, command_buffer, size);
        
        int offset = k*BUFFER_SIZE;
        cout << "size: " << size << ", offset: " << offset<< endl;
        cout << piece_data << endl;
        //write_to_file1(piece_data, size, offset, destfd);
        write_to_file2(piece_data, size, offset, file_ptr);
    }    

    fclose(file_ptr);
    //close(destfd);
}

void write_to_file1(char* content, int size, int offset, int destfd){
    if(lseek(destfd,offset,SEEK_SET) < 0) 
    {
       error("error on lseek");
    }
    int written_size = write (destfd, &content, size);
}

void write_to_file2(char* content, int size, int offset, FILE* file_ptr){
    fseek(file_ptr, offset, SEEK_SET);
    int written_c = fwrite(content, 1, size, file_ptr);;
    cout << "COUNT: " << written_c << endl;
}