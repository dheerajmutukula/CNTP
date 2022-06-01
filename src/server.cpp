//program to implement server logic
#include <server.h>

Server::Server(int port){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    perror("socket");   // Print error message if socket() fails
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    perror("bind");   // Print error message if bind() fails
    listen(sockfd, 5);
    perror("listen");   // Print error message if listen() fails
}

int Server::acceptClient(){
    int client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);
    perror("accept");   // Print error message if accept() fails
    return client_sockfd;
}

char* Server::readFromNtpServer(){
		char* hostname = (char *)"216.239.35.8"; //google server
		int portno=123;     //NTP is port 123
		int maxlen=1024;        //check our buffers
		int i;          // misc var i
		unsigned char msg[48]={010,0,0,0,0,0,0,0,0};    // the packet we send
		unsigned long  buf[maxlen]; // the buffer we get back
		//struct in_addr ipaddr;  
		struct protoent *proto;
		struct sockaddr_in server_addr;
		int s;  // socket
		long tmit;
		proto=getprotobyname("udp");
		s=socket(PF_INET, SOCK_DGRAM, proto->p_proto);
		perror("socket");
		memset( &server_addr, 0, sizeof( server_addr ));
		server_addr.sin_family=AF_INET;
		server_addr.sin_addr.s_addr = inet_addr(hostname);
		server_addr.sin_port=htons(portno);
		i=sendto(s,msg,sizeof(msg),0,(struct sockaddr *)&server_addr,sizeof(server_addr));
		perror("sendto");
		struct sockaddr saddr;
		socklen_t saddr_l = sizeof (saddr);
		i=recvfrom(s,buf,48,0,&saddr,&saddr_l);
		perror("recvfr:");
		tmit=ntohl((time_t)buf[4]);
		tmit-= 2208988800U;
		std::cout << "time is " << ctime(&tmit)  << std::endl;
		i=time(0);
		std::cout << "System time is " << (i-tmit) << " seconds off" << std::endl;
		return ctime(&tmit);
}
