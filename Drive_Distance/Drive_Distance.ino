#include <PID_v1.h>
//#include "encoderInterrupt.h"
#include "encoderPolling.h"
#include "motor.h"


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
void turn(float degree)
{
   encoder.resetCount();
   int rotation = 140;
   int avg_moved = 0;
   float degreeToCount = (20.0/160.0); // 20 counts / correction
   int turnCount = (int)(degreeToCount * degree);
   Setpoint = 0;
   Serial.print("TurnCount: "); Serial.println(turnCount);
   while (avg_moved < turnCount)
  {

    encoder.poll();
    float lspd = encoder.getLeftSpeed();
    float rspd = encoder.getRightSpeed(); // read this side

    Input = lspd - rspd;
    myPID.Compute();

    if (rotation < 160)
    {
      motor.left(0);
      motor.right(0);
    }
    else
    {
      motor.left(rotation - Output);
      motor.right(-(rotation + Output));
    }

    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - lastTime;

    avg_moved = (encoder.getRightCount() + encoder.getLeftCount())/2;

    if (elapsedTime > 200)
    {
      Serial.println(avg_moved);
      if (speedup) rotation += 5;
      //    else throttle -= 15;
      if (rotation > 200) rotation = 200;
      lastTime = currentTime;
    }
  }
  motor.stop();
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
   int throttle = 140;
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
      motor.left(0);
      motor.right(0);
    }
    else
    {
      motor.left(throttle - Output);
      motor.right(throttle + Output);
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
//      moveForward(newDistance);
        turn(newDistance);
    } // this is now how many inches to move
  }
}
