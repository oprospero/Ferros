
#ifndef RANGER_H
#define RANGER_H

#include <Wire.h>
#include <VL53L0X.h>

class Ranger
{
public:
  VL53L0X sensor;

  Ranger();
  ~Ranger();

  void begin();

  int getDist();
};


#endif
