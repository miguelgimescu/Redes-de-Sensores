#include <ArduinoBLE.h>

// UUID personalizado con tu nombre codificado como identificativo
// "Miguel" en hex: 4d-69-67-75-65-6c
BLEService myService("4d696775-656c-0000-0000-000000000000");

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!BLE.begin()) {
    Serial.println("Error iniciando BLE");
    while (1);
  }

  BLE.setLocalName("Miguel");
  BLE.setAdvertisedService(myService);
  BLE.addService(myService);
  BLE.advertise();

  Serial.println("BLE advertising iniciado");
}

void loop() {
  BLE.poll(); // mantiene BLE activo
}