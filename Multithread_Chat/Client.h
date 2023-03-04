#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <unistd.h>
#include <stdexcept>

using namespace std;
class Client
{
    public:
        Client();
        ~Client();
        void SetNetwork(int internetwork);
        void SetPort(unsigned short port);
        void SetIP(unsigned long ip);
        void CreateSocket(int domain, int type, int protocol);
        int ConnectSocket();
        void SendEmail(string subject, string data);
        int CloseSocket();    
    private:
        int _internetwork;
        int ClientSocket;
        sockaddr sock_addr;
        unsigned short _port;
        unsigned long _ip;


};