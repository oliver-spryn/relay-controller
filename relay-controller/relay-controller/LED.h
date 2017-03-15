#ifndef LED_H
#define LED_H

#include "RelayStatus.h"
#include "SmartThings.h"

class LED {
public:
	LED(SmartThings*, int, int);
	~LED();

public:
	void off(int);
	void on(int);
	void run();

private:
	int _count;
	int _pin;
	RelayStatus* _relays;
	SmartThings* _st;
};

#endif