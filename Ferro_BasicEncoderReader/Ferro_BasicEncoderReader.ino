
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



unsigned long lastTimeLowHigh = 0;
unsigned long lastTimeHighLow = 0;
int enc1Last = LOW;
int enc2Last = LOW;
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
  Serial.println("Ready");
  motorForward();
}

void loop() {
  delay(2);
  int enc1 = digitalRead(PIN_ENCODER_1);
  int enc2 = digitalRead(PIN_ENCODER_2);

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

  if (enc2 == HIGH && enc2Last != HIGH)
  {
    enc2Last = HIGH;
    Serial.println("Encoder 2: HIGH");
  }
  else if (enc2 == LOW && enc2Last != LOW)
  {
    enc2Last = LOW;
    Serial.println("Encoder 2: LOW");
  }
  
  if (Serial.available())
  {
    int num = Serial.parseInt();

    setSpeed(num);
  }
  
}
