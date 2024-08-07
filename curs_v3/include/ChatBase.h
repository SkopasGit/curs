#ifndef CHATBASE_H
#define CHATBASE_H

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>
#include <stdexcept>
#include <cstring>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

// Base class for chat applications
class ChatBase {
protected:
    SOCKET sock;                        // Socket for connection
    const short BUFF_SIZE = 1024;       // Maximum buffer size
    vector<char> buffer;                // Buffer for sending/receiving data
    const char* IP_ADDRESS;             // IP address for connection
    const short PORT_NUMBER;            // Port number for connection

public:
    ChatBase(const char* ip, short port);
    virtual ~ChatBase();
    void CloseConnection();
    void InitializeSocket();
    sockaddr_in InitializeSockAddr();
    void ConnectToServer();
    void BindAndListen();
    int ReceiveData(SOCKET clientSock, vector<char>& recvBuffer);
    void SendData(SOCKET clientSock, const vector<char>& sendBuffer);
    virtual void Run() = 0; // Pure virtual function to be implemented by derived classes
};

#endif // CHATBASE_H
