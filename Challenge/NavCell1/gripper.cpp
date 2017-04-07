
#include "pindef.h"
#include "gripper.h"
#include <Servo.h>


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
    sLift.write(pos);
}

void Gripper::setClaw(int pos)
{
    sClaw.write(pos);
}

void Gripper::reset()
{
    setLift(0);
    setClaw(100);
}
