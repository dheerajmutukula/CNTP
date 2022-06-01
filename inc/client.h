#include<iostream>
#include<sstream>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/time.h>
class Client{
    private:
        int sockfd;
        struct sockaddr_in server_addr;
        char buffer[1024];
    public:
        Client(const char* ip, int port);
        int getSockfd();
        void sendMessage(const char* message);
        char* receiveMessage();
        void sync();
};
