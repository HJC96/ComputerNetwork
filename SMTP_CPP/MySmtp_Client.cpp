#include "MySmtp_Client.h"

#define uint4_t uint16_t
#define uint6_t uint16_t

MySmtp_Client::MySmtp_Client(int internetwork, unsigned short port, unsigned long ip)
{
    int client_socket;
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sa_family = internetwork;                                          // UDP, TCP, ETC
    *(unsigned short*)&sock_addr.sa_data[0] = port;                    // htons(),htonl():'host'to'network'short/long \ port: 25 
    *(unsigned long*)&sock_addr.sa_data[2] = ip;             //  "192.168.0.8" smtp.gmail.com
    
}

MySmtp_Client::~MySmtp_Client()
{
    
}

void MySmtp_Client::Create_Socket(int domain, int type, int protocol)
{
    client_socket = socket(domain, type, 0);
}

int MySmtp_Client::Connect_Socket()
{
    return connect(client_socket, &sock_addr, sizeof(sock_addr));
}

void MySmtp_Client::SendEmail(string subject, string data)
{
    int ret;
    char buffer[256];
    
    memset(&buffer,0,sizeof(buffer));
    printf("Send %d bytes\n",ret);
    recv(client_socket, buffer, 256, 0);
    printf("%s", buffer);
    ret = send(client_socket, "EHLO Hi\r\n",strlen("EHLO Hi\r\n"), 0);
    
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