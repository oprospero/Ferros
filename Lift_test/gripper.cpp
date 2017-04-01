
#include "gripper.h"
#include <Arduino.h>
#include "pindef.h"

#define LIFT_MAX_VALUE 180
#define LIFT_MIN_VALUE 35
#define CLAW_MAX_VALUE 120
#define CLAW_MIN_VALUE 0


Gripper::Gripper()
{

}

Gripper::~Gripper()
{

}

void Gripper::begin()
{
    sLift.attach(PIN_GRIPPER_LIFT);
    sClaw.attach(PIN_GRIPPER_CLAW);
}

void Gripper::setLift(int pos)
{
  if (pos > LIFT_MAX_VALUE) pos = LIFT_MAX_VALUE;
  if (pos < LIFT_MIN_VALUE) pos = LIFT_MIN_VALUE;
  sLift.write(pos);
}

void Gripper::setClaw(int pos)
{
  if (pos > CLAW_MAX_VALUE) pos = CLAW_MAX_VALUE;
  if (pos < CLAW_MIN_VALUE) pos = CLAW_MIN_VALUE;
    sClaw.write(pos);
}

void Gripper::reset()
{
    setLift(0);
    setClaw(100);
}
