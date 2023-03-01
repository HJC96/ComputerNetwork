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
    char rcv_buffer[256];
    char send_buffer[256];
    
    memset((char*)&rcv_buffer,0,sizeof(rcv_buffer));
    memset((char*)&send_buffer,0,sizeof(send_buffer));
    snprintf(send_buffer,sizeof(send_buffer),"EHLO Hi Server\r\n");
    recv(ClientSocket, rcv_buffer, 256, 0);
    printf("%s", rcv_buffer);
    ret = send(ClientSocket, (char*)send_buffer,strlen(send_buffer), 0); // 3rd param not sizeof but strlen
    
    memset(&rcv_buffer,0,sizeof(rcv_buffer));
    memset(&send_buffer,0,sizeof(send_buffer));
    snprintf(send_buffer,sizeof(send_buffer),"AUTH LOGIN\r\n");
    ret = send(ClientSocket, (char*)send_buffer,strlen(send_buffer), 0);
    recv(ClientSocket, rcv_buffer, 256, 0);
    printf("%s", rcv_buffer);

    memset(&rcv_buffer,0,sizeof(rcv_buffer));
    memset(&send_buffer,0,sizeof(send_buffer));
    snprintf(send_buffer,sizeof(send_buffer),"aGpj\r\n"); // base64
    ret = send(ClientSocket, (char*)send_buffer,strlen(send_buffer), 0);
    recv(ClientSocket, rcv_buffer, 256, 0);
    printf("%s", rcv_buffer);

    memset(&rcv_buffer,0,sizeof(rcv_buffer));
    memset(&send_buffer,0,sizeof(send_buffer));
    snprintf(send_buffer,sizeof(send_buffer),"Y2tzMTQ3\r\n");
    ret = send(ClientSocket, (char*)send_buffer,strlen(send_buffer), 0);
    recv(ClientSocket, rcv_buffer, 256, 0);
    printf("%s", rcv_buffer);
    
    memset(&rcv_buffer,0,sizeof(rcv_buffer));
    memset(&send_buffer,0,sizeof(send_buffer));
    snprintf(send_buffer,sizeof(send_buffer),"mail from:<hjc@mysmtp>\r\n");
    ret = send(ClientSocket, (char*)send_buffer,strlen(send_buffer), 0);
    recv(ClientSocket, rcv_buffer, 256, 0);
    printf("%s", rcv_buffer);

    memset(&rcv_buffer,0,sizeof(rcv_buffer));
    memset(&send_buffer,0,sizeof(send_buffer));
    snprintf(send_buffer,sizeof(send_buffer),"RCPT TO:<gkswlcjs2@naver.com>\r\n");
    ret = send(ClientSocket, (char*)send_buffer,strlen(send_buffer), 0);
    recv(ClientSocket, rcv_buffer, 256, 0);
    printf("%s", rcv_buffer);

    memset(&rcv_buffer,0,sizeof(rcv_buffer));
    memset(&send_buffer,0,sizeof(send_buffer));
    snprintf(send_buffer,sizeof(send_buffer),"DATA\r\n");
    ret = send(ClientSocket, (char*)send_buffer,strlen(send_buffer), 0);
    recv(ClientSocket, rcv_buffer, 256, 0);
    printf("%s", rcv_buffer);

    memset(&rcv_buffer,0,sizeof(rcv_buffer));
    memset(&send_buffer,0,sizeof(send_buffer));
    snprintf(send_buffer,sizeof(send_buffer),     "To:gkswlcjs2@naver.com\nFrom:hjc@hjc\nSubject:%s\n\n%s\r\n",subject.c_str(), data.c_str());
    ret = send(ClientSocket, (char*)send_buffer,strlen(send_buffer), 0);
    recv(ClientSocket, rcv_buffer, 256, 0);
    printf("%s", rcv_buffer);

    memset(&rcv_buffer,0,sizeof(rcv_buffer));
    memset(&send_buffer,0,sizeof(send_buffer));
    snprintf(send_buffer,sizeof(send_buffer),".\r\n");
    ret = send(ClientSocket, (char*)send_buffer,strlen(send_buffer), 0);
    recv(ClientSocket, rcv_buffer, 256, 0);
    printf("%s", rcv_buffer);


}

int MySmtp_Client::CloseSocket()
{
    close(ClientSocket);
}