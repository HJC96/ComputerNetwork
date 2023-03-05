#include "Server.h"

#define DEFAULT_PORT 25
#define MAX_CLIENT 3
void check_port(int argc);
void error_msg(const char* msg);



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
    int clnt_sock;
    Server* my_server = new Server;                     // 객체를 5개? 아니면 객체 하나에 스레드 다섯개? 후자가 맞는듯.
    my_server->SetNetwork(AF_INET);    
    my_server->SetIP(htonl(INADDR_ANY));                // INADDR_ANY: 컴퓨터에 존재하는 랜카드 주소 중 사용가능한것을 사용하라
    my_server->SetPort(htons(stoi(pt)));                       // htons(),htonl():'host'to'network'short/long \ port: 25 
    my_server->CreateSocket(AF_INET, SOCK_STREAM, 0);   // domain, type, protocol
    if(my_server->BindSocket()==-1)    error_msg("Bind Error");
    if(my_server->ListenSocket(MAX_CLIENT)==-1) error_msg("Listen Error"); // MAX_CLIENT 수 만큼 큐에서 대기
    if((clnt_sock = my_server->AcceptSocket())==-1)  error_msg("Accept Error");

    
    int ret;
    char rcv_buffer[256];
    char send_buffer[256];


    memset((char*)&rcv_buffer,0,sizeof(rcv_buffer));
    memset((char*)&send_buffer,0,sizeof(send_buffer));
    snprintf(send_buffer,sizeof(send_buffer),"Hi~");
    recv(clnt_sock, rcv_buffer, 256, 0);
    printf("%s", rcv_buffer);
    ret = send(my_server->GetSocket(), (char*)send_buffer,strlen(send_buffer), 0); // 3rd param not sizeof but strlen

    
    while(1);                                          // main함수가 종료되는 것을 방지

    



}






void error_msg(const char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

void check_port(int argc)
{
    char error[64];
    memset(error,0,sizeof(error));
    snprintf(error,sizeof(error),"PLEASE ENTER YOUR PORT NUMBER, DEFAULT PORT NUMBER IS %d",DEFAULT_PORT);

    if(argc == 1) throw domain_error(error);
}




