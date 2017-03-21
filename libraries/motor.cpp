
#include "motor.h"
#include "pindef.h"

Motor::Motor()
{
  pinMode(PIN_MOTOR_ENB, OUTPUT);
  digitalWrite(PIN_MOTOR_ENB, LOW);

  pinMode(PIN_MOTOR1_IN1, OUTPUT);
  pinMode(PIN_MOTOR1_IN2, OUTPUT);
  pinMode(PIN_MOTOR2_IN1, OUTPUT);
  pinMode(PIN_MOTOR2_IN2, OUTPUT);
  pinMode(PIN_MOTOR1_SPD, OUTPUT);
  pinMode(PIN_MOTOR2_SPD, OUTPUT);
  stop();
  
  digitalWrite(PIN_MOTOR_ENB, HIGH);
}

Motor::stop()
{
  digitalWrite(PIN_MOTOR1_SPD, LOW);
  digitalWrite(PIN_MOTOR2_SPD, LOW);
}


Motor::leftForward(int speed)
{
  digitalWrite(PIN_MOTOR1_IN1, HIGH);
  digitalWrite(PIN_MOTOR1_IN2, LOW);
  analogWrite(PIN_MOTOR1_SPD, speed);
}
Motor::rightForward(int speed)
{
  digitalWrite(PIN_MOTOR2_IN1, HIGH);
  digitalWrite(PIN_MOTOR2_IN2, LOW);
  analogWrite(PIN_MOTOR2_SPD, speed);
}

Motor::leftBackward(int speed)
{
  digitalWrite(PIN_MOTOR1_IN1, LOW);
  digitalWrite(PIN_MOTOR1_IN2, HIGH);
  analogWrite(PIN_MOTOR1_SPD, speed);
}
Motor::rightBackward(int speed)
{
  digitalWrite(PIN_MOTOR2_IN1, LOW);
  digitalWrite(PIN_MOTOR2_IN2, HIGH);
  analogWrite(PIN_MOTOR2_SPD, speed);
}