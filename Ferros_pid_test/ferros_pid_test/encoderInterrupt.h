
#ifndef ENCODER_H
#define ENCODER_H

#define SPEED_TIMEOUT 50000

void ISR_getLeftEncoderTime();
void ISR_getRightEncoderTime();

class Encoder
{
public:
	unsigned long lastTimeLeft;
	unsigned long lastTimeRight;
	float leftSpeed;
	float rightSpeed;

	Encoder();
	void begin();

    void pollSpeed();

	float getLeftSpeed();
	float getRightSpeed();

};

#endif //ENCODER_H
