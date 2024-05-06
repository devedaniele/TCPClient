#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>

using namespace std;

class Client{
    public:
        int PORT;
        string IP;

        Client(){
            PORT = 8080;
            IP = "127.0.0.1";
        }

        int createSocket(){
            server =  socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

            if (server == -1){
                cout  << "socket creation failed." << endl;

                return -1;
            }

            return 0;
        }

        int connectServer(){
			if (connect(server,(struct sockaddr*)&serverAddress,sizeof(serverAddress)) != 0){
				cout << "server connection failed." << endl;

				return -1;
			}

			return 0;
		}

        int setupClient(){
            if (createSocket() == -1){				
				return -1;
			}

            /* 

            int opt = 1;

            if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,sizeof(opt))){
				cout << "setsockopt failed." << endl;

				return 1;
			} */

            serverAddress.sin_family = AF_INET;
			serverAddress.sin_addr.s_addr = inet_addr(IP.c_str());
			serverAddress.sin_port = htons(PORT);

            return 0;
        }

        int readData(){
			ssize_t bytesRead = read(server,buffer,1024);

            if (bytesRead == -1){
                return -1;
            }

            cout << buffer << endl;

            return 0;
		}

        int sendString(string message){
			int byteSent = 0;
            int totalByteSent = 0;

            while(totalByteSent < message.size()){
                byteSent = write(server,message.c_str(),message.size());

                if (byteSent == -1){
                    return -1;
                }

                totalByteSent += byteSent;
            }

            return 0;
		}

        int closeClient(){
            return close(server);
        }

        ~Client(){
			closeClient();
		}
    
    private:
        int server;
        struct sockaddr_in serverAddress;
        char buffer[1024];
};