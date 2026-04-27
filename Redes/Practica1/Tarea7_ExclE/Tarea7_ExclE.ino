#include <Wire.h>

#define SLAVE_ADDRESS 0x08
#define SDA_PIN 21
#define SCL_PIN 22
#define LED_PIN 2

const int BYTES_PER_SAMPLE = 36;  // 9 floats x 4 bytes
byte buffer[BYTES_PER_SAMPLE];
int bufIdx = 0;
volatile bool encenderLED = false;
unsigned long ledTimer = 0;

void receiveEvent(int numBytes) {
  // Señal de fin de transmisión
  if (numBytes == 1) {
    byte b = Wire.read();
    if (b == 0xFF) encenderLED = true;
    return;
  }

  while (Wire.available()) {
    if (bufIdx < BYTES_PER_SAMPLE) {
      buffer[bufIdx++] = Wire.read();
    } else {
      Wire.read();
    }
  }

  if (bufIdx >= BYTES_PER_SAMPLE) {
    float ax = bytesToFloat(0),  ay = bytesToFloat(4),  az = bytesToFloat(8);
    float gx = bytesToFloat(12), gy = bytesToFloat(16), gz = bytesToFloat(20);
    float mx = bytesToFloat(24), my = bytesToFloat(28), mz = bytesToFloat(32);

    Serial.printf("Acc: %.3f, %.3f, %.3f\n", ax, ay, az);
    Serial.printf("Gyr: %.3f, %.3f, %.3f\n", gx, gy, gz);
    Serial.printf("Mag: %.3f, %.3f, %.3f\n", mx, my, mz);
    Serial.println("---");

    bufIdx = 0;
  }
}

float bytesToFloat(int offset) {
  float val;
  memcpy(&val, buffer + offset, 4);
  return val;
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
  if (encenderLED) {
    digitalWrite(LED_PIN, HIGH);
    ledTimer = millis();
    encenderLED = false;
  }
  if (digitalRead(LED_PIN) == HIGH && millis() - ledTimer >= 1000) {
    digitalWrite(LED_PIN, LOW);
  }
}