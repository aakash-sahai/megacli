/*
 * PushButton.cpp
 *
 *  Created on: Aug-11-2018
 *      Author: Aakash Sahai
 */

#include "PushButton.h"

namespace mksgen {

PushButton::PushButton(byte aPin) {
	_pin = aPin;
  _onPress = 0;
  _onRelease = 0;
}

PushButton::~PushButton() {
}

void PushButton::reset(void) {
  _clickQty = 0;
  _debounceQty = 0;
  _state = RELEASED;
}

void PushButton::enable(void) {
  _task->enable();
}

void PushButton::disable(void) {
  _task->disable();
  reset();
}

void PushButton::begin(Scheduler &runner) {
  reset();
	pinMode(_pin, INPUT_PULLUP);
  _task = new Task(checkInterval, TASK_FOREVER, _run, &runner);
  _task->setLtsPointer(this);
  _task->enable();
}

PushButton & PushButton::self(void)
{
  Scheduler &runner = Scheduler::currentScheduler();
  Task &task = runner.currentTask();
  PushButton *pb = (PushButton *)(task.getLtsPointer());
  return *pb;
}

void PushButton::_run(void) {
  PushButton &pb = self();
  int state = digitalRead(pb._pin);
  State last = pb._state;
  switch (pb._state) {
    case RELEASED:
      if (state == LOW) {
        pb._debounceQty = 0;
        pb._state = PRESSING;
      }
      break;
    case PRESSING:
      if (state == LOW) {
        if (++pb._debounceQty > pb.maxDebounceQty) {
          pb._state = PRESSED;
          pb._debounceQty = 0;
          if (pb._onPress) {
            pb._onPress(pb, pb._onPressCtx);
          }
        }
      } else {
        pb._debounceQty = 0;
      }
      break;
    case PRESSED:
      if (state == HIGH) {
        pb._debounceQty = 0;
        pb._state = RELEASING;
      }
      break;
    case RELEASING:
      if (state == HIGH) {
        if (++pb._debounceQty > pb.maxDebounceQty) {
          pb._state = RELEASED;
          pb._clickQty++;
          pb._debounceQty = 0;
          if (pb._onRelease) {
            pb._onRelease(pb, pb._onReleaseCtx);
          }
        }
      } else {
        pb._debounceQty = 0;
      }
      break;
  }
  if (pb._state != last) {
    DBG_PRINT(F("PB Level: "));
    DBG_PRINT(state);
    DBG_PRINT(F(" State: "));
    DBG_PRINTLN(pb._state);
  }
}

void PushButton::exec(char *args[], char **result) {
	*result = (char *)"do ok";
	if (strcmp(args[0], "reset") == 0) {
		reset();
	} else if (strcmp(args[0], "enable") == 0) {
		enable();
	} else if (strcmp(args[0], "disable") == 0) {
		disable();
	} else {
		*result = (char *)"do failed: no such command";
	}
}

void PushButton::get(char *args[], char **result) {
	*result = 0;
	if (strcmp(args[0], "state") == 0) {
		Serial.println(_state);
	} else if (strcmp(args[0], "clicks") == 0) {
		Serial.println(_clickQty);
	} else if (strcmp(args[0], "pin") == 0) {
		Serial.println(_pin);
	} else {
		Serial.println("get failed: no such attribute");
	}
}

void PushButton::set(char *args[], char **result) {
	*result = (char *)"set ok";
}


/*
 * create <name> as pushbutton <pin>
 */
Runnable *PushButton::create(char *args[]) {
	int pin = atoi(args[0]);
	PushButton *obj = new PushButton(pin);
	return obj;
}

}
