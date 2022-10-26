#ifndef I_BASE_SOCKET_H
#define I_BASE_SOCKET_H

#include <string>

class IBaseSocket {
public:
	IBaseSocket() = default;
	virtual ~IBaseSocket() = default; 

	virtual void createSocket() = 0;
	virtual void update() = 0;
	virtual std::string readData() = 0;
	virtual void writeData(const std::string& data) = 0;
};

#endif // I_BASE_SOCKET_H