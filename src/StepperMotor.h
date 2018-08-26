/*
 * StepperMotor.h
 *
 *  Created on: Aug-12-2018
 *      Author: Aakash Sahai
 */

#include "mkscommon.h"
#include "EndStop.h"
#include "CLI.h"

#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_

namespace mksgen {

class StepperMotor {

public:

  typedef struct {
    byte step;
    byte enable;
    byte dir;
    byte cs;
  } StepperPins;

	StepperMotor(byte number);
  StepperMotor(byte number, short stepsPerRev, short microsteps, short rpm);
  virtual ~StepperMotor();

  void begin(Scheduler &runner);
  void enable(void);
  void disable(void);
  void rotate(int degrees) { rotate((long)degrees); }
	void rotate(long degrees);
  void rotate(double degrees);
	void step(long steps);
  void oneStep(void);
  void stop(void);
  bool running(void) { return (_stepsRemaining > 0); }
  void setRPM(short rpm) { /* if (rpm > 200) _rpm = 200; else */ _rpm = rpm; }
  short getRPM(void) { return _rpm; }
  void setStepsPerRev(short srv) { _stepsPerRev = srv; }
  short getStepsPerRev(void) { return _stepsPerRev; }
  void setMicrosteps(short ms) { _microsteps = ms; }
  short getMicrosteps(void) { return _microsteps; }
  static void exec(void *obj, CLI::Command cmd, char *result);

private:
  Task *_task;
  byte _number;
  EndStop *_endStop;
  byte _dir = HIGH;
  short _rpm = 200;
  short _microsteps = 32;
  short _stepsPerRev = 200;
  long _stepsRemaining = 0;
  long _stepDuration = 0;

  long calcStepsForRotation(double deg){
        return (long)(deg * _stepsPerRev * _microsteps / 360);
  }

  static const StepperPins pins[MAX_MKS_STEPPERS];
  static const int checkInterval = 5000;

  static void _run(void);
  static StepperMotor & self(void);
};
}

#endif /* STEPPER_MOTOR_H_ */
