#include "MySmtp_Client.h"

const char* connect_err = "Connect Error";
void error_msg(const char* msg);

int main()
{
    MySmtp_Client smtp_client;    
    
    smtp_client.SetNetwork(AF_INET);
    smtp_client.SetPort(htons(25));
    smtp_client.SetIP(htonl(3232235528));
    smtp_client.CreateSocket(AF_INET, SOCK_STREAM, 0); // domain, type, protocol
    
    if(smtp_client.ConnectSocket() == -1)
        error_msg(connect_err);
    smtp_client.SendEmail("tst", "tst");

}


void error_msg(const char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}
