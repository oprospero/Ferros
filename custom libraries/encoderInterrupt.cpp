
#include "encoder.h"
#include "pindef.h"

Encoder::Encoder() :
    leftTrigger(false),
    rightTrigger(false)
{
    pinMode(PIN_ENCODER_1, INPUT);
    pinMode(PIN_ENCODER_2, INPUT);
}

void Encoder::begin()
{
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_1), ISR_getLeftEncoderTime, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_2), ISR_getRightEncoderTime, RISING);
}

float Encoder::getLeftSpeed()
{
    unsigned long currentTime = micros();
    unsigned long diff = currentTime - lastTimeLeftEncoder;
    if ()
    return 1.0 / diffLeft;
}

float Encoder::gethRightSpeed()
{
    return 1.0 / diffRight;
}

void Encoder::ISR_getLeftEncoderTime()
{
    unsigned long currentTime = micros();
    diffLeft = currentTime - lastTimeLeftEncoder;
    lastTimeLeftEncoder = currentTime;
}

void Encoder::ISR_getRightEncoderTime()
{
    unsigned long currentTime = micros();
    diffRight = currentTime - lastTimeRightEncoder;
    lastTimeRightEncoder = currentTime
}