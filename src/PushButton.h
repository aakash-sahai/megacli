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

  static const byte maxDebounceQty = 5;
  static const byte defaultPin =	2;
  static const int checkInterval = 5000;  // Period in microseconds to check for status

	PushButton();
	PushButton(byte aPin);    // Create a push button bound to aPin
  virtual ~PushButton();

  void onPress(void (*callback)(PushButton &)) { _onPress= callback; }
  void onClick(void (*callback)(PushButton &)) { _onClick = callback; }

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
  void (*_onPress)(PushButton &);
  void (*_onClick)(PushButton &);
  byte	_pin;
  State _state;
  int _clickQty;
  int _debounceQty;
  Task *_task;

  static void _run(void);
  static PushButton & self(void);
};

#endif /* PUSHBUTTON_H_ */
