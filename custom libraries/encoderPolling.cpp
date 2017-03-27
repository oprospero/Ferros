
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
    int enc1 = digitalRead(PIN_ENCODER_1);
    int enc2 = digitalRead(PIN_ENCODER_2);
 
    if (enc1 == HIGH && enc1Last != HIGH)
    {
        enc1Last = HIGH;
        unsigned long t = micros();
        unsigned long diff = t - lastTimeLowHigh;
        lastTimeLowHigh = t;
        
        Serial.print("Encoder 1: HIGH ");
        Serial.println(diff);
    }
    else if (enc1 == LOW && enc1Last != LOW)
    {
        enc1Last = LOW;
        unsigned long t = micros();
        unsigned long diff = t - lastTimeHighLow;
        lastTimeHighLow = t;
        Serial.print("Encoder 1: LOW ");
        Serial.println(diff);
    }
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
    leftTrigger = true;
}

void Encoder::ISR_getRightEncoderTime()
{
    rightTrigger = true;
}