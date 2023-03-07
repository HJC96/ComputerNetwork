#include <thread>

#define DEFAULT_PORT "25"
#define DEFAULT_IP   "127.0.0.1"

void check_port_client(int argc);
void check_port_server(int argc);
void error_msg(const char* msg);
unsigned long String2IPAddr(string str_ip);



void error_msg(const char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

void check_port_client(int argc)
{
    char error[128];
    memset(error,0,sizeof(error));
    snprintf(error,sizeof(error),"PLEASE RE-ENTER YOUR IP AND PORT NUMBER, DEFAULT IP NUMNER IS %s AND PORT NUMBER IS %s",DEFAULT_IP, DEFAULT_PORT);

    if(argc != 3) throw domain_error(error);
}

void check_port_server(int argc)
{
    char error[128];
    memset(error,0,sizeof(error));
    snprintf(error,sizeof(error),"PLEASE RE-ENTER YOUR PORT NUMBER, DEFAULT IP NUMNER IS %s AND PORT NUMBER IS %s",DEFAULT_IP, DEFAULT_PORT);

    if(argc != 2) throw domain_error(error);
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
    
    ip |= stoi(token[0]) << 24;
    ip |= stoi(token[1]) << 16;
    ip |= stoi(token[2]) << 8;
    ip |= stoi(token[3]);
    
    return ip;
}








