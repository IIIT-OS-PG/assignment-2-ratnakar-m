#include<util.h>

int main(int argc, char *argv[])
{
    int port = 8888;
    int sockfd = connect_server("localhost", port);
    char* file_info_command = "get_file_info moby_dick.txt";
    char* command_buffer = clone(file_info_command);
    char* file_info = communicate_with_server(sockfd, command_buffer, BUFFER_SIZE);

    cout << "File Info: " << file_info << endl;
    sockfd = connect_server("localhost", port);
    char* piece_data_command = "download_piece 1 512";
    command_buffer = clone(piece_data_command);
    char* piece_data = communicate_with_server(sockfd, command_buffer, BUFFER_SIZE);
    cout << "Piece Data: " << piece_data << endl;
}