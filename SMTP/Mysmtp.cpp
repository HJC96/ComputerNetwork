#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h> // for using sockaddr_in structure



struct sockaddr {
	__uint8_t       sa_len;         /* total length */
	sa_family_t     sa_family;      /* [XSI] address family */
#if __has_ptrcheck
	char            sa_data[__counted_by(sa_len - 2)];
#else
	char            sa_data[14];    /* [XSI] addr value (actually smaller or larger) */
#endif
};


int main()
{
    int client_socket;
    struct sockaddr sock_addr;

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sa_family = AF_INET; // UDP, TCP, ETC
    sock_addr.sa_data[0] = htonl // port, ip ? or ip, port?
    
    
    socklen_t address_len;
    client_socket = socket(AF_INET, SOCK_STREAM, 0); // domain, type, protocol
    connect(client_socket, sock_addr.sa_data, address_len);
}

