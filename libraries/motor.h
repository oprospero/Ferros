
#ifndef MOTOR_H
#define MOTOR_H


#endif //MOTOR_H

class Motor
{
public:
    // Motor(int a1, int a1, int aSpd, int b1, int b2, int bSpd, int enable);
    Motor();
    begin();
    enable();
    disable();
    leftForward(int speed);
    leftBackward(int speed);
    rightForward(int speed);
    rightBackward(int speed);
}