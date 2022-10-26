#ifndef TRANSIT_HUB_H
#define TRANSIT_HUB_H

#include <string>

class IBaseDevice;

class TransitHub {
public:
	static TransitHub& getInstance() {
		static TransitHub instance;
		return instance;
	}

	~TransitHub();

	TransitHub(const TransitHub&) = delete;
	void operator=(const TransitHub&) = delete;

	void sendData(const std::string& data);
	std::string receiveData();

	void addDevice(IBaseDevice* new_device);

private:
	TransitHub() = default;

protected:
	IBaseDevice* device = nullptr;
};

#endif // TRANSIT_HUB_H