#include <Arduino.h>
#include "LED.h"

LED::LED(SmartThings* st, int relayCount, int ledPin) :
	_count(relayCount), _relays(new RelayStatus[relayCount]), _pin(ledPin), _st(st) {
	pinMode(_pin, OUTPUT);

	for (int i = 0; i < _count; ++i) {
		_relays[i] = OPEN;
	}
}

LED::~LED() {
	delete[] _relays;
}

void LED::off(int relay) {
	if (relay >= _count) return;
	_relays[relay] = OPEN;
}

void LED::on(int relay) {
	if (relay >= _count) return;
	_relays[relay] = CLOSED;
}

void LED::run() {
	bool anyOn = false;

	for (int i = 0; i < _count; ++i) {
		anyOn = anyOn || (_relays[i] == CLOSED);
	}

	digitalWrite(_pin, HIGH);

	if(anyOn)
		_st->shieldSetLED(0, 1, 0); // Green
	else
		_st->shieldSetLED(1, 0, 0); // Red
}