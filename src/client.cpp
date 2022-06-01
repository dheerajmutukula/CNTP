//program for implement the client logic
#include <client.h>

Client::Client(const char* ip, int port){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    perror("socket");   // Print error message if socket() fails
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    perror("connect");   // Print error message if connect() fails    
}

int Client::getSockfd(){
    return sockfd;
}

void Client::sendMessage(const char* message){
    send(sockfd, message, strlen(message), 0);
}

char* Client::receiveMessage(){
    memset(buffer, 0, sizeof(buffer));
    recv(sockfd, buffer, 1024, 0);
    return buffer;
}

void Client::sync(){
    while(1){
        std::string req;
        req = "sync";
        //send request to server every 5 seconds

        sendMessage(req.c_str());
        char* buffer = receiveMessage();
	std::cout << buffer << std::endl;
        //receive the time from server and set the hardware clock
        // struct timeval tv;
        // struct timezone tz;
        // gettimeofday(&tv, &tz);
        // struct tm* tm = localtime(&tv.tv_sec);
        // tm->tm_hour = atoi(buffer);
        // tm->tm_min = atoi(buffer+4);
        // tm->tm_sec = atoi(buffer+8);
        // tv.tv_sec = mktime(tm);
        // settimeofday(&tv, &tz);
	std::stringstream ss;
        ss << "hwclock -l --set --date=\""<< buffer<<"\"";
        std::string cmd = ss.str();
        system(cmd.c_str());
        sleep(5);
    }    
}
