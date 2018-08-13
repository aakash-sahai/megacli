#include <PushButton.h>
#include <TaskScheduler.h>

Scheduler runner;

PushButton pb1(7);
PushButton pb2(8);


void pressed(PushButton &pb) {
 Serial.print("Pressed PB on pin: ");
 Serial.println(pb.getPin());  
}


void clicked(PushButton &pb) {
 Serial.print("Clicked PB on pin: ");
 Serial.print(pb.getPin());
 Serial.print(" times: ");PushButton::
 Serial.println(pb1.clicks());
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println(F("Ready"));
  pb1.onPress(pressed);
  pb1.onClick(clicked);
  pb1.begin(runner);
  pb2.begin(runner);
}

void loop() {
  runner.execute();
}
