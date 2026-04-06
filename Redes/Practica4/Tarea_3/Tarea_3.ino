#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>

BLEService imuService("1101");

// Característica solo lectura + notificaciones, 12 bytes (3 floats x 4 bytes)
BLECharacteristic accelCharacteristic("2101", BLERead | BLENotify, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Error iniciando IMU");
    while (1);
  }

  if (!BLE.begin()) {
    Serial.println("Error iniciando BLE");
    while (1);
  }

  BLE.setLocalName("Miguel");
  BLE.setAdvertisedService(imuService);
  imuService.addCharacteristic(accelCharacteristic);
  BLE.addService(imuService);
  BLE.advertise();

  Serial.println("BLE IMU Peripheral listo");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Conectado: ");
    Serial.println(central.address());

    while (central.connected()) {
      float x, y, z;

      if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(x, y, z);

        // Empaquetamos los 3 floats en un array de bytes
        float datos[3] = {x, y, z};
        accelCharacteristic.writeValue((byte*)datos, 12);

        Serial.print("X: "); Serial.print(x);
        Serial.print(" Y: "); Serial.print(y);
        Serial.print(" Z: "); Serial.println(z);
      }
    }

    Serial.println("Desconectado");
  }
}