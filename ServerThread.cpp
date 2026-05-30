#include <iostream>
#include "ServerThread.h"
#include "CameraThread.h"

void ServerThread::serverThreadLoop() {

	//initialize the Winsock
	if (!initializeWinsock()) {
		std::cout << "Failed to initialize Winsock. Exiting server thread." << std::endl;
		return;
	}

	//initialize addrinfo structure
	struct addrinfo* result = NULL, * ptr = NULL, hints;

	//set hints structure to all 0s before setting the fields
	ZeroMemory(&hints, sizeof(hints));

	//set the fields in the hints structure
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	int iResult = getaddrinfo(NULL, std::to_string(serverPort_).c_str(), &hints, &result);
	if (iResult != 0) {
		std::cout << "getaddrinfo failed with error: " << iResult << std::endl;
		return;
	}
	
	//create a SOCKET for the server to listen for client connections
	SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	//ensure the socket was created successfully
	if (ListenSocket == INVALID_SOCKET) {
		std::cout << "socket() failed with error: " << iResult << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	//bind the socket
	iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		std::cout << "bind() failed with error: " << iResult << std::endl;
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	//clean up the addrinfo structure
	freeaddrinfo(result);

	//ensure the socket is listening for client connections
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		std::cout << "listen() failed with error: " << iResult << std::endl;
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	//initialize a SOCKET variable to accept client connections
	SOCKET ClientSocket = INVALID_SOCKET;

	//infinite loop to accept client connections and start a new thread for each client
	while (true) {

		std::cout << "waiting for client connection..." << std::endl;
		
		//accept a client connection
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			std::cout << "accept() failed with error: " << iResult << std::endl;
			continue;
		}

		std::cout << "Client connected" << std::endl;

		//start a new thread to handle the client connection
		CameraThread cThread(ClientSocket);
		cThread.startCameraThread();

	}

}

bool ServerThread::initializeWinsock() {
	WSADATA wsaData;
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cout << "WSAStartup failed with error: " << iResult << std::endl;
		return false;
	}

	return true;
}