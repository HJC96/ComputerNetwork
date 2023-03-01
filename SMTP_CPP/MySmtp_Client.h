#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>


class MySmtp_Client
{
    public:
        MySmtp_Client();
        ~MySmtp_Client();
        int SendEmail(void);

};