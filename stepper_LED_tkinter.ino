#define CW 5 // CW+
#define CCW 7 // CCW+
#define LED_PIN 8 // Pin for the LED

bool motor_stopped = true; // Flag to indicate motor stop status

void setup() {
  pinMode(CW, OUTPUT);
  pinMode(CCW, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "CW") {
      if (!motor_stopped) {
        stopMotor();
        delay(100);
      }
      motor_stopped = false;
      CW_n(3600); // Rotate 360 degrees clockwise
      motor_stopped = true;
    } else if (command == "CCW") {
      if (!motor_stopped) {
        stopMotor();
        delay(100);
      }
      motor_stopped = false;
      CCW_n(3600); // Rotate 360 degrees counterclockwise
      motor_stopped = true;
    } else if (command == "STOP") {
      stopMotor();
    } else if (command == "BLINK") {
      blinkLED();
    } else {
      // do nothing
    }
  }
}

void CW_n(int n) {
  for (int i = 0; i < n; i++) {
    if (motor_stopped) {
      break;
    }
    digitalWrite(CW, HIGH);
    delayMicroseconds(1000); 
    digitalWrite(CW, LOW);
    delayMicroseconds(1000);
  }
}

void CCW_n(int n) {
  for (int i = 0; i < n; i++) {
    if (motor_stopped) {
      break;
    }
    digitalWrite(CCW, HIGH);
    delayMicroseconds(1000);
    digitalWrite(CCW, LOW);
    delayMicroseconds(1000);
  }
}

void stopMotor() {
  digitalWrite(CW, LOW);
  digitalWrite(CCW, LOW);
  motor_stopped = true;
}

void blinkLED() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
  }
}
