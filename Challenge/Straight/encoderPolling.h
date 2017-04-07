
#ifndef ENCODER_H
#define ENCODER_H


class Encoder
{
public:
	unsigned long lastTimeLeft;
	unsigned long lastTimeRight;
	float leftSpeed;
	float rightSpeed;
	bool leftPinLast;
	bool rightPinLast;
	int leftCount;
	int rightCount;

	Encoder();
	void begin();

	void poll();

	float getLeftSpeed();
	float getRightSpeed();
	int getLeftCount();
	int getRightCount();

	void resetCount();


};

#endif //ENCODER_H
