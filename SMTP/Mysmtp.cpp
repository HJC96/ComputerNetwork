#include "email.h"

int main()
{
    int client_socket;
    struct sockaddr sock_addr;
    
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sa_family = AF_INET;                                          // UDP, TCP, ETC
    *(unsigned short*)&sock_addr.sa_data[0] = htons(80);                    // htons(),htonl():'host'to'network'short/long \ port: 2byte, ip:4byte, else 0 
    *(unsigned long*)&sock_addr.sa_data[2] = htonl(3749890155);             //  "223.130.200.107"
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0); // domain, type, protocol
    connect(client_socket, &sock_addr, sizeof(sock_addr));
}

