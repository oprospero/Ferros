
#include "encoderInterrupt.h"
#include "pindef.h"
#include <arduino.h>

volatile bool leftTrigger;
volatile bool rightTrigger;

Encoder::Encoder() :
    lastTimeLeft(0),
    lastTimeRight(0),
    leftSpeed(0),
    rightSpeed(0)
{
}

void Encoder::begin()
{
    pinMode(PIN_ENCODER_1, INPUT);
    pinMode(PIN_ENCODER_2, INPUT);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_1), ISR_getLeftEncoderTime, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_2), ISR_getRightEncoderTime, RISING);
}

float Encoder::getLeftSpeed()
{
    unsigned long currentTime = micros();
    unsigned long diff = currentTime - lastTimeLeft;
    if (leftTrigger)
    {
        leftSpeed = 1.0 / diff;
        lastTimeLeft = currentTime;
        leftTrigger = false;
    }
    else if (diff < SPEED_TIMEOUT)
    {
        leftSpeed = leftSpeed / 2.0;
    }
    else
    {
        leftSpeed = 0;
    }

    return leftSpeed;
}

float Encoder::getRightSpeed()
{
    unsigned long currentTime = micros();
    unsigned long diff = currentTime - lastTimeRight;
    if (rightTrigger)
    {
        rightSpeed = 1.0 / diff;
        lastTimeRight = currentTime;
        rightTrigger = false;
    }
    else if (diff < SPEED_TIMEOUT)
    {
        rightSpeed = rightSpeed / 2.0;
    }
    else
    {
        rightSpeed = 0;
    }

    return rightSpeed;
}

void ISR_getLeftEncoderTime()
{
    leftTrigger = true;
}

void ISR_getRightEncoderTime()
{
    rightTrigger = true;
}
