#include <Wire.h>

#define SLAVE_ADDRESS 0x08
#define SDA_PIN 21
#define SCL_PIN 22
#define LED_PIN 2

void receiveEvent(int numBytes) {
  while (Wire.available()) {
    byte cmd = Wire.read();
    if (cmd == 1) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
    } else if (cmd == 0) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
    }
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SLAVE_ADDRESS, SDA_PIN, SCL_PIN);
  Wire.onReceive(receiveEvent);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("ESP32 Slave listo...");
}

void loop() {
  delay(100);
}