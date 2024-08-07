#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include "ChatBase.h"

// Derived class for client chat
class ChatClient : public ChatBase {
public:
    ChatClient(const char* ip, short port);
    void Run() override;
};

#endif // CHATCLIENT_H
