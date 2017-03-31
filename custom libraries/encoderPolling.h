
#ifndef ENCODER_H
#define ENCODER_H

#define SPEED_TIMEOUT 100000

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


}

#endif //ENCODER_H
