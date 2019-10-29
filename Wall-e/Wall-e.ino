#include <Servo.h>
Servo left;
Servo right;

void setup() {
  left.attach(9);
  right.attach(8);
}

void loop() {
  left.write(80);
  right.write(100);
}
