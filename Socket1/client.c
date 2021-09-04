#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

char* msg1 = "0123456789";
char* msg2 = "HELLOWORLD";
char* msg3 = "ABCDEFGHIJ";

void error_handling(char* message);

int main(int argc, char** argv)
{
        int sock;
        char message[BUFSIZE];
        int str_len;
        struct sockaddr_in serv_addr;

        if (argc != 3) {
                printf("Usage: %s <IP> <port> \n", argv[0]);
                exit(1);
        }
        sock = socket(PF_INET, SOCK_STREAM, 0);
        if (sock == -1)
                error_handling("socket() error");
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
        serv_addr.sin_port = htons(atoi(argv[2]));

        if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
                error_handling("connect() error");

        int len1, len2, len3;
        len1 = strlen(msg1);
        len2 = strlen(msg2);
        len3 = strlen(msg3);

        send(sock, msg1, len1, 0);
        send(sock, msg2, len1, 0);
        send(sock, msg3, len1, 0);

        while (1) {
                /* 메시지 입력, 전송*/
                fputs("전송할 메시지를 입력 하세요(q to quit): ", stdout);
                fgets(message, BUFSIZE, stdin);

                if (!strcmp(message, "q\n")) break;
                send(sock, message, strlen(message), 0);

                /* 메시지 수신, 출력 사용하지 않음*/
                str_len = recv(sock, message, BUFSIZE - 1, 0);
                message[str_len] = 0;
                printf("서버로부터 전송된 메시지: %s \n", message);

                close(sock);
                return 0;
        }
}

void error_handling(char* message) {
        fputs(message, stderr);
        fputc('\n', stderr); exit(1);
}

