#include "multimeter_channel.h"
#include <utility>
#include <iostream>
#include "const_device.h"

const std::vector<std::pair<float, float>> range_voltage = {
	std::make_pair(0.0000001f, 0.001f),
	std::make_pair(0.001f, 1.f),
	std::make_pair(1.f, 1000.f),
	std::make_pair(1000.f, 1000000.f)
};

MultimeterChannel::MultimeterChannel() {
	ranges.push_back(MULTIMETER_RANGE - 1);
}

std::string MultimeterChannel::getStatus() {

	std::string param{STATE_ERROR};

	switch(state) {
		case ERROR : param = STATE_ERROR; break;
		case IDLE : return param = STATE_IDLE; break;
		case MEASURE: return param = ((rand() % 100) < 20) ? STATE_BUSY : STATE_MEASURE; break;
		case BUSY: return param = STATE_BUSY; break;
	}

	return generateResponse(param);
}

std::string MultimeterChannel::startMeasure() {
	state = MEASURE;
	return generateResponse("");
}

std::string MultimeterChannel::stopMeasure() {
	state = IDLE;
	return generateResponse("");
}

std::string MultimeterChannel::setRange(int range) {
	ranges.clear();
	ranges.push_back(range);
	return generateResponse("range" + std::to_string(range));
}

std::string MultimeterChannel::generateResponse(const std::string& param) {
	return ((rand() % 100) < 20) ? "fail " + param : "ok " + param; 
}

std::string MultimeterChannel::getResult() {

	std::string param{""};

	for(const int range : ranges) {
		float res = getRandomResult(std::get<0>(range_voltage[range]), std::get<1>(range_voltage[range]));
		param += " " + std::to_string(res);
	}

	return generateResponse(param);
}

float MultimeterChannel::getRandomResult(float startRange, float endRange) {
	return startRange + (rand() / (RAND_MAX / (endRange - startRange)));
}