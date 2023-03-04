#include "Server.h"
#define DEFAULT_PORT 25

void check_port(int argc)
{
    char error[64];
    memset(error,0,sizeof(error));
    snprintf(error,sizeof(error),"PLEASE ENTER YOUR PORT NUMBER, DEFAULT PORT NUMBER IS %d",DEFAULT_PORT);

    if(argc == 1) throw domain_error(error);
}

int main(int argc, char* argv[])
{
    string pt;
    try
    {
        check_port(argc);
        pt = string(argv[1]);
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        pt = to_string(DEFAULT_PORT);
    }  
    Server* my_server = new Server;                     // 객체를 5개? 아니면 객체 하나에 스레드 다섯개? 후자가 맞는듯.
    my_server->SetNetwork(AF_INET);    
    my_server->SetIP(htonl(INADDR_ANY));                // INADDR_ANY: 컴퓨터에 존재하는 랜카드 주소 중 사용가능한것을 사용하라
    my_server->SetPort(stoi(pt));                       // htons(),htonl():'host'to'network'short/long \ port: 25 
    my_server->CreateSocket(AF_INET, SOCK_STREAM, 0);   // domain, type, protocol
    
    


}