
#define PIN_MOTOR1_IN1 4
#define PIN_MOTOR1_IN2 12

#define PIN_MOTOR2_IN1 7
#define PIN_MOTOR2_IN2 8

#define PIN_MOTOR1_SPD 5
#define PIN_MOTOR2_SPD 6

#define PIN_MOTOR_ENB 13

#define PIN_ENCODER_1 2
#define PIN_ENCODER_2 3

#define SPEED_TIMEOUT 100000

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
  setSpeed(255);
}

void setSpeed(int speed)
{
  analogWrite(PIN_MOTOR1_SPD, speed);
  analogWrite(PIN_MOTOR2_SPD, speed);
}

unsigned long lastTimeLeft = 0;
unsigned long lastTimeRight = 0;
unsigned long currentTimeLeftEncoder = 0;
unsigned long currentTimeRightEncoder = 0;


volatile bool leftTrigger;
volatile bool rightTrigger;

float leftSpeed;
float rightSpeed;

void ISR_getLeftEncoderTime()
{
    leftTrigger = true;
}

void ISR_getRightEncoderTime()
{
    rightTrigger = true;
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
  pinMode(PIN_ENCODER_1, INPUT);
  pinMode(PIN_ENCODER_2, INPUT);
  motorStop();
  delay(1000);
  digitalWrite(PIN_MOTOR_ENB, HIGH);
  Serial.println("Ready Player One");
  motorForward();

  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_1), ISR_getLeftEncoderTime, RISING);
//  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_2), ISR_getRightEncoderTime, HIGH);
}

void loop() {
  
  unsigned long currentTime = micros();
  unsigned long diff = currentTime - lastTimeLeft;
  if (leftTrigger)
  {
      leftSpeed = 100000.0 / (float)diff;
      lastTimeLeft = currentTime;
      leftTrigger = false;
      Serial.println(diff);
  }
  else if (diff < SPEED_TIMEOUT)
  {
      // We can try to do some predictive logic here
      leftSpeed = leftSpeed;
  }
  else
  {
      leftSpeed = 0;
  }

  if (Serial.available())
  {
    int num = Serial.parseInt();

    setSpeed(num);
  }
}
