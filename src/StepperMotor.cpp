/*
 * StepperMotor.cpp
 *
 *  Created on: Aug-11-2018
 *      Author: Aakash Sahai
 */

#include "StepperMotor.h"

namespace mksgen {

const StepperMotor::StepperPins StepperMotor::pins[] = {
	{ X_STEP_PIN, X_ENABLE_PIN, X_DIR_PIN, X_CS_PIN },
	{ Y_STEP_PIN, Y_ENABLE_PIN, Y_DIR_PIN, Y_CS_PIN },
	{ Z_STEP_PIN, Z_ENABLE_PIN, Z_DIR_PIN, Z_CS_PIN },
	{ E0_STEP_PIN, E0_ENABLE_PIN, E0_DIR_PIN, E0_CS_PIN },
	{ E1_STEP_PIN, E1_ENABLE_PIN, E1_DIR_PIN, E1_CS_PIN },
};

StepperMotor::StepperMotor(byte number) {
	_number = number - 1;
	if (number >=1 && number <= 3) {
		_endStop = new EndStop(number);
	} else {
		_endStop = 0;
	}
}

StepperMotor::StepperMotor(byte number,	short stepsPerRev, short microsteps, short rpm) {
	_rpm = rpm;
	_microsteps = microsteps;
	_stepsPerRev = stepsPerRev;

	_number = number - 1;
	if (number >=1 && number <= 3) {
		_endStop = new EndStop(number);
	} else {
		_endStop = 0;
	}
}

StepperMotor::~StepperMotor() {
}

void StepperMotor::enable(void) {
	digitalWrite(pins[_number].enable, LOW);
	_task->enable();
}

void StepperMotor::disable(void) {
	digitalWrite(pins[_number].enable, HIGH);
  _task->disable();
}

void StepperMotor::begin(Scheduler &runner) {
  _task = new Task(TASK_IMMEDIATE, TASK_FOREVER, _run, &runner);
  _task->setLtsPointer(this);
	if (_endStop) {
		_endStop->begin(runner);
	}
	pinMode(pins[_number].dir, OUTPUT);
	digitalWrite(pins[_number].dir, HIGH);
	pinMode(pins[_number].step, OUTPUT);
	digitalWrite(pins[_number].step, LOW);
	pinMode(pins[_number].enable, OUTPUT);
	digitalWrite(pins[_number].enable, HIGH);
}

StepperMotor & StepperMotor::self(void)
{
  Scheduler &runner = Scheduler::currentScheduler();
  Task &task = runner.currentTask();
  StepperMotor *stepper = (StepperMotor *)(task.getLtsPointer());
  return *stepper;
}

void StepperMotor::rotate(long degrees) {
	rotate((double)degrees);
}

void StepperMotor::rotate(double degrees) {
	step(calcStepsForRotation(degrees));
}

void StepperMotor::step(long steps) {
	_dir = (steps >= 0) ? HIGH : LOW;
	_stepsRemaining = abs(steps);
	_stepDuration = (60*1000000L/_rpm/_stepsPerRev/_microsteps);
	_task->setInterval(_stepDuration);
	enable();
	oneStep();
}

void StepperMotor::oneStep() {
	_stepsRemaining--;
	digitalWrite(pins[_number].dir, _dir);
	digitalWrite(pins[_number].step, HIGH);
	delayMicroseconds(2);
	digitalWrite(pins[_number].step, LOW);
}

void StepperMotor::stop(void) {
	_stepsRemaining = 0;
	disable();
}

void StepperMotor::_run(void) {
  StepperMotor &stepper = self();
	if (  (stepper._stepsRemaining <= 0) ||
				(stepper._dir == HIGH && stepper._endStop->minButton().pressed()) ||
				(stepper._dir == LOW  && stepper._endStop->maxButton().pressed())  ) {
		stepper.stop();
		return;
	}
	stepper.oneStep();
}
}
