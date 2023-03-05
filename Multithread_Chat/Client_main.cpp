#include "Client.h"
#define DEFAULT_PORT "25"
#define DEFAULT_IP   "127.0.0.1"


void check_port(int argc);
void error_msg(const char* msg);
unsigned long String2IPAddr(string str_ip);


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
        pt = DEFAULT_PORT;
        ip = DEFAULT_IP;
    }  
    Client* my_client = new Client;                           // 객체를 5개? 아니면 객체 하나에 스레드 다섯개? 후자가 맞는듯.
    my_client->SetIP(htonl(String2IPAddr(ip)));                         // stol not stoi                
    my_client->SetPort(htons(stoi(pt)));                       // htons(),htonl():'host'to'network'short/long \ port: 25 

    my_client->CreateSocket(AF_INET, SOCK_STREAM, 0); // domain, type, protocol

    if(my_client->ConnectSocket() == -1) error_msg("Connect err");

    
    
    return 0;
}


void error_msg(const char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

void check_port(int argc)
{
    char error[128];
    memset(error,0,sizeof(error));
    snprintf(error,sizeof(error),"PLEASE ENTER YOUR IP AND PORT NUMBER, DEFAULT IP NUMNER IS %s AND PORT NUMBER IS %s",DEFAULT_IP, DEFAULT_PORT);

    if(argc != 3) throw domain_error(error);
}

unsigned long String2IPAddr(string str_ip)
{
    vector<string> token;
    unsigned long ip = 0x0;
    int pos=0;
    str_ip.push_back('.');
    while((pos=str_ip.find('.')) != string::npos)
    {
        token.push_back(str_ip.substr(0,pos));
        str_ip.erase(0,pos+1);
    }
    
    // for(auto mod:token)
    //     cout << mod<<endl;
    ip |= stoi(token[0]) << 24;
    ip |= stoi(token[1]) << 16;
    ip |= stoi(token[2]) << 8;
    ip |= stoi(token[3]);
    
    return ip;
}