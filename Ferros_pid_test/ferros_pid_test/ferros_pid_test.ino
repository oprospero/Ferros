#include <PID_v1.h>
#include "encoderInterrupt.h"
#include "motor.h"

#define PIN_INPUT 0
#define PIN_OUTPUT 3

unsigned int throttle;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp = 2, Ki = 5, Kd = 1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

Encoder encoder;
Motor motor;

unsigned long lastTime = 0;

void setup()
{

  throttle = 0;
  encoder.begin();
  motor.begin();
  Serial.begin(115200);

  //initialize the variables we're linked to
  Input = 0;
  Setpoint = 0;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  Input = encoder.getLeftSpeed() - encoder.getRightSpeed();
  myPID.Compute();
  motor.leftForward(throttle + Output);
  motor.rightForward(throttle - Output);

  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - lastTime;
  
  if(elapsedTime > 1000)
  {
    throttle += 5;
    lastTime = currentTime;
  }
  
}
