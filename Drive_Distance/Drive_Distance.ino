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
int distance; // target distance to move in counts
int moved; // number of counts moved
float targetDistance; //target distance in inches
float inchesToCount; // conversion factor from inches to count (e.g 2" = 100 counts)

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
  distance = 0; // target distance
  moved = 0; // encoder counts to track how far we moved
  inchesToCount = (6.0/20.0);

  //initialize the variables we're linked to
  Input = 0;
  Setpoint = steeringTrim;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(10);
  myPID.SetOutputLimits(-255.0,255.0);
  Serial.println("Ready Player One");
}

void moveForward()
{

}

void loop()
{
  if (Serial.available())
  {
    if(Serial.parseFloat() != targetDistance)
    {
      distance = (int)(targetDistance * inchesToCount);
      moved = 0;
      encoder.resetCount();
    } // this is now how many inches to move
  }
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


    if(elapsedTime > 200)
    {
  //    Serial.print("T: "); Serial.println(throttle);
  //    Serial.print("lspd: "); Serial.println(lspd);
  //  Serial.print("rspd: "); Serial.println(rspd);
    Serial.print("I: "); Serial.println(Input);
    Serial.print("O: "); Serial.println(Output);
      if (speedup) throttle += 5;
  //    else throttle -= 15;
      if (throttle > 300) speedup = false;
      if (throttle < 0) speedup = true;
      lastTime = currentTime;
    }

    moved += encoder.getLeftCount();

  }

}
