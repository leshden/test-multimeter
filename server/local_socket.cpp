#include "local_socket.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "transit_hub.h"

#define NAME_LOCAL_SOCKET "server_socket.server"
#define BUFFER_SIZE 256

LocalSocket::~LocalSocket() {

}

void LocalSocket::createSocket() {

	localSocket = socket(AF_LOCAL, SOCK_STREAM, 0);

	if (localSocket == -1) {
		std::cout << "Error opening local socket" << std::endl;
		exit(EXIT_FAILURE);
	}

	bindSocket();
	listenSocket();
}

void LocalSocket::bindSocket() {
	struct sockaddr_un localSocketAddr;

	localSocketAddr.sun_family = AF_LOCAL;
	strcpy(localSocketAddr.sun_path, NAME_LOCAL_SOCKET);
	int len = sizeof(localSocketAddr);

	unlink(NAME_LOCAL_SOCKET);
	int bindResult = bind(localSocket, (struct sockaddr *) &localSocketAddr, len);
	if (bindResult == -1) {
		std::cout << "Error binding name to local socket" << std::endl;
		close(localSocket);
		exit(EXIT_FAILURE);
	}
}

void LocalSocket::listenSocket() {
	int listenResult = listen(localSocket, 0);
	if (listenResult == -1) {
		std::cout << "Error listening for local socket" << std::endl;
		close(localSocket);
		exit(EXIT_FAILURE);
	}
}

void LocalSocket::acceptClient() {
	std::cout << "Waiting to accept a connection..." << std::endl;
	acceptedClient = accept(localSocket, NULL, NULL);
	if (acceptedClient == -1) {
		std::cout << "Error accept connection" << std::endl;
		close(acceptedClient);
		return;
	}
}

void LocalSocket::getNameClient() {
	struct sockaddr_un clientAddr;
	memset(&clientAddr, 0, sizeof(struct sockaddr_un));
	
	socklen_t clientAddrLen = sizeof(clientAddr);
	int peerName = getpeername(acceptedClient, (struct sockaddr *) &clientAddr, &clientAddrLen);
	if(peerName == -1) {
		std::cout << "Error get name client" << std::endl;
		close(acceptedClient);
		return;
	} else {
		std::cout << "Name client: " << clientAddr.sun_path << std::endl;
	}
}

void LocalSocket::update() {
	for(;;) {
		acceptClient();
		//getNameClient();

		TransitHub::getInstance().sendData(readData());
		writeData(TransitHub::getInstance().receiveData());

		close(acceptedClient);
	}
}

std::string LocalSocket::readData() {
	char buf[BUFFER_SIZE];
	memset(buf, 0, BUFFER_SIZE);

	int readDataFromClient = recv(acceptedClient, buf, sizeof(buf), 0);
	if (readDataFromClient == -1) {
		std::cout << "Error read data from client" << std::endl;
		close(acceptedClient);
	} else {
		std::cout << "Data from client : " << buf << '\n';
	}

	return {buf};
}

void LocalSocket::writeData(const std::string& data) {

	char buf[BUFFER_SIZE];
	memset(buf, 0, BUFFER_SIZE);
	strcpy(buf, data.c_str());
	
	int sendToClient = send(acceptedClient, buf, sizeof(buf), 0);
	if (sendToClient == -1) {
		std::cout << "Error send data to client" << std::endl;
		close(acceptedClient);
	} else {
		std::cout << "Send data: " << buf << std::endl;
	}
}