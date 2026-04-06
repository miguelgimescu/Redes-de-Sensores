#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {

  Serial.begin(115200);
  SerialBT.begin("ESP32_Miguel"); // nombre Bluetooth
  Serial.println("Bluetooth iniciado. Esperando conexión...");
}

void loop() {

  // Datos recibidos desde el móvil
  if (SerialBT.available()) {
    char c = SerialBT.read();
    Serial.write(c);
  }
  // Datos enviados desde el PC
  if (Serial.available()) {
    char c = Serial.read();
    SerialBT.write(c);
  }
}