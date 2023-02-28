#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>

class email
{
    public:
        email();
        ~email();
        int SendEmail(void);
};