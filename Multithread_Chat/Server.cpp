#include "Server.h"


Server::Server()
{
    
}
Server::~Server()
{

}
void Server::SetNetwork(int internetwork) {_internetwork = internetwork;}
void Server::SetPort(unsigned short port) {_port = port; }
void Server::SetIP(unsigned long ip)      {_ip = ip;}
void Server::CreateSocket(int domain, int type, int protocol)
{
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sa_family = _internetwork;                                          // UDP, TCP, ETC
    *(unsigned short*)&sock_addr.sa_data[0] = _port;                              // htons(),htonl():'host'to'network'short/long \ port: 25 
    *(unsigned long*)&sock_addr.sa_data[2] = _ip;                                 //  "192.168.0.8" 
    
    ServerSocket = socket(domain, type, 0);

}

int Server::GetSocket() { return ServerSocket;}


int Server::BindSocket()
{
    return ::bind(ServerSocket, &sock_addr, (socklen_t)sizeof(sock_addr)); // not using std::bind but using bind from <thread> 
}

int Server::ListenSocket(int backlog)
{
    return listen(ServerSocket,backlog);
}

int Server::AcceptSocket()
{
    return accept(ServerSocket, &sock_addr, (socklen_t*)sock_addr.sa_data);
}
int Server::CloseSocket()
{
     return 0;
}


