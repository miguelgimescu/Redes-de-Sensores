// ===============================
//  práctica Python
// Acelerómetro cada 50 ms
// ===============================

#include <Arduino_LSM9DS1.h>

unsigned long lastSendTime = 0;
float ax, ay, az;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Error: IMU no detectada");
    while (1);
  }

  // Cabecera para Excel
  Serial.println("ax;ay;az");
}

void loop() {
  unsigned long t = millis();

  if (t - lastSendTime >= 50) {
    lastSendTime = t;

    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(ax, ay, az);

      Serial.print(ax); Serial.print(";");
      Serial.print(ay); Serial.print(";");
      Serial.println(az);
    }
  }
}
