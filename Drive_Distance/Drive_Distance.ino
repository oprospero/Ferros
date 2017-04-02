#include <PID_v1.h>
//#include "encoderInterrupt.h"
#include "encoderPolling.h"
#include "motor.h"


unsigned int throttle;
int steeringTrim;
bool speedup;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Distance to drive
float targetDistance; //target distance in inches

//Specify the links and initial tuning parameters
double Kp = 2, Ki = 0, Kd = 0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

Encoder encoder;
Motor motor;

unsigned long lastTime = 0;

void setup()
{
  encoder.resetCount();
  throttle = 50;
  // Po
  steeringTrim = -1.5;
  speedup = true;
  encoder.begin();
  motor.begin();
  Serial.begin(115200);


  //initialize the variables we're linked to
  Input = 0;
  Setpoint = steeringTrim;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(10);
  myPID.SetOutputLimits(-255.0, 255.0);
  Serial.println("Ready Player One");
}

/*
function: moveForward

Parameters
inches (float): distance to move forward robot in inches

returns void

*/
void moveForward(float inches)
{
   encoder.resetCount();
   throttle = 140;
   int moved = 0;
   float inchesToCount = (20.0/7.5); // 20 counts / correction
   int distance = (int)(inchesToCount * inches);
   
   while (moved < distance)
  {

    encoder.poll();
    float lspd = encoder.getLeftSpeed();
    float rspd = encoder.getRightSpeed(); // read this side

    Input = lspd - rspd;
    myPID.Compute();

    if (throttle < 160)
    {
      motor.leftForward(0);
      motor.rightForward(0);
    }
    else
    {
      motor.leftForward(throttle - Output);
      motor.rightForward(throttle + Output);
    }

    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - lastTime;

    moved = encoder.getLeftCount();

    if (elapsedTime > 200)
    {
      if (speedup) throttle += 5;
      //    else throttle -= 15;
      if (throttle > 200) throttle = 200;
      lastTime = currentTime;
    }
  }
  motor.stop();
}

void loop()
{
  if (Serial.available())
  {
    float newDistance = Serial.parseFloat();
    Serial.print("new: "); Serial.println(newDistance);
    if (newDistance > 0.0f)
    {
      moveForward(newDistance);
    } // this is now how many inches to move
  }
}
