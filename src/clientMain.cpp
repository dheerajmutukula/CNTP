//program to execute client 
//#include<iostream>
//#include<string.h>
//#include<arpa/inet.h>
//#include<unistd.h>
#include <client.h>
using namespace std;
int main(){
    while(1){
        string uname,passwd;
        Client client("127.0.0.1", 8088);
        cout<<"Please enter your username: ";
        cin>>uname;
        cout<<"Please enter your password: ";
        cin>>passwd;
        //send username and password to server
        client.sendMessage((uname+" "+passwd).c_str());
        
        //receive message from server
        char* buffer = client.receiveMessage();
        if(buffer[0] == '1'){
            cout<<"Authentication successful!"<<endl;
            client.sync();
            break;
        }
        else{
            cout<<"Authentication failed!"<<endl;
        }
    }    
    return 0;
}
