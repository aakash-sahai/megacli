/*
 * PushButton.h
 *
 *  Created on: Aug-12-2018
 *      Author: Aakash Sahai
 */

#include "mkscommon.h"

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

class PushButton {

public:

  enum State {
    RELEASED	= 0,
    PRESSING  = 1,
    PRESSED   = 2,
    RELEASING = 3
  };

	PushButton();
	PushButton(byte aPin);    // Create a push button bound to aPin
  virtual ~PushButton();

  void onPress(void (*callback)(PushButton &, void *), void *ctx) {
     _onPress = callback; _onPressCtx = ctx;
  }

  void onRelease(void (*callback)(PushButton &, void *), void *ctx) {
     _onRelease = callback; _onReleaseCtx = ctx;
   }

  void begin(Scheduler &runner);
  void reset(void);
  void enable(void);
  void disable(void);
	int  clicks() { return _clickQty; }
	void clearClicks() { _clickQty = 0; }
	bool pressed(void) { return _state == PRESSED; }
	bool clicked(void) { return _clickQty > 0; };
	byte getPin() { return _pin; }

private:

  static const byte maxDebounceQty = 5;
  static const byte defaultPin =	2;
  static const int checkInterval = 5000;  // Period in microseconds to check for status

  void (*_onPress)(PushButton &, void *);
  void (*_onRelease)(PushButton &, void *);
  void *_onPressCtx;
  void *_onReleaseCtx;
  byte	_pin;
  State _state;
  int _clickQty;
  int _debounceQty;
  Task *_task;

  static void _run(void);
  static PushButton & self(void);
};

#endif /* PUSHBUTTON_H_ */
