
#define PIN_MOTOR1_IN1 4
#define PIN_MOTOR1_IN2 5

#define PIN_MOTOR2_IN1 7
#define PIN_MOTOR2_IN2 8

#define PIN_MOTOR1_SPD 6
#define PIN_MOTOR2_SPD 9

#define PIN_MOTOR_ENB 13

#define PIN_ENCODER_1 2
#define PIN_ENCODER_2 3


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

unsigned long lastTimeLeftEncoder = 0;
unsigned long lastTimeRightEncoder = 0;
volatile unsigned long currentTimeLeftEncoder = 0;
volatile unsigned long currentTimeRightEncoder = 0;

void ISR_getLeftEncoderTime() {
  currentTimeLeftEncoder = millis();
}

void ISR_getRightEncoderTime() {
  currentTimeRightEncoder = millis();
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
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_2), ISR_getRightEncoderTime, RISING);
}

void loop() {
  if (currentTimeLeftEncoder > lastTimeLeftEncoder)
  {
    unsigned long diff = currentTimeLeftEncoder - lastTimeLeftEncoder;
    Serial.print("L: ");
    Serial.println(diff);
    lastTimeLeftEncoder = currentTimeLeftEncoder;
  }
  
  if (currentTimeRightEncoder > lastTimeRightEncoder)
  {
    unsigned long diff = currentTimeRightEncoder - lastTimeRightEncoder;
    Serial.print("R: ");
    Serial.println(diff);
    lastTimeRightEncoder = currentTimeRightEncoder;
  }

  
  if (Serial.available())
  {
    int num = Serial.parseInt();
    
    setSpeed(num);
  }
//  Serial.println(currentTimeLeftEncoder);
//  Serial.println(gt);

  if (enc1 == HIGH && enc1Last != HIGH)
  {
    enc1Last = HIGH;
    unsigned long t = micros();
    unsigned long diff = t - lastTimeLowHigh;
    lastTimeLowHigh = t;
    
    Serial.print("Encoder 1: HIGH ");
    Serial.println(diff);
  }
  else if (enc1 == LOW && enc1Last != LOW)
  {
    enc1Last = LOW;
    unsigned long t = micros();
    unsigned long diff = t - lastTimeHighLow;
    lastTimeHighLow = t;
    Serial.print("Encoder 1: LOW ");
    Serial.println(diff);
  }

//  if (enc2 == HIGH && enc2Last != HIGH)
//  {
//    enc2Last = HIGH;
//    Serial.println("Encoder 2: HIGH");
//  }
//  else if (enc2 == LOW && enc2Last != LOW)
//  {
//    enc2Last = LOW;
//    Serial.println("Encoder 2: LOW");
//  }
  
}
