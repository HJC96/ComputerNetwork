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

int main(int argc, char** argv)
{
    struct sockaddr_in servaddr;
    int sock;
    char buf[MAXBUF];
    int filesize, fp, filenamesize;
    int sread;

    if (argc != 4) {
        printf("Usage: %s <server_ip_address> <server_port_number> <file_name> \n", argv[0]);
        exit(1);
    }
    sock = socket(PF_INET, SOCK_STREAM, 0); // socket 생성
    if (sock == -1)
        error_handling("socket() error");
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
        error_handling("connect() error");

    while (1) {
    memset(buf, 0, MAXBUF);
    sread = read(fp, buf, MAXBUF);
    send(sock, buf, sread, 0);

    if(sread == 0){
        break;
       }
    }
}
void error_handling(char* message) {
        fputs(message, stderr);
        fputc('\n', stderr); exit(1);
}
