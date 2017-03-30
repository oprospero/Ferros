#include <PID_v1.h>
#include "encoderInterrupt.h"
#include "motor.h"


unsigned int throttle;
int steeringTrim;
bool speedup;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp = 1, Ki = 0, Kd = 0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

Encoder encoder;
Motor motor;

unsigned long lastTime = 0;

void setup()
{

  throttle = 0;
  // Po
  steeringTrim = 100;
  speedup = true;
  encoder.begin();
  motor.begin();
  Serial.begin(115200);

  //initialize the variables we're linked to
  Input = 0;
  Setpoint = 0;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  Serial.println("Ready Player One");
}

void loop()
{
  delay(5);
  float lspd = encoder.getLeftSpeed();
  float rspd = encoder.getRightSpeed();
  Input = lspd - rspd + steeringTrim;
  myPID.Compute();
  motor.leftForward(throttle - Output);
  motor.rightForward(throttle + Output);

  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - lastTime;

  
  if (Serial.available())
  {
    int num = Serial.parseInt();
    throttle = (num);
  }
  if(elapsedTime > 200)
  {
    Serial.print("T: "); Serial.println(throttle);
    Serial.print("lspd: "); Serial.println(lspd);
//  Serial.print("rspd: "); Serial.println(rspd);
//  Serial.print("I: "); Serial.println(Input);
//  Serial.print("O: "); Serial.println(Output);
//    if (speedup) throttle += 10;
//    else throttle -= 15;
    if (throttle > 300) speedup = false;
    if (throttle < 0) speedup = true;
    lastTime = currentTime;
  }
  
}
