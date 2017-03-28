
#include "sonar.h"
#include "pindef.h"


Sonar::Sonar() : hcsr04(PIN_SONAR_TRIG, PIN_SONAR_ECHO)
{

}

Sonar::~Sonar()
{

}

void Sonar::begin()
{
	
}