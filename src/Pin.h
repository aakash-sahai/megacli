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
class Pin {

public:

  enum Type {
      DIGITAL = 0,
      ANALOG = 1
  };

	Pin(byte aPin, byte type, byte mode);
  virtual ~Pin();

	int get(void);
	void set(int value);
	byte getPin() { return _pin; }
  byte getType() { return _type; }
  byte getMode() { return _mode; }
  static void exec(void *obj, CLI::Command cmd, char *result);

private:
  byte	_pin;
  byte _type;
  byte _mode;
};
}

#endif /* PIN_H_ */
