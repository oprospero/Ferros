#include <PID_v1.h>
#include "encoderPolling.h"
#include "motor.h"
#include "ranger.h"

#define STEER_AWAY_WALL 5;
#define STEER_TO_WALL 1;

#define TRAVEL_FEETS 40
#define STEERINGTRIM -4.5

#define THROTTLE_START 140
#define THROTTLE_MAX 255
#define THROTTLE_STEP 5
#define THROTTLE_STEP_TIME 200

#define INCH_COUNT_CONVERSION 20.0/7.5
#define DEGREE_COUNT_CONVERSION 20.0/160.0

#define SCAN_RANGE 75
#define SCAN_STEPS 8
#define SCAN_POINTS (SCAN_RANGE/SCAN_STEPS)+1 //Must be an odd number

#define DEPTH_THRESHOLD 200
#define RANGE_OK_GRAB 60
#define RANGE_TOO_CLOSE 40
#define RANGE_MAX 300
#define RANGE_OBJ_DIFF 50

#define RANGE_INCH_CONVERSION 1.0/50.0
#define INCH_COUNT_CONVERSION 20.0/7.5

int phase = 0;
int steeringTrim;
double Kp = 2.4, Ki = 0, Kd = 0;
double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
int targetDist;

Encoder encoder;
Motor motor;
Ranger range;


float scan()
{
  int preDist = 8000;
  int zeroOffset = 0;
  bool wallFound = false;
  preDist = range.getDist();
  Serial.println("Scanning Left");
  for (int i = 0; i < SCAN_POINTS; i++)
  {
    turn(-SCAN_STEPS, true);
    zeroOffset -= SCAN_STEPS;
    delay(300);
    int dist = range.getDist();

    if (dist < preDist - DEPTH_THRESHOLD)
    {
      preDist = dist;
      break;
    }
  }
  if (wallFound)
  {
    float dratio = 150.0/preDist;
    float degree = asin(dratio);
  
    if (degree > 45) degree = 45;
  
    turn(degree, false);
  
    float distInch = preDist / INCH_COUNT_CONVERSION;
    return distInch;
  }
  return preDist;
}

float moveForward(float inches, bool align)
{
  encoder.resetCount();
  Setpoint = STEERINGTRIM;
  int throttle = THROTTLE_START;
  int moved = 0;
  float inchesToCount = (INCH_COUNT_CONVERSION); // 20 counts / correction
  int distance = (int)(inchesToCount * inches);
  unsigned long lastTime = micros();
   
  while (moved < distance)
  {
    
    encoder.poll();
    float lspd = encoder.getLeftSpeed();
    float rspd = encoder.getRightSpeed(); // read this side

    Input = lspd - rspd;
    if ( 
      (lspd == 0 && rspd > 0) ||
      (lspd > 0 && rspd == 0)
    )
    {
      Input = Input * 4;
    }
    myPID.Compute();

    if (throttle < 0)
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

    moved = (encoder.getRightCount() + encoder.getLeftCount())/2;

    if (elapsedTime > THROTTLE_STEP_TIME)
    {
      throttle += THROTTLE_STEP;
      if (throttle > THROTTLE_MAX) throttle = THROTTLE_MAX;
      lastTime = currentTime;
    }

    if (align)
    {
      int wallProxy = range.getProxy();
      if (wallProxy)
      {
        Setpoint += STEER_AWAY_WALL;
      }
      else
      {
        Setpoint -= STEER_TO_WALL;
      }
    }
  }
  motor.stop();
  return moved / INCH_COUNT_CONVERSION;
}



void setup() {
  Serial.begin(115200);
  steeringTrim = STEERINGTRIM;
  Setpoint = steeringTrim;
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(10);
  myPID.SetOutputLimits(-255.0, 255.0);
  encoder.begin();
  motor.begin();
  range.begin();
  delay(1000);
}



float turn(float degree, bool align)
{
  bool clockwise = true;
  int trys = 0;
  if (degree < 0)
  {
    clockwise = false;
    degree = abs(degree);
  }
   encoder.resetCount();
   int rotation = 140;
   int avg_moved = 0;
   float degreeToCount = DEGREE_COUNT_CONVERSION; // 20 counts / correction
   int turnCount = (int)(degreeToCount * degree);
   Serial.print("Count: "); Serial.println(turnCount);
   Setpoint = 0;

   unsigned long lastTime = micros();
   
   while (avg_moved < turnCount)
  {
    
    encoder.poll();
    float lspd = encoder.getLeftSpeed();
    float rspd = encoder.getRightSpeed(); // read this side

    Input = lspd - rspd;
    if ( 
      (lspd == 0 && rspd > 0) ||
      (lspd > 0 && rspd == 0)
    )
    {
      Input = Input * 4;
    }
    
    myPID.Compute();

    if (rotation < THROTTLE_START)
    {
      motor.left(0);
      motor.right(0);
    }
    else if (clockwise)
    {
      motor.left(rotation - Output);
      motor.right(-(rotation + Output));
    }
    else
    {
      motor.left(-(rotation - Output));
      motor.right((rotation + Output));
    }

    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - lastTime;

    avg_moved = (encoder.getRightCount() + encoder.getLeftCount())/2;

    if (elapsedTime > THROTTLE_STEP_TIME)
    {
      rotation += THROTTLE_STEP;
      if (rotation > THROTTLE_MAX) rotation = THROTTLE_MAX;
      lastTime = currentTime;
    }
    
    if (align)
    {
      int wallProxy = range.getProxy();
      if (wallProxy == 1)
      {
        moveForward(3, false);
        wallProxy = range.getProxy();
        if (wallProxy == 1)
          break;
      }
    }
  }
  motor.stop();

  return avg_moved / degreeToCount;
}

#if 0

void loop() {
  float feets = 7;
  float inches = feets * 12;
  moveForward(inches, true);
  turn(-90.0, true);
  
  feets = 3;
  inches = feets * 12;
  moveForward(inches, true);
  turn(-90.0, true);
  
  feets = 7;
  inches = feets * 12;
  moveForward(inches, true);
}

#else
void loop() {
  float feets = 5;
  float inches = feets * 12;
  moveForward(inches, true);
  int dist = scan();

  while (dist < 3000)
  {
    inches = dist + 6;
    moveForward(inches, true);
    dist = scan();
  }
  
  feets = 3;
  inches = feets * 12;
  moveForward(inches, true);
  dist = scan();
  
  while (dist < 3000)
  {
    inches = dist + 6;
    moveForward(inches, true);
    dist = scan();
  }
  
  feets = 8;
  inches = feets * 12;
  moveForward(inches, true);
}
#endif
