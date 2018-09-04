/*
 * Pin.cpp
 *
 *  Created on: Aug-11-2018
 *      Author: Aakash Sahai
 */

#include "Pin.h"

namespace mksgen {

void Pin::begin(Scheduler &runner) {
}

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
	if (_pin == -1 || _mode != OUTPUT) { return; }
	if (_type == Pin::Type::DIGITAL) {
		digitalWrite(_pin, value);
	} else if (_type == Pin::Type::ANALOG) {
		analogWrite(_pin, value);
	}
}

void Pin::exec(char *args[], char **result) {
	*result = (char *)"do ok";
}

void Pin::get(char *args[], char **result) {
  *result = 0;
	if (strcmp(args[0], "value") == 0) {
		Serial.println(get());
	} else if (strcmp(args[0], "pin") == 0) {
		Serial.println(_pin);
	} else {
		Serial.println("get failed: no such attribute");
	}
}

void Pin::set(char *args[], char **result) {
	if (strcmp(args[0], "value")) {
		*result = (char *)"set failed: only 'value' can be set";
		return;
	}
	int value = atoi(args[1]);
	set(value);
	*result = (char *)"set ok";
}

/*
 * create <name> as pin { digital | analog } { input | input_pullup | output } <pin>
 */
Runnable *Pin::create(char *args[]) {
	int pin = -1;

	byte type = Pin::Type::DIGITAL;
	byte mode = INPUT_PULLUP;

	if (strcmp(args[0], "analog") == 0) {
		type = Pin::Type::ANALOG;
		pin = atoi(&args[2][1]) + A0;
	} else {
		pin = atoi(args[2]);
	}

	if (strcmp(args[1], "input") == 0) {
		mode = INPUT;
	} else if (strcmp(args[1], "input_pullup") == 0) {
		mode = INPUT_PULLUP;
	} else if (strcmp(args[1], "output") == 0) {
		mode = OUTPUT;
	}

	Pin *obj = new Pin(pin, type, mode);
	return obj;
}

}
