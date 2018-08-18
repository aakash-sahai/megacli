/*
 * EndStop.cpp
 *
 *  Created on: Aug-11-2018
 *      Author: Aakash Sahai
 */

#include "EndStop.h"

const byte EndStop::minPin[MAX_MKS_ENDSTOPS] =
	{ X_MIN_PIN, Y_MIN_PIN, Z_MIN_PIN };

const byte EndStop::maxPin[MAX_MKS_ENDSTOPS] =
	{ X_MAX_PIN, Y_MAX_PIN, Z_MAX_PIN  };

EndStop::EndStop(byte number) {
	if (number < 0 || number > MAX_MKS_ENDSTOPS) {
		return;
	}
	_number = number;
	_min = new PushButton(minPin[number-1]);
	_max = new PushButton(maxPin[number-1]);
	_onPress = 0;
	_onRelease = 0;
	_min->onPress(&_onPressHandler, this);
	_max->onPress(&_onPressHandler, this);
	_min->onRelease(&_onReleaseHandler, this);
	_max->onRelease(&_onReleaseHandler, this);
}

EndStop::~EndStop() {
}

void EndStop::begin(Scheduler &runner) {
	if (_number == -1) {
		return;
	}
	_min->begin(runner);
	_max->begin(runner);
}

void EndStop::_onPressHandler(PushButton &pb, void *ctx) {
	EndStop &stop = *(EndStop *)ctx;
	if (stop._onPress) {
		if (pb.getPin() == stop.minPin[stop._number]) {
			stop._onPress(stop, EndStop::MIN_STOP, pb);
		} else {
			stop._onPress(stop, EndStop::MAX_STOP, pb);
		}
	}
}

void EndStop::_onReleaseHandler(PushButton &pb, void *ctx) {
	EndStop &stop = *(EndStop *)ctx;
	if (stop._onRelease) {
		if (pb.getPin() == stop.minPin[stop._number]) {
			stop._onRelease(stop, EndStop::MIN_STOP, pb);
		} else {
			stop._onRelease(stop, EndStop::MAX_STOP, pb);
		}
	}
}
