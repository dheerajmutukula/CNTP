//program to implement main logic
#include<iostream>
#include<string.h>
#include<sstream>
#include<fstream>
#include<signal.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <server.h>
using namespace std;
int main(){
    Server server(8088);
    char buffer[1024];

    while(1){

    int clientfd = server.acceptClient();
    pid_t pid = fork();
    perror("fork");

    if(pid == 0){ //child process
    memset(buffer, 0, sizeof(buffer));
    recv(clientfd, buffer, 1024, 0);
    //check whether the buffer data is found in the database or not
    ifstream file("../data/users");
    string line,buf = buffer;
    if(file.is_open()){
        while(getline(file, line)){
            if(line == buf){
                send(clientfd, "1", 1, 0);
                cout << "Authentication successful!" << endl;
                break;
            }
        }
        file.close();
        if(line != buf){
            send(clientfd, "0", 1, 0);
            cout << "Authentication failed!" << endl;
            continue;
        }
        while(1){
            memset(buffer,0,sizeof(buffer));
            recv(clientfd, buffer, 1024, 0);
            //read the hwclock in epoch time and send it to client 
             stringstream ss;
             ss << "hwclock -r";
	    //ss << "hwclock --setepoch --getepoch=1970";
             string cmd = ss.str();
             FILE *fp = popen(cmd.c_str(), "r");
             if(fp == NULL){
                 perror("popen");
                 exit(1);
             }
             char buf[1024];
             while(fgets(buf, sizeof(buf), fp) != NULL){
		 std::cout << buf << std::endl;
                 //send(clientfd, buf, strlen(buf), 0);
		 memset(buf,0,sizeof(buf));
             }
             pclose(fp);
	    char* time = server.readFromNtpServer();
	    send(clientfd,time,strlen(time),0);

           //send the system time in epoch time to client
            // stringstream ss;
            // ss << "date +%s";
            // string cmd = ss.str();
            // FILE *fp = popen(cmd.c_str(), "r");
            // if(fp == NULL){
            //     perror("popen");
            //     exit(1);
            // }
            // char buf[1024];
            // while(fgets(buf, sizeof(buf), fp) != NULL){
            //     send(clientfd, buf, strlen(buf), 0);
            // }
            // pclose(fp);
        }
    }
    close(clientfd);
    exit(0);
    }
    signal(SIGCHLD,SIG_IGN);
    close(clientfd);
    }
    return 0;
}
