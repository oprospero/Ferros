 #define PIN_PWM 9
 
 void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PIN_PWM, OUTPUT);
  Serial.println("Ready Player One");
}

void loop() {

  if (Serial.available())
  {
    int num = Serial.parseInt();
    analogWrite(PIN_PWM, num);
    Serial.println(num);
  }
}
