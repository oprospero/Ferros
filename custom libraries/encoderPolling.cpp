
#include "encoderPolling.h"
#include "pindef.h"

Encoder::Encoder() :
	leftTrigger,
	rightTrigger,
  lastTimeLeft(0),
  lastTimeRight(0),
  diffLeft(0),
  diffRight(0)
{
}

void Encoder::begin()
{
    pinMode(PIN_ENCODER_1, INPUT);
    pinMode(PIN_ENCODER_2, INPUT);
}

void Encoder::pollSpeed()
{
    int leftPin = digitalRead(PIN_ENCODER_1);
    int rightPin = digitalRead(PIN_ENCODER_2);

    unsigned long currentTime = micros();
    unsigned long diffLeft = currentTime - lastTimeLeft;

    if (leftPin == HIGH && leftPinLast != HIGH)
    {
        leftPinLast = HIGH;
        lastTimeLowHigh = currentTime;
				leftSpeed = 100000.0 / (float) diffLeft;

    }
    else if (leftPin == LOW && leftPinLast != LOW)
    {
        leftPinLast = LOW;
        lastTimeHighLow = currentTime;
    }


    unsigned long diffRight = currentTime - lastTimeRight;
}

float Encoder::getLeftSpeed()
{
    int enc1 = digitalRead(PIN_ENCODER_1);
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
    leftTrigger = true;
}

void Encoder::ISR_getRightEncoderTime()
{
    rightTrigger = true;
}
