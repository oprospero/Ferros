
#ifndef SONAR_H
#define SONAR_H

class Sonar
{
	ST_HW_HC_SR04 hcsr04;
	Sonar();
	~Sonar();
	void begin();
	int getDistance();
}


#endif //SONAR_H