#include "Server.h"
//#include <pthread.h>

#include "chat.h"
#define DEFAULT_PORT "25"
#define MAX_CLIENT 3

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
        check_port(argc);
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
    
    while(1)
    {
        
        if((clnt_sock=my_server->AcceptSocket())==-1) error_msg("Accept Error"); // MAX_CLIENT 수 만큼 큐에서 대기
        sock_data sd;
        sd.clientsock = clnt_sock ;
        sd.server = my_server;
        thread(client_req_handler, ref(sd)).detach();
    }
    my_server->CloseSocket();

}


void client_req_handler(sock_data sd)
{
    thread(recv_message, ref(sd)).detach();
    while(1)
    {    
        char send_buffer[256];
        cin.getline(send_buffer, sizeof(send_buffer),'\n');
        cout << "[You Sended]: " <<send_buffer << endl;
        send(sd.clientsock, send_buffer,strlen(send_buffer), 0);
    }

}



void recv_message(sock_data sd)
{
    while(1)
    {    
        char rcv_buffer[256];
        memset((char*)&rcv_buffer,0,sizeof(rcv_buffer));

        recv(sd.clientsock, rcv_buffer, 256, 0);
        cout << "[You Received]: ";
        
        printf("%s", rcv_buffer);
        cout << endl;
    }

}
/*
        Task To do
        구조 -> main에서 반복문을 돌면서 accept를 받고, 그걸 스레드에 넘겨줘서 처리하게 한다.
        1. 스레드로 클라이언트의 리퀘스트 실행하기
         1.1 함수명 변경필요.
          1.2 전달해줄 구조체 혹은 클래스 생성 필요
           1.2.1 구조체 내용은 ip주소, Accept로 받은 clnt_sock 주소
        2. 리퀘스트 처리하는 스레드로 넘어간 이후는 detach를 해준다.
         2.1 왜 detach가 필요한지 공부필요
          2.1.1 어떤 역할을 하는지도. join을 안해주면 좀비프로세스나 고아 프로세스의 가능성이 있음.
        3. 리팩토링
*/