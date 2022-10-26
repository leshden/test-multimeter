#ifndef I_BASE_DEVICE_H
#define I_BASE_DEVICE_H

#include <string>

class IBaseDevice {
public:
	IBaseDevice() = default;
	virtual ~IBaseDevice() = default; 

	virtual void inputData(const std::string& data) = 0;
	virtual std::string outputData() = 0;
};

#endif // I_BASE_DEVICE_H