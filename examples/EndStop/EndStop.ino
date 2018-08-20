#include <EndStop.h>
#include <TaskScheduler.h>

using namespace mksgen;

Scheduler runner;

EndStop stop(ENDSTOP_X);

void pressed(EndStop &stop, EndStop::StopType type, PushButton &pb) {
 char buf[80];
 sprintf(buf, "Pressed EndStop type %s on pin %d", (type == EndStop::StopType::MIN_STOP) ? "MIN" : "MAX", pb.getPin());
 Serial.println(buf);
}


void released(EndStop &stop, EndStop::StopType type, PushButton &pb) {
 char buf[80];
 sprintf(buf, "Released EndStop type %s on pin %d", (type == EndStop::StopType::MIN_STOP) ? "MIN" : "MAX", pb.getPin());
 Serial.println(buf);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println(F("Ready"));
  stop.onPress(pressed);
  stop.onRelease(released);
  stop.begin(runner);
}

void loop() {
  runner.execute();
}
