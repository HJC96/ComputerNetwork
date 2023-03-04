#include "Client.h"
#define DEFAULT_PORT 25
#define DEFAULT_IP   3232235528

void check_port(int argc)
{
    char error[128];
    memset(error,0,sizeof(error));
    snprintf(error,sizeof(error),"PLEASE ENTER YOUR IP AND PORT NUMBER, DEFAULT IP NUMNER IS %ld AND PORT NUMBER IS %d",DEFAULT_IP, DEFAULT_PORT);

    if(argc != 3) throw domain_error(error);
}

int main(int argc, char* argv[])
{
    string pt;
    string ip;
    try
    {
        check_port(argc);
        ip = string(argv[1]);
        pt = string(argv[2]);
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        pt = to_string(DEFAULT_PORT);
        ip = to_string(DEFAULT_IP);
    }  
    Client* my_client = new Client;                     // 객체를 5개? 아니면 객체 하나에 스레드 다섯개? 후자가 맞는듯.
    my_client->SetNetwork(AF_INET);    
    my_client->SetIP(htonl(stol(ip)));                  // stol not stoi                
    my_client->SetPort(stoi(pt));                       // htons(),htonl():'host'to'network'short/long \ port: 25 
    my_client->CreateSocket(AF_INET, SOCK_STREAM, 0);   // domain, type, protocol
    
    


}