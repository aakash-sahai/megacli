#include <CLI.h>
#include <TaskScheduler.h>

using namespace mksgen;

Scheduler runner;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
  }
  MKS::init();
  CLI::begin(runner);
}

void loop() {
  runner.execute();
}
