//
// Servos
//

#define SERVO1_PIN       11
#define SERVO2_PIN        6
#define SERVO3_PIN        5
#define SERVO4_PIN        4

//
// Limit Switches or EndStops, a pair each for X, Y and Z steppers.
//
#define X_MIN_PIN          3
#define X_MAX_PIN          2
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

//
// EndStops can be accessed as #1 through #6, or as aliases defined below
//
#define ENDSTOP_X_MIN   1
#define ENDSTOP_X_MAX   2
#define ENDSTOP_Y_MIN   3
#define ENDSTOP_Y_MAX   4
#define ENDSTOP_Z_MIN   5
#define ENDSTOP_Z_MAX   6

//
// Steppers
//
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_CS_PIN           53

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_CS_PIN           49

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_CS_PIN           40

#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      24
#define E0_CS_PIN          42

#define E1_STEP_PIN        36
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30
#define E1_CS_PIN          44

//
// Steppers can be accessed as #1 through #5, or as aliases defined below
//
#define STEPPER_X   1
#define STEPPER_Y   2
#define STEPPER_Z   3
#define STEPPER_E0  4
#define STEPPER_E1  5

//
// Analog Inputs / Thermal sensors
//
#define TEMP_1_PIN         13   // Analog Input
#define TEMP_2_PIN         15   // Analog Input
#define TEMP_3_PIN         14   // Analog Input

#define E0_THERMAL    TEMP_1_PIN
#define BED_THERMAL   TEMP_2_PIN
#define E1_THERMAL    TEMP_3_PIN

//
// MOSFET Outputs / Fan & Heaters
//
#define MOSFET_1_PIN  7
#define MOSFET_2_PIN  10
#define MOSFET_3_PIN  9
#define MOSFET_4_PIN  8

#define E1_MOSFET_PIN   MOSFET_1_PIN
#define E0_MOSFET_PIN   MOSFET_2_PIN
#define FAN_MOSFET_PIN  MOSFET_3_PIN
#define BED_MOSFET_PIN  MOSFET_4_PIN

//
// Defining some maximum quantities
//
#define MAX_SERVOS    4
#define MAX_STEPPERS  5
#define MAX_ENDSTOPS  6
#define MAX_MOSFET    4
#define MAX_THERMAL   3
