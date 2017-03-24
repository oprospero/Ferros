
#ifndef ENCODER_H
#define ENCODER_H


class Encoder
{
	unsigned long lastTimeLeftEncoder;
	unsigned long lastTimeRightEncoder;
	volatile unsigned long diffLeft;
	volatile unsigned long diffRight;

	Encoder();
	begin();
	getLeftSpeed();
	getRightSpeed();

	ISR_getLeftEncoderTime();
	ISR_getRightEncoderTime();
}

#endif //ENCODER_H