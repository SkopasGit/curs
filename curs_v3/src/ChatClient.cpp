#include "ChatClient.h"
#include <iostream>
#include <algorithm> 

ChatClient::ChatClient(const char* ip, short port) : ChatBase(ip, port) {
    InitializeSocket();
}

void ChatClient::Run() {
    ConnectToServer();

    while (true) {
       // std::fill(buffer.begin(), buffer.end(), '\0');
        cout << "Your (Client) message to server: ";
        
        fgets(buffer.data(), buffer.size(), stdin);

        // Видалити символ нового рядка, якщо є
       // buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());

        if (buffer.empty()) {
            continue; // Пропустити порожні повідомлення
        }

        if (buffer[0] == 'x' && buffer[1] == 'x' && buffer[2] == 'x') {
            CloseConnection();
            return;
        }

        SendData(sock, buffer);
        
        int packetSize = ReceiveData(sock, buffer);
        if (packetSize > 0) {
            buffer[packetSize] = '\0';  // Null-terminate the string
            cout << "Server message: " << buffer.data() << endl;
            std::fill(buffer.begin(), buffer.end(), '\0');
        } else {
            cout << "Error receiving data from server." << endl;
            CloseConnection();
            return;
        }
    }
}

