#include <PushButton.h>
#include <TaskScheduler.h>

using namespace mksgen;

Scheduler runner;

PushButton pb1(7);
PushButton pb2(8);


void pressed(PushButton &pb, void *ctx) {
 Serial.print("Pressed PB on pin: ");
 Serial.println(pb.getPin());
}


void released(PushButton &pb, void *ctx) {
 Serial.print("Released PB on pin: ");
 Serial.print(pb.getPin());
 Serial.print(" times: ");
 Serial.println(pb.clicks());
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println(F("Ready"));
  pb1.onPress(pressed, 0);
  pb1.onRelease(released, 0);
  pb1.begin(runner);
  pb2.begin(runner);
}

void loop() {
  runner.execute();
}
