#include <PID_v1.h>
//#include "encoderInterrupt.h"
#include "encoderPolling.h"
#include "motor.h"


unsigned int throttle;
int steeringTrim;
bool speedup;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp = 2, Ki = 0, Kd = 0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

Encoder encoder;
Motor motor;

unsigned long lastTime = 0;

void setup()
{

  throttle = 50;
  // Po
  steeringTrim = -1.7;
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
  myPID.SetOutputLimits(-255.0,255.0);
  Serial.println("Ready Player One");
}

void loop()
{
  encoder.poll();
  float lspd = encoder.getLeftSpeed();
  float rspd = encoder.getRightSpeed();
  if ((lspd == 0 && rspd > 0) ||
    (lspd > 0 && rspd == 0)
  )
  {
    Input = (lspd - rspd) * 2;
  }
  Input = lspd - rspd;
  myPID.Compute();

  if (throttle < 100)
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

  if (Serial.available())
  {
    int num = Serial.parseInt();
    if (num < 1000)
      throttle = (num);
    else if ( num >= 1000)
    {
//      Setpoint = num / 1000;
//      Kp = num / 1000;
//      myPID.SetTunings(Kp, Ki, Kd);
    }
  }
  if(elapsedTime > 200)
  {
//    Serial.print("T: "); Serial.println(throttle);
//    Serial.print("lspd: "); Serial.println(lspd);
//  Serial.print("rspd: "); Serial.println(rspd);
  Serial.print("I: "); Serial.println(Input);
  Serial.print("O: "); Serial.println(Output);
    if (speedup) throttle += 10;
//    else throttle -= 15;
    // if (throttle > 300) speedup = false;
    if (throttle > 200) throttle = 200;
    if (throttle < 0) speedup = true;
    lastTime = currentTime;
  }

}
