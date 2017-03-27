
#include "encoderInterrupt.h"
#include "pindef.h"

Encoder::Encoder() :
    leftTrigger(false),
    rightTrigger(false),
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
        speed = 1.0 / diff;
        lastTimeLeft = currentTime;
        leftTrigger = false;
    }
    else if (diff < SPEED_TIMEOUT)
    {
        speed = speed / 2.0;
    }
    else
    {
        speed = 0;
    }
    
    return speed;
}

float Encoder::getRightSpeed()
{
    unsigned long currentTime = micros();
    unsigned long diff = currentTime - lastTimeRight;
    if (rightTrigger)
    {
        speed = 1.0 / diff;
        lastTimeRight = currentTime;
        rightTrigger = false;
    }
    else if (diff < SPEED_TIMEOUT)
    {
        speed = speed / 2.0;
    }
    else
    {
        speed = 0;
    }
    
    return speed;
}

void Encoder::ISR_getLeftEncoderTime()
{
    leftTrigger = true;
}

void Encoder::ISR_getRightEncoderTime()
{
    rightTrigger = true;
}