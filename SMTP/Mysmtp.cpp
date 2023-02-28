#include "email.h"


typedef struct
{
    uint16_t src;
    uint16_t dst;
    uint32_t ACK;
    uint4_t  HLEN;
    uint4_t  RSV;
    uint6_t  CON;
    uint16_t WIN;
    uint16_t CheckSum;
    uint16_t URGPtr;
}TCP_layout;



int main()
{
    int client_socket;
    struct sockaddr sock_addr;
    const char* msg = "MAIL FROM:<gkswlcjs2@naver.com>";
    struct msghdr mh;
    memset(&mh, 0, sizeof(mh));

    *(char*)&mh.msg_name = *msg;
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sa_family = AF_INET;                                          // UDP, TCP, ETC
    *(unsigned short*)&sock_addr.sa_data[0] = htons(587);                    // htons(),htonl():'host'to'network'short/long \ port: 2byte, ip:4byte, else 0 
    *(unsigned long*)&sock_addr.sa_data[2] = htonl(1823571308);             //  "108.177.125.108" smtp.gmail.com
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0); // domain, type, protocol
    connect(client_socket, &sock_addr, sizeof(sock_addr));

    
    sendmsg(client_socket, &mh,0);
}


//RCPT TO:<jchanvvv@gmail.com>
