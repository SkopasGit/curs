#include "ChatClient.h"
#include "ChatServer.h"

// Main function to run server or client
const char* defIP = "127.0.0.1";
const short port = 3617;

int main() {
    try {
        char selectNumber;
        std::cout << "Enter the number (1: Server, 2: Client): ";
        std::cin >> selectNumber;

        switch (selectNumber) {
            case '1': {
                ChoiseTask server(defIP, port);
                server.Run();
                break;
            }
            case '2': {
                ChatClient client(defIP, port);
                client.Run();
                break;
            }
            default:
                std::cout << "Wrong number" << std::endl;
                return 1;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
