// IPK project 1 - client for remote calculator
// Author: David Sklenář - xsklen14
// Date: 2023/03/12

#include <iostream>
#include <regex>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>


using namespace std;

int validate_args(int argc, vector <string> argv, string &host_address, int &port_number, string &protocol){
    bool h_flag = false;
    bool p_flag = false;
    bool m_flag = false;
    if (argc != 7)
    {
        cerr << "Invalid number of arguments" << endl;
        return 1;
    }
    for (int i = 1; i < argc; i++){
        if (argv[i] == "-h"){
            if (h_flag){
                cerr << "Duplicate -h argument" << endl;
                return 1;
            }
            if (!regex_match(argv[i+1], regex("^(?:[0-9]{1,3}.){3}[0-9]{1,3}$")))
            {
                cerr << "Invalid IP address" << endl;
                return 1;
            }
            host_address = argv[i+1];
            h_flag = true;
        }
        if (argv[i] == "-p"){
            if (p_flag){
                cerr << "Duplicate -p argument" << endl;
                return 1;
            }
            if (!regex_match(argv[i+1], regex("^[0-9]{1,5}$")) || stoi(argv[i+1]) > 65535)
            {
                cerr << "Invalid port number" << endl;
                return 1;
            }
            port_number = stoi(argv[i+1]);
            p_flag = true;
        }
        if (argv[i] == "-m"){
            if (m_flag){
                cerr << "Duplicate -m argument" << endl;
                return 1;
            }
            // transform to lower case
            transform(argv[i+1].begin(), argv[i+1].end(), argv[i+1].begin(), ::tolower);
            if (argv[i+1] != "udp" && argv[i+1] != "tcp")
            {
                cerr << "Invalid protocol" << endl;
                return 1;
            }
            protocol = argv[i+1];
            m_flag = true;
        }

    }
    if (!h_flag){
        cerr << "Missing -h argument" << endl;
        return 1;
    }
    if (!p_flag){
        cerr << "Missing -p argument" << endl;
        return 1;
    }
    if (!m_flag){
        cerr << "Missing -m argument" << endl;
        return 1;
    }
    return 0;
}

int tcp_communication(struct sockaddr_in server_address, int socket_client){
    char buffer[128] = {0};

    

    // connect to server
    if (connect(socket_client, (struct sockaddr *)&server_address, sizeof(server_address)) != 0){
        cerr << "Connection failed" << endl;
        return 1;
    }

    // send data to server
    while (fgets(buffer, 128, stdin) != NULL){
        if (send(socket_client, buffer, strlen(buffer), 0) < 0){
            cerr << "Send failed" << endl;
            return 1;
        }
        memset(buffer, 0, 128);

        // receive data from server
        if (recv(socket_client, buffer, 128, 0) < 0){
            cerr << "Receive failed";
            return 1;
        }
        cout << buffer;
        if (strcmp(buffer, "BYE\n") == 0){
            break;
        }
        memset(buffer, 0, 128);
    }

    return 0;
}


int main(int argc, char *argv[])
{
    string host_address;
    int port_number;
    string protocol;

    vector <string> all_args = {argv, argv + argc};

    struct sockaddr_in server_address;   
    int socket_client; 

    // validate arguments
    if (validate_args(argc, all_args, host_address, port_number, protocol)){
        exit(1);
    }

    // fill rest of server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);

    // fill server address
    if (inet_pton(AF_INET, host_address.c_str(), &server_address.sin_addr) <= 0){
        cerr << "Inet_pton error for" << host_address << endl;
        exit(1);
    }

    
    // create socket
    if (protocol == "tcp"){
        socket_client = socket(AF_INET, SOCK_STREAM, 0);
        if(tcp_communication(server_address, socket_client)){
            // close socket
            shutdown(socket_client, SHUT_RDWR);
            close(socket_client);
            exit(1);
        }
    }
    else{
        socket_client = socket(AF_INET, SOCK_DGRAM, 0);
        if(tcp_communication(server_address, socket_client)){
            // close socket
            shutdown(socket_client, SHUT_RDWR);
            close(socket_client);
            exit(1);
        }
    }
    if ((socket_client = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
	{
		cerr << "Socket creation error" << endl;
		exit(1);
	}

    // close socket
    shutdown(socket_client, SHUT_RDWR);
    close(socket_client);
    return 0;
}