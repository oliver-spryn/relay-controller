#include <Arduino.h>
#include "Relay.h"
#include "RelayStatus.h"
#include "SmartThings.h"

Relay::Relay(SmartThings* st, int relayNumber, int pin) :
	_cloudMsg(""), _number(relayNumber), _pin(pin), _st(st), _status(OPEN) {
	pinMode(_pin, OUTPUT);
}

Relay::~Relay() {

}

void Relay::close(String msg) {
	_cloudMsg = msg;
	_status = CLOSED;
}

void Relay::open(String msg) {
	_cloudMsg = msg;
	_status = OPEN;
}

void Relay::run() {
	digitalWrite(_pin, _status == CLOSED ? HIGH : LOW);

	if (!_cloudMsg.equals("")) {
		_st->send(_cloudMsg);
		_cloudMsg = "";
	}
}

void Relay::toggle(String closeMsg, String openMsg) {
	_status == CLOSED ? open(openMsg) : close(closeMsg);
}

RelayStatus Relay::status() {
	return _status;
}