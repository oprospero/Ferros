
#ifndef GRIPPER_H
#define GRIPPER_H

#include <Servo.h>

class Gripper
{
    Servo sLift;
    Servo sClaw;
    Gripper();
    ~Gripper();

    void begin();

    void setLift(int );
    void setClaw(int );

    void reset();

};


#endif //GRIPPER_H
