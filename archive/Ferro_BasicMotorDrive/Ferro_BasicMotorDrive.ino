
#define PIN_MOTOR1_IN1 4
#define PIN_MOTOR1_IN2 5

#define PIN_MOTOR2_IN1 7
#define PIN_MOTOR2_IN2 8

#define PIN_MOTOR1_SPD 6
#define PIN_MOTOR2_SPD 9

#define PIN_MOTOR_ENB 13

#define PIN_ENCODER_1 2
#define PIN_ENCODER_2 3


void motorFullSpeed(int speed)
{
  analogWrite(PIN_MOTOR1_SPD, speed);
  analogWrite(PIN_MOTOR2_SPD, speed);
}

void motorStop()
{
  digitalWrite(PIN_MOTOR1_SPD, LOW);
  digitalWrite(PIN_MOTOR2_SPD, LOW);
}

void motorForward(int speed)
{
  digitalWrite(PIN_MOTOR1_IN1, HIGH);
  digitalWrite(PIN_MOTOR1_IN2, LOW);
  digitalWrite(PIN_MOTOR2_IN1, HIGH);
  digitalWrite(PIN_MOTOR2_IN2, LOW);
  motorFullSpeed(speed);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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
  if (Serial.available())
  {
    int num = Serial.parseInt();
    
    motorForward(num);
  }
//  delay(1000);
//  motorForward();
//  delay(3000);
//  motorStop();
}
