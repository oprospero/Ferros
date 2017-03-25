
#ifndef ENCODER_H
#define ENCODER_H


class Encoder
{
	volatile bool leftTrigger;
	volatile bool rightTrigger;


	Encoder();
	void begin();
	float getLeftSpeed();
	float getRightSpeed();

    void pollSpeed();

	ISR_getLeftEncoderTime();
	ISR_getRightEncoderTime();
}

#endif //ENCODER_H