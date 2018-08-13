
#include <stddef.h>
#include <inttypes.h>
#include <math.h>
#include <Arduino.h>
#include <Servo.h>
#include <BasicStepperDriver.h>
#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_MICRO_RES
#define _TASK_LTS_POINTER
#define _TASK_PRIORITY
#include <TaskSchedulerDeclarations.h>

#ifndef MKS_COMMON_H
#define MKS_COMMON_H

#define	RAD2DEG(_r)	(_r * RAD_TO_DEG)
#define	DEG2RAD(_d)	(_d * DEG_TO_RAD)

#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG
#define DBG_PRINT(x)	Serial.print(x)
#define DBG_PRINTLN(x)	Serial.println(x)
#else
#define DBG_PRINT(x)
#define DBG_PRINTLN(x)
#endif

#endif // MKS_COMMON_H
