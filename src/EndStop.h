/*
 * EndStop.h
 *
 *  Created on: Aug-12-2018
 *      Author: Aakash Sahai
 */

#include "mkscommon.h"
#include "PushButton.h"

#ifndef ENDSTOP_H_
#define ENDSTOP_H_

class EndStop {

public:

  enum StopType {
    MIN_STOP = 0,
    MAX_STOP = 1
  };

	EndStop(byte number);
  virtual ~EndStop();

  void begin(Scheduler &runner);
  PushButton &minButton(void) { return *_min; }
  PushButton &maxButton(void) { return *_max; }
  void onPress(void (*callback)(EndStop &, StopType, PushButton &)) { _onPress = callback; }
  void onRelease(void (*callback)(EndStop &, StopType, PushButton &)) { _onRelease = callback; }

private:

  void (*_onPress)(EndStop &stop, StopType type, PushButton &pb);
  void (*_onRelease)(EndStop &stop, StopType type, PushButton &pb);

  static void _onPressHandler(PushButton &pb, void *ctx);
  static void _onReleaseHandler(PushButton &pb, void *ctx);

  static const byte minPin[MAX_MKS_ENDSTOPS];
  static const byte maxPin[MAX_MKS_ENDSTOPS];

  PushButton *_min;
  PushButton *_max;
  byte _number = -1;

};

#endif /* ENDSTOP_H_ */
