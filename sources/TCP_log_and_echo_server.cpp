#include "../headers/TCP_log_and_echo_server.h"

int TCP_log_and_echo_server(){
    /// initialize a socket
    WSAData wsData;
    WORD ver = MAKEWORD(2, 2);
    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0){
        std::cerr<<"Can't initialize winsock! Quitting."<<std::endl;
        return -1;
    }
    /// create a socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET){
        std::cerr<<"Can't create a socket! Quitting."<<std::endl;
        return -1;
    }
    /// bind socket to IP-address and port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(12345);
    hint.sin_addr.S_un.S_addr = INADDR_ANY; ///could also use inet_pton

    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR){
        ShowLastError(); ///cerr<<"Can't bind to this socket, it is in use!"<<WSAGetLastError()<<endl;
        return -1;
    }
    /// tell winsocket the socket is for listenning
    listen(listening, SOMAXCONN);
    /// wait for connection
    sockaddr_in client;
    int clientSize = sizeof(client);

    SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

    char host[NI_MAXHOST];      /// client's remote name
    char service[NI_MAXHOST];   /// service (i.e. port) the client is connected on
    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXHOST);

    //DWORD dwRetval = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXHOST, 0);
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXHOST, 0) == 0){
        std::cout<<"host "<<host<<" connected on port "<< service <<std::endl;
    }
    else{
        inet_ntoa(client.sin_addr);///host
        std::cout<<"host "<<host<<" connected on port "<< ntohs(client.sin_port) <<std::endl;
    }
    /// close listening socket
    closesocket(listening);
    /// while-loop: accept and echo messages
    char buf[4096];

    while(true){
        ZeroMemory(buf, sizeof(buf));
        ///wait for client to send data
        int bytesReceived = recv(clientSocket, buf, sizeof(buf), 0);
        if (bytesReceived == SOCKET_ERROR){
            std::cerr << "Error in recv(). Quitting."<<std::endl;
            break;
        }
        if (bytesReceived == 0){
            std::cout << "Client has disconnected."<<std::endl;
            break;
        }

        ///log message to the log file
        std::string s{buf};
        if (s[0] != char(13)){
            logToFile(s);
        std::cout<<"Receved and logged " << s.size() << " symbols." << std::endl;
        }
        ///echo message back to client
        send(clientSocket, buf, bytesReceived+1, 0);

        char ex[] = "exit";
        if (!strcmp(buf, ex)){
            std::cout<<"You entered ""exit!"<<std::endl;
            break;
        }
    }
    /// close socket
    closesocket(clientSocket);
    /// cleanup winsock
    WSACleanup();
	return 0;
}
