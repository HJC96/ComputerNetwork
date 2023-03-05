#include "Client.h"

Client::Client()
{

}

Client::~Client()
{

}

void Client::SetNetwork(int internetwork) {_internetwork = internetwork;}
void Client::SetPort(unsigned short port) {_port = port; }
void Client::SetIP(unsigned long ip)      {_ip = ip;}
void Client::CreateSocket(int domain, int type, int protocol)
{
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sa_family = _internetwork;                                          // UDP, TCP, ETC
    *(unsigned short*)&sock_addr.sa_data[0] = _port;                              // htons(),htonl():'host'to'network'short/long \ port: 25 
    *(unsigned long*)&sock_addr.sa_data[2] = _ip;                                 //  "192.168.0.8" 
    
    ClientSocket = socket(domain, type, 0);

}

int Client::ConnectSocket()
{
    return connect(ClientSocket, &sock_addr, sizeof(sock_addr));
}
int Client::CloseSocket() 
{

} 
