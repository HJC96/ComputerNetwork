#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>


#define MAXBUF 1024
void error_handling(char* message);

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    int serv_sock;
    int clnt_sock;
    char message[MAXBUF];
    char message_cpy[MAXBUF];
    int str_len;
    int fd;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    int check_bind;
    int client_len, read_len, file_read_len;

    client_len = sizeof(clnt_addr);

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");
    int clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    if (clnt_sock == -1)
        error_handling("accept() error");
  
    while (1) {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &client_len);
        char filename[MAXBUF];
        memset(message, 0, MAXBUF);

        read_len = recv(clnt_sock, message, MAXBUF, 0);
        if(read_len > 0){
            strcpy(filename,message);
        }
        else{
            close(clnt_sock);
            break;
        }
        fd = open(filename,O_WRONLY | O_CREAT);
        if(!fd){
            error_handling("file open error :");
            break;
        }

    while(1)
    {
        // memset(message, 0, MAXBUF);
        file_read_len = recv(clnt_sock, message, MAXBUF, 0);
        write(fd, message, file_read_len);
        if(file_read_len == EOF | file_read_len == 0)
        {
            printf("END\n");
            break;
        }
    }
    close(clnt_sock);
    close(fd);
}
}
void error_handling(char* message) {
        fputs(message, stderr);
        fputc('\n', stderr); exit(1);
}
