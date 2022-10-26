#ifndef MULTIMETER_CHANNEL_H
#define MULTIMETER_CHANNEL_H

#include <string>
#include <vector>

class MultimeterChannel {
public:
	
	MultimeterChannel();

	std::string getStatus();
	std::string startMeasure();
	std::string stopMeasure();
	std::string setRange(int range);
	std::string getResult();

protected:

	std::string generateResponse(const std::string& param);
	float getRandomResult(float startRange, float endRange);

protected:

	enum State {
		ERROR,
		IDLE,
		MEASURE,
		BUSY 
	};

	State state = IDLE;
	std::vector<int> ranges;
};

#endif // MULTIMETER_CHANNEL_H