/*
 * Command.h
 *
 *  Created on: Aug-22-2018
 *      Author: Aakash Sahai
 */

#include "mkscommon.h"

#ifndef CLI_H_
#define CLI_H_

namespace mksgen {

static const byte MAX_ARGS = 10;
static const byte CMD_BUF_SIZE = 100;

class CLI {

public:

  struct Command {
    char *cmd;
    byte nargs;
    char *args[MAX_ARGS];
  };

  virtual ~CLI();
  static void begin(Scheduler &runner);
  static void addModule(char * module, char * (*exec)(void *obj, Command cmd));

private:

  struct Registry {
    char *name;
    char *(*exec)(void *obj, Command cmd);
  };

  struct Object {
    char *name;
    void *obj;
  };

  CLI();
  static Registry _registry[10];
  static Object _objects[10];
  static Command _cmd;
  static char _buf[CMD_BUF_SIZE+1];
  static char *_bp;
  static int _buflen;
  static Task *_task;
  static void _run(void);
  static void _parse(void);
  static void _execute(void);
};
}

#endif /* CLI_H_ */
