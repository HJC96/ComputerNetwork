#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
class Server
{
    public:
        Server();
        ~Server();
        void SetNetwork(int internetwork);
        void SetPort(unsigned short port);
        void SetIP(unsigned long ip);
        int CreateSocket();
        int BindSocket();
        int AcceptSocket();
        int CloseSocket();
        
    private:
        sockaddr sock_addr;
        unsigned short port;
        unsigned long ip;

    


};