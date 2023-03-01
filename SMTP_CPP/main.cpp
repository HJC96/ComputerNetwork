#include "MySmtp_Client.h"

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
    const char* msg3 = "To:<jchanvvv@gmail.com>\nFrom:<hjc@hjc>\nSubject:Hi\r\n\r\nNice To Meet you\r\n.\r\n";
    struct msghdr mh;
	char buffer[2048];

    int ret = 0;

    memset(&mh, 0, sizeof(mh));

    //*(char*)&mh.msg_name = *msg;
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sa_family = AF_INET;                                          // UDP, TCP, ETC
    *(unsigned short*)&sock_addr.sa_data[0] = htons(25);                    // htons(),htonl():'host'to'network'short/long \ port: 25 
    *(unsigned long*)&sock_addr.sa_data[2] = htonl(3232235528);             //  "192.168.0.8" smtp.gmail.com
    
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0); // domain, type, protocol
    if(connect(client_socket, &sock_addr, sizeof(sock_addr)) == -1)
        error_msg(connect_err);

    
    ret = send(client_socket, "EHLO Hi\r\n",strlen("EHLO Hi\r\n"), 0); // 3nd param not sizeof but strlen (sizeof로 했을때, 마지막'0'이 남아았이서 오류가 떴던 것)
    printf("Send %d bytes\n",ret);
    recv(client_socket, buffer, 256, 0);
    printf("%s", buffer);

    memset(&buffer,0,sizeof(buffer));
    ret = send(client_socket, "AUTH LOGIN\r\n",strlen("AUTH LOGIN\r\n"), 0);
    printf("Send %d bytes\n",ret);
    recv(client_socket, buffer, 256, 0);
    printf("%s", buffer);

    memset(&buffer,0,sizeof(buffer));
    ret = send(client_socket, "aGpj\r\n",strlen("aGpj\r\n"), 0);
    printf("Send %d bytes\n",ret);
    recv(client_socket, buffer, 256, 0);
    printf("%s", buffer);

    memset(&buffer,0,sizeof(buffer));
    ret = send(client_socket, "Y2tzMTQ3\r\n",strlen("Y2tzMTQ3\r\n"), 0);
    printf("Send %d bytes\n",ret);
    recv(client_socket, buffer, 256, 0);
    printf("%s", buffer);


    memset(&buffer,0,sizeof(buffer));
    ret = send(client_socket, "mail from:<hjc@mysmtp>\r\n",strlen("mail from:<hjc@mysmtp>\r\n"), 0);
    printf("Send %d bytes\n",ret);

    recv(client_socket, buffer, 256, 0);
    printf("%s", buffer);


    ret = send(client_socket, "RCPT TO:<gkswlcjs2@naver.com>\r\n",strlen("RCPT TO:<gkswlcjs2@naver.com>\r\n"), 0);
    recv(client_socket, buffer, 256, 0);
    printf("%s", buffer);

    ret = send(client_socket, "DATA\r\n",strlen("DATA\r\n"), 0);
    recv(client_socket, buffer, 256, 0);
    printf("%s", buffer);

    ret = send(client_socket, "To:gkswlcjs2@naver.com\nFrom:hjc@hjc\nSubject:This is me\n\nNice To Meet you\r\n",strlen("To:gkswlcjs2@naver.com\nFrom:hjc@hjc\nSubject:This is me\n\nNice To Meet you\r\n"), 0);
    recv(client_socket, buffer, 256, 0);
    printf("%s", buffer);

    ret = send(client_socket, ".\r\n",strlen(".\r\n"), 0);
    recv(client_socket, buffer, 256, 0);
    printf("%s", buffer);

}


void error_msg(const char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}
