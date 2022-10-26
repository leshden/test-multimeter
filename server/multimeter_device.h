#ifndef MULTIMETER_DEVICE_H
#define MULTIMETER_DEVICE_H

#include "base_device.h"
#include "const_device.h"

class MultimeterChannel;

class MultimeterDevice: public IBaseDevice {
public:
	MultimeterDevice();
	virtual ~MultimeterDevice(); 

	virtual void inputData(const std::string& data) override;
	virtual std::string outputData() override;

protected:
	void requestHandle(const std::string& data);

	bool selectCommand(const std::string& command);
	bool selectChannel(const std::string& channel);
	bool selectRange(const std::string& range);

	bool prepareHandleCommand(const std::string& data);
	void handleCommand();
	
	void fail();

protected:
	int curChannel = 0;
	int curRange = MULTIMETER_RANGE - 1;

	std::string curCommand = START_MEASURE;
	std::string output = "fail";
	
	MultimeterChannel* channels[MULTIMETER_CHANNELS];
};

#endif // MULTIMETER_DEVICE_H