#include <iostream>
#include <vector>
#include <algorithm>
#include "multimeter_device.h"
#include "multimeter_channel.h"

const std::vector<std::string> commands{
START_MEASURE, 
SET_RANGE, 
STOP_MEASURE, 
GET_STATUS, 
GET_RESULT};



MultimeterDevice::MultimeterDevice() {
	for (int i{0}; i < MULTIMETER_CHANNELS; ++i) {
		channels[i] = new MultimeterChannel();
	}
}

MultimeterDevice::~MultimeterDevice() {
	for (int i{0}; i < MULTIMETER_CHANNELS; ++i) {
		delete channels[i];
	}
}

void MultimeterDevice::inputData(const std::string& data) {
	std::cout << "Handle Commands Multimeter - " << data << std::endl;
	requestHandle(data);
}

std::string MultimeterDevice::outputData() {
	return output;
}

void MultimeterDevice::fail() {
	output = "fail";
}

void MultimeterDevice::requestHandle(const std::string& data) {
	if(!prepareHandleCommand(data)) {
		fail();
		return;
	}

	handleCommand();
}

bool MultimeterDevice::prepareHandleCommand(const std::string& data) {
	if (data.empty()) {
		return false;
	}

	size_t pos = 0;
	std::vector<std::string> requests;
	std::string tmp{data};

	while ((pos = tmp.find(" ")) != std::string::npos) {
		requests.push_back(tmp.substr(0, pos));
		tmp.erase(0, pos + 1);
	}

	if (!tmp.empty()) {
		requests.push_back(tmp);
	}

	if (requests.size() == 0) {
		return false;
	}

	if (!selectCommand(requests[0])) {
		return false;
	}

	if (!selectChannel(requests[1])) {
		return false;
	}

	bool hasRange = false; 
	for (const auto&request : requests ) {
		if (request.find("range") != std::string::npos) {
			hasRange = true;
			break;
		}
	}

	if (hasRange && !selectRange(requests[2])) {
		return false;
	}

	return true;
}

bool MultimeterDevice::selectCommand(const std::string& command) {
	if(std::find(commands.begin(), commands.end(), command) != commands.end()) {
		curCommand = command;
		return true;
	}

	return false;
}

bool MultimeterDevice::selectChannel(const std::string& channel) {
	std::string mask = "channel";
	if (channel.find(mask) != 0) {
		return false;
	}

	curChannel = stoi(channel.substr(mask.length()));
	if (curChannel < 0 || curChannel >= MULTIMETER_CHANNELS) {
		curChannel = 0;
		return false;
	}

	return true;
}

bool MultimeterDevice::selectRange(const std::string& range) {
	std::string mask = "range";
	if (range.find(mask) != 0) {
		return false;
	}

	curRange = stoi(range.substr(mask.length()));
	if (curRange < 0 || curRange >= MULTIMETER_RANGE) {
		curRange = MULTIMETER_RANGE;
		return false;
	}

	return true;
}

void MultimeterDevice::handleCommand() {

	MultimeterChannel* channel = channels[curChannel];
	if (curCommand == GET_STATUS) {
		output = channel->getStatus();
	} else if (curCommand == START_MEASURE) {
		output = channel->startMeasure();
	} else if (curCommand == STOP_MEASURE) {
		output = channel->stopMeasure();
	} else if (curCommand == SET_RANGE) {
		output = channel->setRange(curRange);
	} else if (curCommand == GET_RESULT) {
		output = channel->getResult();
	}
	
}