#include "Client.h"
#include "chat.h"

void send_message(Client* my_client);


int main(int argc, char* argv[])
{
    string pt;
    string ip;
    try
    {
        check_port_client(argc);
        ip = string(argv[1]);
        pt = string(argv[2]);
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        pt = DEFAULT_PORT;
        ip = DEFAULT_IP;
    }  
    Client* my_client = new Client;                                     // 객체를 5개? 아니면 객체 하나에 스레드 다섯개? 후자가 맞는듯.
    my_client->SetIP(htonl(String2IPAddr(ip)));                         // stol not stoi                
    my_client->SetPort(htons(stoi(pt)));                                // htons(),htonl():'host'to'network'short/long \ port: 25 
    my_client->CreateSocket(AF_INET, SOCK_STREAM, 0);                   // domain, type, protocol

    if(my_client->ConnectSocket() == -1) error_msg("Connect err");

        
    char send_buffer[256];


    thread(send_message, ref(my_client)).detach();

    char rcv_buffer[256];
    while(recv(my_client->GetSocket(), rcv_buffer, 256, 0)>0)
    {
        cout << "[You Received]: ";
        printf("%s", rcv_buffer);
        cout << endl;
        memset((char*)&rcv_buffer,0,sizeof(rcv_buffer));
    }
    return 0;
}



void send_message(Client* my_client)
{
    
    while(1)
    {    
        char send_buffer[256];
        cin.getline(send_buffer, sizeof(send_buffer),'\n');
        if(!strcmp(send_buffer,"quit"))
            break;
        cout << "[You Sended]: " <<send_buffer << endl;
        send(my_client->GetSocket(), send_buffer,strlen(send_buffer), 0);
    }
    my_client->CloseSocket();
}
