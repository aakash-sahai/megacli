
#include <stddef.h>
#include <inttypes.h>
#include <math.h>
#include <Arduino.h>
#include <Servo.h>
#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_MICRO_RES
#define _TASK_LTS_POINTER
#define _TASK_PRIORITY
#include <TaskSchedulerDeclarations.h>
#include "pin_mksgen14.h"

#ifndef MKS_COMMON_H
#define MKS_COMMON_H

#define	RAD2DEG(_r)	(_r * RAD_TO_DEG)
#define	DEG2RAD(_d)	(_d * DEG_TO_RAD)

#ifndef DEBUG
#define DEBUG 0
#endif

#if DEBUG
#define DBG_PRINT(x)	Serial.print(x)
#define DBG_PRINTLN(x)	Serial.println(x)
#else
#define DBG_PRINT(x)
#define DBG_PRINTLN(x)
#endif

namespace mksgen {

class Runnable {
public:
  virtual void begin(Scheduler &runner) = 0;
  virtual void get(char *args[], char **result) = 0;
  virtual void set(char *args[], char **result) = 0;
  virtual void exec(char *args[], char **result) = 0;
};

class MKS {
public:
  virtual ~MKS();
  static void init(void);

private:

  MKS();
};
}

#endif // MKS_COMMON_H
