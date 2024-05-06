#include <iostream>
#include "../client.hpp"

using namespace std;

int main(int argc, char const* argv[]){
    Client client;

    client.IP = "0.0.0.0";
    client.PORT = 8767;

    // if (client.setupClient() != 0){
    //     return -1;
    // }

    string command = "pwd";

    int conn = 1;

    while (true){
        if (client.setupClient() != 0){
           return -1;
        }

        conn = client.connectServer();

        if (conn == 0){
            cout << "$ ";
            cin >> command;

            if (command == "exit"){
                break;
            }

            client.sendString(command);
                
            cout << "\nfrom server: ";
            client.readData();
        }
        
        if (client.closeClient() !=0 ){
            return -1;
        }
    };

   return 0;  
}
