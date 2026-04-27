#include <Wire.h>

#define SLAVE_ADDRESS 0x08

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Master listo. Escribe 'on' o 'off'");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "on") {
      Wire.beginTransmission(SLAVE_ADDRESS);
      Wire.write(1);
      Wire.endTransmission();
      Serial.println("Enviado: ON");
    } else if (cmd == "off") {
      Wire.beginTransmission(SLAVE_ADDRESS);
      Wire.write(0);
      Wire.endTransmission();
      Serial.println("Enviado: OFF");
    }
  }
}