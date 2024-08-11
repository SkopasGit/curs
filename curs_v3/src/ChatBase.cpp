#include "ChatBase.h"


ChatBase::ChatBase(const char* ip, short port)
    : buffer(BUFF_SIZE), IP_ADDRESS(ip), PORT_NUMBER(port) {
    WSADATA wsData;
    int erStat = WSAStartup(MAKEWORD(2, 2), &wsData);
    if (erStat != 0) {
        throw runtime_error("Error initializing WinSock version #" + to_string(WSAGetLastError()));
    }
    cout << "WinSock initialization successful" << endl;
}


ChatBase::~ChatBase() {
    WSACleanup();
}


void ChatBase::CloseConnection() {
    shutdown(sock, SD_BOTH);
    closesocket(sock);
}

void ChatBase::InitializeSocket() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        throw runtime_error("Error initializing socket #" + to_string(WSAGetLastError()));
    }
    cout << "Socket initialization successful" << endl;
}


sockaddr_in ChatBase::InitializeSockAddr() {
    sockaddr_in servInfo;
    in_addr ip_to_num;
    int erStat = inet_pton(AF_INET, IP_ADDRESS, &ip_to_num);
    if (erStat <= 0) {
        throw runtime_error("Error converting IP to special numeric format");
    }

    ZeroMemory(&servInfo, sizeof(servInfo));
    servInfo.sin_family = AF_INET;
    servInfo.sin_addr = ip_to_num;
    servInfo.sin_port = htons(PORT_NUMBER);

    return servInfo;
}


void ChatBase::ConnectToServer() {
    sockaddr_in servInfo = InitializeSockAddr();

    int erStat = connect(sock, (sockaddr*)&servInfo, sizeof(servInfo));
    if (erStat != 0) {
        throw runtime_error("Failed to connect to server. Error #" + to_string(WSAGetLastError()));
    }
    cout << "Connection successfully established. Ready to send message to server" << endl;
}


void ChatBase::BindAndListen() {
    sockaddr_in servInfo = InitializeSockAddr();

    int erStat = bind(sock, (sockaddr*)&servInfo, sizeof(servInfo));
    if (erStat != 0) {
        throw runtime_error("Error binding socket to server info. Error #" + to_string(WSAGetLastError()));
    }
    cout << "Socket binding to server info successful" << endl;

    erStat = listen(sock, SOMAXCONN);
    if (erStat != 0) {
        throw runtime_error("Failed to start listening. Error #" + to_string(WSAGetLastError()));
    }
    cout << "Listening..." << endl;
}


int ChatBase::ReceiveData(SOCKET clientSock, vector<char>& recvBuffer) {
    int packetSize =  recv(clientSock, recvBuffer.data(), recvBuffer.size(), 0);
    if (packetSize == SOCKET_ERROR) {
        //throw runtime_error("Failed to receive message. Error #" + to_string(WSAGetLastError()));
        std::cout<<"wrong reccive"<<std::endl;    
    }
    return packetSize;
}


void ChatBase::SendData(SOCKET clientSock, const vector<char>& sendBuffer) {
    int packetSize = send(clientSock, sendBuffer.data(), sendBuffer.size(), 0);
    if (packetSize == SOCKET_ERROR) {
       // throw runtime_error("Failed to send message. Error #" + to_string(WSAGetLastError()));
       std::cout<<"wrong reccive"<<std::endl;    

    }
}
 
