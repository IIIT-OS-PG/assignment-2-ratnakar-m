#include<util.h>

int main(int argc, char *argv[])
{
    int port = 9999;
    int sockfd = connect_server("localhost", port);
    char* file_info_command = "get_file_info moby_dick.txt";
    char* command_buffer = clone(file_info_command);
    char* file_info_json = communicate_with_server(sockfd, command_buffer, BUFFER_SIZE);

    Value file_info_root;
    Reader reader;

    bool parsing_status = reader.parse( file_info_json, file_info_root );


    //cout << "File Info: " << file_info << endl;
    Value pieces = file_info_root["pieces"];
    

    vector<string> names = pieces.getMemberNames();

    int destfd = open("new.txt", O_WRONLY | O_CREAT, 0644);
    if(destfd == -1){
      perror("open");
      return 2;
    }

    for(int k=0; k<names.size(); k++){
        cout << names[k] << endl;
        int size = pieces[names[k]]["piece_size"].asInt();
        
        string piece_data_command = "download_piece "+to_string(k)+string(" ")+to_string(size);
        command_buffer = clone((char*)piece_data_command.c_str());
        sockfd = connect_server("localhost", port);
        char* piece_data = communicate_with_server(sockfd, command_buffer, size);
        char buffer [ BUFFER_SIZE] ; 
        
        int offset = k*BUFFER_SIZE;
        cout << "size: " << size << ", offset: " << offset<< endl;
        if(lseek(destfd,offset,SEEK_SET) < 0) 
          {
            error("error on lseek");
            return NULL;
          }
        int written_size = write (destfd, &piece_data, size);
        //cout << "Piece Data: " << piece_data << endl;
    }    

    close(destfd);
}