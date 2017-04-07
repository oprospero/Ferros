
#ifndef MOTOR_H
#define MOTOR_H

#include <arduino.h>

class Motor
{
public:
    // Motor(int a1, int a1, int aSpd, int b1, int b2, int bSpd, int enable);
    Motor();
    void begin();
    void enable();
    void disable();
    void stop();

    void leftForward(int speed);
    void leftBackward(int speed);
    void rightForward(int speed);
    void rightBackward(int speed);

    void left(int speed);
    void right(int speed);
};


#endif //MOTOR_H
