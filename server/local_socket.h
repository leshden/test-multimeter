#ifndef LOCAL_SOCKET_H
#define LOCAL_SOCKET_H

#include "base_socket.h"

class LocalSocket : public IBaseSocket {
public:
	virtual ~LocalSocket();

	virtual void createSocket() override;
	virtual void update() override;
	virtual std::string readData() override;
	virtual void writeData(const std::string& data) override;

protected:
	void bindSocket();
	void listenSocket();
	void acceptClient();
	void getNameClient();

protected:
	int localSocket = -1;
	int acceptedClient = -1;
};

#endif // LOCAL_SOCKET_H