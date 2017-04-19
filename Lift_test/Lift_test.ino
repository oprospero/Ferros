#include "gripper.h"
#include "ranger.h"

Gripper g;
Ranger r;
int pos;
bool climb;

bool targetLift;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  g.begin();
  r.begin();
  pos = 0;
  climb = true;
  targetLift = true;
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.println(pos);
  g.setLift(pos);
//  g.setClaw(pos);
  
  delay(200);
  int dist = r.getDist();
  Serial.println(dist);

  
  if (Serial.available())
  {
    int num = Serial.parseInt();
    pos = num;
  }

 
//  if (climb) pos += 10;
//  else pos -= 5;
//  
//  if (pos >= 180) climb = false;
//  else if (pos <= 0) climb = true;
}
