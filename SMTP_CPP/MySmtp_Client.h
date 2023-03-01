#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>

using namespace std;
class MySmtp_Client
{
    public:
        MySmtp_Client(int internetwork, unsigned short port, unsigned long ip);
        ~MySmtp_Client();
        int client_socket;
        sockaddr sock_addr;

        void Create_Socket(int domain, int type, int protocol);
        int Connect_Socket();
        void SendEmail(string subject, string data);


};