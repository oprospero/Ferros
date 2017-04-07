


#include "ranger.h"
#include "pindef.h"
#include <Wire.h>
#include <VL53L0X.h>
#include <Arduino.h>


// Uncomment this line to use long range mode. This
// increases the sensitivity of the sensor and extends its
// potential range, but increases the likelihood of getting
// an inaccurate reading because of reflections from objects
// other than the intended target. It works best in dark
// conditions.

#define LONG_RANGE


// Uncomment ONE of these two lines to get
// - higher speed at the cost of lower accuracy OR
// - higher accuracy at the cost of lower speed

//#define HIGH_SPEED
#define HIGH_ACCURACY

Ranger::Ranger()
{

}

Ranger::~Ranger()
{

}

void Ranger::begin()
{

  pinMode(PIN_PROXIMITY, INPUT);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);

  // lower the return signal rate limit (default is 0.25 MCPS)
  // Signal strength threshold.
  // Lower values will increase range and wider view
  // Higher values will decrease range with narrow view
  sensor.setSignalRateLimit(0.6);
#if defined LONG_RANGE
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(100000);
#endif
}

int Ranger::getDist()
{
  int result;
  result = sensor.readRangeSingleMillimeters();
  return result;
}

int Ranger::getProxy()
{
  return digitalRead(PIN_PROXIMITY);
}
