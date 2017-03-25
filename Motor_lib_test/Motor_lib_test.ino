#include "motor.h"

Motor motor;

void setup() {
  // put your setup code here, to run once:
  motor.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  motor.leftForward(255);
  motor.rightForward(255);
  delay(3000);
  motor.leftBackward(200);
  motor.rightBackward(200);
}
