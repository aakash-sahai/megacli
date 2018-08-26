/*
 * Pin.cpp
 *
 *  Created on: Aug-11-2018
 *      Author: Aakash Sahai
 */

#include "Pin.h"

namespace mksgen {

Pin::Pin(byte aPin, byte type, byte mode) {
	_pin = aPin;
  _type = type;
  _mode = mode;
	if (type == Pin::Type::DIGITAL) {
		pinMode(aPin, mode);
	} else if (type != Pin::Type::ANALOG) {
		_pin = -1;
	}
}

Pin::~Pin() {
}

int Pin::get(void) {
  if (_pin == -1) { return -1; }
	if (_type == Pin::Type::DIGITAL) {
		return digitalRead(_pin);
	} else if (_type == Pin::Type::ANALOG) {
		analogRead(_pin);
	}
}

void Pin::set(int value) {
	if (_pin == -1) { return; }
	if (_type == Pin::Type::DIGITAL) {
		digitalWrite(_pin, value);
	} else if (_type == Pin::Type::ANALOG) {
		analogWrite(_pin, value);
	}
}

void Pin::exec(void *obj, CLI::Command cmd, char *result) {
	Pin &pin = *(Pin *)obj;
	return;
}

}
