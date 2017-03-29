
#include "motor.h"
#include "pindef.h"

Motor::Motor()
{
  pinMode(PIN_MOTOR_ENB, OUTPUT);
  disable();
  pinMode(PIN_MOTOR1_IN1, OUTPUT);
  pinMode(PIN_MOTOR1_IN2, OUTPUT);
  pinMode(PIN_MOTOR2_IN1, OUTPUT);
  pinMode(PIN_MOTOR2_IN2, OUTPUT);
  pinMode(PIN_MOTOR1_SPD, OUTPUT);
  pinMode(PIN_MOTOR2_SPD, OUTPUT);
}

void Motor::begin()
{
  stop();
  enable();
}

void Motor::disable()
{
  digitalWrite(PIN_MOTOR_ENB, LOW);
}

void Motor::enable()
{
  digitalWrite(PIN_MOTOR_ENB, HIGH);
}

void Motor::stop()
{
  digitalWrite(PIN_MOTOR1_SPD, LOW);
  digitalWrite(PIN_MOTOR2_SPD, LOW);
}


void Motor::leftForward(int speed)
{
  digitalWrite(PIN_MOTOR1_IN1, HIGH);
  digitalWrite(PIN_MOTOR1_IN2, LOW);
  analogWrite(PIN_MOTOR1_SPD, speed);
}
void Motor::rightForward(int speed)
{
  digitalWrite(PIN_MOTOR2_IN1, HIGH);
  digitalWrite(PIN_MOTOR2_IN2, LOW);
  analogWrite(PIN_MOTOR2_SPD, speed);
}

void Motor::leftBackward(int speed)
{
  digitalWrite(PIN_MOTOR1_IN1, LOW);
  digitalWrite(PIN_MOTOR1_IN2, HIGH);
  analogWrite(PIN_MOTOR1_SPD, speed);
}
void Motor::rightBackward(int speed)
{
  digitalWrite(PIN_MOTOR2_IN1, LOW);
  digitalWrite(PIN_MOTOR2_IN2, HIGH);
  analogWrite(PIN_MOTOR2_SPD, speed);
}