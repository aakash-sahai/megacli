#include <EndStop.h>
#include <TaskScheduler.h>

Scheduler runner;

EndStop stop(ENDSTOP_X);

void pressed(byte number, EndStop::StopType type, PushButton &pb) {
 char buf[80];
 sprintf(buf, "Pressed EndStop %d type %s on pin %d", number, (type == EndStop::StopType::MIN_STOP) ? "MIN" : "MAX", pb.getPin());
 Serial.println(buf);
}


void clicked(byte number, EndStop::StopType type, PushButton &pb) {
 char buf[80];
 sprintf(buf, "Released EndStop %d type %s on pin %d", number, (type == EndStop::StopType::MIN_STOP) ? "MIN" : "MAX", pb.getPin());
 Serial.println(buf);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println(F("Ready"));
  stop.onPress(pressed);
  stop.onClick(clicked);
  stop.begin(runner);
}

void loop() {
  runner.execute();
}
