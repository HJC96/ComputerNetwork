#include "MySmtp_Client.h"

#define uint4_t uint16_t
#define uint6_t uint16_t

MySmtp_Client::MySmtp_Client()
{
}

MySmtp_Client::~MySmtp_Client()
{
    
}

void MySmtp_Client::SetNetwork(int internetwork)
{
    this->internetwork = internetwork;
}
void MySmtp_Client::SetPort(unsigned short port)
{
    this->port = port;
}

void MySmtp_Client::SetIP(unsigned long ip)
{
    this->ip = ip;
}

void MySmtp_Client::CreateSocket(int domain, int type, int protocol)
{
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sa_family = internetwork;                                          // UDP, TCP, ETC
    *(unsigned short*)&sock_addr.sa_data[0] = port;                    // htons(),htonl():'host'to'network'short/long \ port: 25 
    *(unsigned long*)&sock_addr.sa_data[2] = ip;             //  "192.168.0.8" smtp.gmail.com
    
    ClientSocket = socket(domain, type, 0);
}

int MySmtp_Client::ConnectSocket()
{
    return connect(ClientSocket, &sock_addr, sizeof(sock_addr));
}

void MySmtp_Client::SendEmail(string subject, string data)
{
    int ret;
    char buffer[256];
    
    memset(&buffer,0,sizeof(buffer));
    printf("Send %d bytes\n",ret);
    recv(ClientSocket, buffer, 256, 0);
    printf("%s", buffer);
    ret = send(ClientSocket, "EHLO Hi\r\n",strlen("EHLO Hi\r\n"), 0);
    
    memset(&buffer,0,sizeof(buffer));
    ret = send(ClientSocket, "AUTH LOGIN\r\n",strlen("AUTH LOGIN\r\n"), 0);
    printf("Send %d bytes\n",ret);
    recv(ClientSocket, buffer, 256, 0);
    printf("%s", buffer);

    memset(&buffer,0,sizeof(buffer));
    ret = send(ClientSocket, "aGpj\r\n",strlen("aGpj\r\n"), 0);
    printf("Send %d bytes\n",ret);
    recv(ClientSocket, buffer, 256, 0);
    printf("%s", buffer);

    memset(&buffer,0,sizeof(buffer));
    ret = send(ClientSocket, "Y2tzMTQ3\r\n",strlen("Y2tzMTQ3\r\n"), 0);
    printf("Send %d bytes\n",ret);
    recv(ClientSocket, buffer, 256, 0);
    printf("%s", buffer);

    memset(&buffer,0,sizeof(buffer));
    ret = send(ClientSocket, "mail from:<hjc@mysmtp>\r\n",strlen("mail from:<hjc@mysmtp>\r\n"), 0);
    printf("Send %d bytes\n",ret);
    recv(ClientSocket, buffer, 256, 0);
    printf("%s", buffer);

    ret = send(ClientSocket, "RCPT TO:<gkswlcjs2@naver.com>\r\n",strlen("RCPT TO:<gkswlcjs2@naver.com>\r\n"), 0);
    recv(ClientSocket, buffer, 256, 0);
    printf("%s", buffer);

    ret = send(ClientSocket, "DATA\r\n",strlen("DATA\r\n"), 0);
    recv(ClientSocket, buffer, 256, 0);
    printf("%s", buffer);

    ret = send(ClientSocket, "To:gkswlcjs2@naver.com\nFrom:hjc@hjc\nSubject:This is me\n\nNice To Meet you\r\n",strlen("To:gkswlcjs2@naver.com\nFrom:hjc@hjc\nSubject:This is me\n\nNice To Meet you\r\n"), 0);
    recv(ClientSocket, buffer, 256, 0);
    printf("%s", buffer);

    ret = send(ClientSocket, ".\r\n",strlen(".\r\n"), 0);
    recv(ClientSocket, buffer, 256, 0);
    printf("%s", buffer);


}