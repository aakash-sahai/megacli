/*
 * Pin.h
 *
 *  Created on: Aug-12-2018
 *      Author: Aakash Sahai
 */

#include "mkscommon.h"
#include "CLI.h"

#ifndef PIN_H_
#define PIN_H_

namespace mksgen {
class Pin  : public Runnable {

public:

  enum Type {
      DIGITAL = 0,
      ANALOG = 1
  };

	Pin(byte aPin, byte type, byte mode);
  virtual ~Pin();

  void begin(Scheduler &runner);
	int get(void);
	void set(int value);
	byte getPin() { return _pin; }
  byte getType() { return _type; }
  byte getMode() { return _mode; }

  static Runnable *create(char *args[]);
  void get(char *args[], char **result);
  void set(char *args[], char **result);
  void exec(char *args[], char **result);

private:
  byte	_pin;
  byte _type;
  byte _mode;
};
}

#endif /* PIN_H_ */
