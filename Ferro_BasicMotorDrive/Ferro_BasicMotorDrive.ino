
#define PIN_MOTOR1_IN1 3
#define PIN_MOTOR1_IN2 4

#define PIN_MOTOR2_IN1 7
#define PIN_MOTOR2_IN2 8

#define PIN_MOTOR1_SPD 5
#define PIN_MOTOR2_SPD 6

#define PIN_MOTOR_ENB 13



void motorFullSpeed()
{
  digitalWrite(PIN_MOTOR1_SPD, HIGH);
  digitalWrite(PIN_MOTOR2_SPD, HIGH);  
}

void motorStop()
{
  digitalWrite(PIN_MOTOR1_SPD, LOW);
  digitalWrite(PIN_MOTOR2_SPD, LOW);
}

void motorForward()
{
  digitalWrite(PIN_MOTOR1_IN1, HIGH);
  digitalWrite(PIN_MOTOR1_IN2, LOW);
  digitalWrite(PIN_MOTOR2_IN1, HIGH);
  digitalWrite(PIN_MOTOR2_IN2, LOW);
  motorFullSpeed();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_MOTOR_ENB, OUTPUT);
  digitalWrite(PIN_MOTOR_ENB, HIGH);
  pinMode(PIN_MOTOR1_IN1, OUTPUT);
  pinMode(PIN_MOTOR1_IN2, OUTPUT);
  pinMode(PIN_MOTOR2_IN1, OUTPUT);
  pinMode(PIN_MOTOR2_IN2, OUTPUT);
  pinMode(PIN_MOTOR1_SPD, OUTPUT);
  pinMode(PIN_MOTOR2_SPD, OUTPUT);
  motorStop();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  motorForward();
  delay(3000);
  motorStop();
}
