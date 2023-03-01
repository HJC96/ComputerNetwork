#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
class MySmtp_Client
{
    public:
        MySmtp_Client();
        ~MySmtp_Client();
        
        void SetNetwork(int internetwork);
        void SetPort(unsigned short port);
        void SetIP(unsigned long ip);
        void CreateSocket(int domain, int type, int protocol);
        int ConnectSocket();
        void SendEmail(string subject, string data);
        int CloseSocket();
    private:
        int ClientSocket;
        int internetwork, port, ip;
        sockaddr sock_addr;



};