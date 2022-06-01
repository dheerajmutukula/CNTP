#include<iostream>
#include<string.h>
#include<arpa/inet.h>
#include<time.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
class Server{
    private:
        int sockfd;
        struct sockaddr_in server_addr, client_addr;
        socklen_t client_addr_len;
        char buffer[1024];
    public:
        Server(int port);
        int acceptClient();
	char* readFromNtpServer();
};
