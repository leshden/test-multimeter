#include <iostream>
#include "base_device.h"
#include "transit_hub.h"

TransitHub::~TransitHub() {
	if (device) {
		delete device;
		device = nullptr;
	}
}

void TransitHub::sendData(const std::string& data) {
	std::cout << "Transit Hub get data : " << data << std::endl; 
	device->inputData(data);
}

std::string TransitHub::receiveData() {
	return device->outputData();
}

void TransitHub::addDevice(IBaseDevice* new_device) {
	if (!new_device) {return;}
	if (device) {delete device;}
	device = new_device;
}