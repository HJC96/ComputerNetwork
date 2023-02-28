#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>

int main()
{
    int client_socket;
    struct sockaddr sock_addr;

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sa_family = AF_INET;                                          // UDP, TCP, ETC
    *(unsigned short*)&sock_addr.sa_data[0] = htons(53);                    // htons(),htonl():'host'to'network'short/long \ port: 2byte, ip:4byte, else 0 
    *(unsigned long*)&sock_addr.sa_data[2] = htonl(2826845953);             //  "168.126.63.1"
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0); // domain, type, protocol
    connect(client_socket, &sock_addr, sizeof(sock_addr));
}

