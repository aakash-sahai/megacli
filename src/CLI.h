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
static const byte MAX_MODULES = 5;
static const byte MAX_OBJECTS = 50;
static const byte MAX_NAME_SIZE = 6;
static const byte MAX_MODULE_NAME_SIZE = 10;
static const byte CMD_BUF_SIZE = 100;

class CLI {

public:

  struct Command {
    char *cmd;
    byte nargs;
    char *args[MAX_ARGS];
  };

  typedef Runnable *(*CreateFn)(char *args[]);

  virtual ~CLI();
  static void begin(Scheduler &runner);
  static void addModule(const char *module, CreateFn create);


private:

  struct Registry {
    char name[MAX_MODULE_NAME_SIZE+1];
    CreateFn create;
  };

  struct Object {
    char name[MAX_NAME_SIZE+1];
    Runnable *obj;
  };

  CLI();
  static Registry _registry[MAX_MODULES];
  static Object _objects[MAX_OBJECTS];
  static Command _cmd;
  static int _objectQty;
  static int _moduleQty;
  static char _buf[CMD_BUF_SIZE+1];
  static char *_bp;
  static int _buflen;
  static Task *_task;
  static Scheduler *_sched;
  static void _run(void);
  static void _parse(void);
  static void _execute(void);
  static const char *_create(void);
  static Runnable *_findObject(const char *name);
};
}

#endif /* CLI_H_ */
