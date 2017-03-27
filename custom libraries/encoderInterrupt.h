
#ifndef ENCODER_H
#define ENCODER_H

#define SPEED_TIMEOUT 50000

class Encoder
{
	volatile bool leftTrigger;
	volatile bool rightTrigger;
	unsigned long lastTimeLeft;
	unsigned long lastTimeRight;
	float leftSpeed;
	float rightSpeed;

	Encoder();
	void begin();

    void pollSpeed();

	float getLeftSpeed();
	float getRightSpeed();

	ISR_getLeftEncoderTime();
	ISR_getRightEncoderTime();
}

#endif //ENCODER_H