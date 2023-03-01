#include "email.h"
#include <unistd.h>

#define uint4_t uint16_t
#define uint6_t uint16_t


// typedef struct
// {
//     uint16_t src_port;
//     uint16_t dst_prot;
//     uint32_t ACK;
//     uint4_t  HLEN;
//     uint4_t  RSV;
//     uint6_t  CON;
//     uint16_t WIN;
//     uint16_t CheckSum;
//     uint16_t URGPtr;
// }TCP_layout;

const char* connect_err = "Connect Error";
void error_msg(const char* msg);

int main()
{
    int client_socket;
    struct sockaddr sock_addr;
    const char* msg = "MAIL FROM:<gkswlcjs2@naver.com>";
    struct msghdr mh;
	char buffer[2048];


    //TCP_layout msg;
    // msg.src_port = 0b11111111;
    // msg.dst_prot = 0b11111111;
    // msg.ACK      = 0b1111;
    // msg.HLEN     = 0b1111;
    // msg.RSV      = 0b1111;
    // msg.CON      = 0b1111;
    // msg.WIN      = 0b1111;
    // msg.CheckSum = 0b11111111;
    // msg.URGPtr   = 0b11111111;
    memset(&mh, 0, sizeof(mh));

    //*(char*)&mh.msg_name = *msg;
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sa_family = AF_INET;                                          // UDP, TCP, ETC
    *(unsigned short*)&sock_addr.sa_data[0] = htons(587);                    // htons(),htonl():'host'to'network'short/long \ port: 2byte, ip:4byte, else 0 
    *(unsigned long*)&sock_addr.sa_data[2] = htonl(1823571308);             //  "108.177.125.108" smtp.gmail.com
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0); // domain, type, protocol
    if(connect(client_socket, &sock_addr, sizeof(sock_addr)) == -1)
        error_msg(connect_err);

    
    send(client_socket, &msg,sizeof(msg), 0);
    recv(client_socket, buffer, 256, 0);
    printf("%s", buffer);
}


void error_msg(const char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

//RCPT TO:<jchanvvv@gmail.com>
