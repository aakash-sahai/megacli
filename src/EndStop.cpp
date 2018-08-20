/*
 * EndStop.cpp
 *
 *  Created on: Aug-11-2018
 *      Author: Aakash Sahai
 */

#include "EndStop.h"

namespace mksgen {

const byte EndStop::minPin[MAX_MKS_ENDSTOPS] =
	{ X_MIN_PIN, Y_MIN_PIN, Z_MIN_PIN };

const byte EndStop::maxPin[MAX_MKS_ENDSTOPS] =
	{ X_MAX_PIN, Y_MAX_PIN, Z_MAX_PIN  };

EndStop::EndStop(byte number) {
	if (number < 0 || number > MAX_MKS_ENDSTOPS) {
		return;
	}
	_number = number - 1;
	_min = new PushButton(minPin[_number]);
	_max = new PushButton(maxPin[_number]);
	_onPress = 0;
	_onRelease = 0;
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

void EndStop::onPress(void (*callback)(EndStop &, StopType, PushButton &)) {
	 _onPress = callback;
	 _min->onPress(&_onPressHandler, this);
	 _max->onPress(&_onPressHandler, this);
}

void EndStop::onRelease(void (*callback)(EndStop &, StopType, PushButton &)) {
	_onRelease = callback;
	_min->onRelease(&_onReleaseHandler, this);
	_max->onRelease(&_onReleaseHandler, this);
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

}
