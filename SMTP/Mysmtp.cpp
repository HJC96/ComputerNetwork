#include "email.h"
#include <unistd.h>

#define uint4_t uint16_t
#define uint6_t uint16_t

const char* connect_err = "Connect Error";
void error_msg(const char* msg);

int main()
{
    int client_socket;
    struct sockaddr sock_addr;
    //const char* msg = "MAIL FROM:<gkswlcjs2@naver.com>\r\n"; // According to the SMTP spec, added <CR><LF> 
    //const char* msg2 = "RCPT TO:<jchanvvv@gmail.com>\r\n";

    struct msghdr mh;
	char buffer[2048];

    int ret = 0;

    memset(&mh, 0, sizeof(mh));

    //*(char*)&mh.msg_name = *msg;
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sa_family = AF_INET;                                          // UDP, TCP, ETC
    *(unsigned short*)&sock_addr.sa_data[0] = htons(587);                    // htons(),htonl():'host'to'network'short/long \ port: 2byte, ip:4byte, else 0 , 465: 587:TLS 
    *(unsigned long*)&sock_addr.sa_data[2] = htonl(1823571308);             //  "108.177.125.108" smtp.gmail.com
    
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0); // domain, type, protocol
    if(connect(client_socket, &sock_addr, sizeof(sock_addr)) == -1)
        error_msg(connect_err);

    
    recv(client_socket, buffer, 256, 0);
    printf("%s", buffer);
    ret = send(client_socket, "EHLO smtp.google.com\r\n",sizeof("HELO smtp.google.com\r\n"), 0);
    printf("Send %d bytes\n",ret);

    recv(client_socket, buffer, 512, 0);
    printf("%s", buffer);

    ret = send(client_socket, "STARTTLS\r\n",sizeof("STARTTLS\r\n"), 0);
    printf("Send %d bytes\n",ret);
    recv(client_socket, buffer, 256, 0);
    printf("%s", buffer);

    // ret = send(client_socket, "AUTH LOGIN\r\n",sizeof("AUTH LOGIN\r\n"), 0);
    // recv(client_socket, buffer, 512, 0);
    // printf("%s", buffer);

    // ret = send(client_socket, "mail from:<gkswlcjs2@naver.com>\r\n",sizeof("mail from:<gkswlcjs2@naver.com>\r\n"), 0);
    // printf("Send %d bytes\n",ret);

    // recv(client_socket, buffer, 256, 0);
    // printf("%s", buffer);


    // //sleep(1);
    // ret = send(client_socket, "RCPT TO:<jchanvvv@gmail.com>\r\n",sizeof("RCPT TO:<jchanvvv@gmail.com>\r\n"), 0);
    // recv(client_socket, buffer, 256, 0);
    // printf("%s", buffer);

    // ret = send(client_socket, "DATA\r\n",sizeof("DATA\r\n"), 0);
    // recv(client_socket, buffer, 256, 0);
    // printf("%s", buffer);


}


void error_msg(const char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

//RCPT TO:<jchanvvv@gmail.com>
