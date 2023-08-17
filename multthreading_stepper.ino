#define CW 5  // CW+
#define CCW 7 // CCW+
#define LED_PIN 8 

volatile boolean executing = false;  

void CW_n(int n) {
  executing = true;
  for (int i = 0; i < n; i++) {
    digitalWrite(CW, HIGH);
    delayMicroseconds(1000); 
    digitalWrite(CW, LOW);
    delayMicroseconds(1000);
  }
  executing = false;
}

void CCW_n(int n) {
  executing = true;
  for (int i = 0; i < n; i++) {
    digitalWrite(CCW, HIGH);
    delayMicroseconds(1000);
    digitalWrite(CCW, LOW);
    delayMicroseconds(1000);
  }
  executing = false;
}

void blinkLED(int times, int delayMs) {
  for (int i = 0; i < times * 2; i++) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(delayMs);
  }
}

void stopMotor() {
  digitalWrite(CW, LOW);
  digitalWrite(CCW, LOW);
  executing = false;
}

void setup() {
  pinMode(CW, OUTPUT);
  pinMode(CCW, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0 && !executing) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "CW") {
      CW_n(3600); //
    } else if (command == "CCW") {
      CCW_n(3600); // 
    } else if (command == "STOP") {
      stopMotor();
    } else if (command == "BLINK") {
      blinkLED(10, 200);
    }
  }
}
