#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
class Client
{
    public:
        Client();
        ~Client();
        
    private:
        sockaddr sock_addr;
        unsigned short port;
        unsigned long ip;


};