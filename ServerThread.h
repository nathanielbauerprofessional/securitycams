#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <winsock2.h>
#include <ws2tcpip.h>

class ServerThread
{
public:

    void startServerThread() { serverThread_ = std::jthread(&ServerThread::serverThreadLoop, this); };

private:

    std::jthread serverThread_;
    int serverPort_ = 5000;

    void serverThreadLoop();
    bool initializeWinsock();

};