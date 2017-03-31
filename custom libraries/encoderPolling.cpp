
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
        lastTimeLeft = currentTime;
				leftSpeed = 100000.0 / (float) diffLeft;

    }
    else if (leftPin == LOW && leftPinLast != LOW)
    {
        leftPinLast = LOW;
    }
		if (diffLeft > SPEED_TIMEOUT)
		{
			leftSpeed = 0;
		}

    unsigned long diffRight = currentTime - lastTimeRight;

    if (rightPin == HIGH && rightPinLast != HIGH)
    {
        rightPinLast = HIGH;
        lastTimeRight = currentTime;
				rightSpeed = 100000.0 / (float) diffRight;

    }
    else if (rightPin == LOW && rightPinLast != LOW)
    {
        rightPinLast = LOW;
    }
		if (diffRight > SPEED_TIMEOUT)
		{
			rightSpeed = 0;
		}

}

float Encoder::getLeftSpeed()
{
	return leftSpeed;
}

float Encoder::gethRightSpeed()
{
	return rightSpeed;
}
