#include <StepperMotor.h>
#include <TaskScheduler.h>

using namespace mksgen;

Scheduler runner;

StepperMotor stepper(2);
long deg = 360L * 1000;
short rpm = 1;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println(F("Ready"));
  stepper.begin(runner);
}

void loop() {
  runner.execute();
  if (!stepper.running()) {
    Serial.println(rpm);
    stepper.setRPM(rpm);
    stepper.rotate(deg);
    deg = -deg;
    rpm = rpm * 2;
    if (rpm > 2048) rpm = 1;
  }
}
