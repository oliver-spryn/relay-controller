#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include "LED.h"
#include "RelayStatus.h"
#include "SmartThings.h"

class Relay {
public:
	Relay(SmartThings*, int, int);
	~Relay();

public:
	void close(String);
	void open(String);
	void run();
	void toggle(String, String);
	RelayStatus status();

private:
	String _cloudMsg;
	int _number;
	int _pin;
	SmartThings* _st;
	RelayStatus _status;
};

#endif