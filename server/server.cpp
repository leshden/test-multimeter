#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "local_socket.h"
#include "transit_hub.h"
#include "multimeter_device.h"

int main(int argc, char const *argv[])
{

	TransitHub::getInstance().addDevice(new MultimeterDevice());

	LocalSocket local_socket;
	local_socket.createSocket();
	local_socket.update();

	std::cout << "Server close" << std::endl;
	return 0;
}