#include "Server.h"

#include "chat.h"
#define DEFAULT_PORT "25"
#define MAX_CLIENT 0

class sock_data
{
    public:
        int clientsock;
        Server* server;
} ;

void client_req_handler(sock_data sd);
void recv_message(sock_data sd);



int main(int argc, char* argv[])
{
    string pt;
    try
    {
        check_port_server(argc);
        pt = string(argv[1]);
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        pt = DEFAULT_PORT;
    }  
    int clnt_sock;
    Server* my_server = new Server;                                             // 객체를 5개? 아니면 객체 하나에 스레드 다섯개? 후자가 맞는듯.
    my_server->SetNetwork(AF_INET);      
    my_server->SetIP(htonl(INADDR_ANY));                                        // INADDR_ANY: 컴퓨터에 존재하는 랜카드 주소 중 사용가능한것을 사용하라
    my_server->SetPort(htons(stoi(pt)));                                        // htons(),htonl():'host'to'network'short/long \ port: 25 
    my_server->CreateSocket(AF_INET, SOCK_STREAM, 0);                           // domain, type, protocol
    if(my_server->BindSocket()==-1)    error_msg("Bind Error");
    if(my_server->ListenSocket(MAX_CLIENT)==-1) error_msg("Listen Error");      // MAX_CLIENT 수 만큼 큐에서 대기
    
       
    if((clnt_sock=my_server->AcceptSocket())==-1) error_msg("Accept Error"); // MAX_CLIENT 수 만큼 큐에서 대기
    sock_data sd;
    sd.clientsock = clnt_sock ;
    sd.server = my_server;
    thread thd1(recv_message, ref(sd));
    
    thd1.join();
    my_server->CloseSocket(my_server->GetSocket());

}


void client_req_handler(sock_data sd)
{
    while(1)
    {    
        char send_buffer[256];
        cin.getline(send_buffer, sizeof(send_buffer),'\n');
        if(!strcmp(send_buffer,"quit"))
        {
            break;
        }
        cout << "[You Sended]: " <<send_buffer << endl;
        send(sd.clientsock, send_buffer,strlen(send_buffer), 0);
    }
    sd.server->CloseSocket(sd.clientsock); 
    sd.server->CloseSocket(sd.server->GetSocket());

}



void recv_message(sock_data sd)
{
    char rcv_buffer[256];
    thread(client_req_handler, ref(sd)).detach();
    while(recv(sd.clientsock, rcv_buffer, 256, 0)>0)
    {    
        if(!strcmp(rcv_buffer,"quit"))
            break;        
        cout << "[You Received]: ";
        printf("%s", rcv_buffer);
        cout << endl;
        memset((char*)&rcv_buffer,0,sizeof(rcv_buffer));
    }

}
