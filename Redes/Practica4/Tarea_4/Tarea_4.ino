#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>

// Servicio BLE
BLEService imuService("180C");

// Characteristic para enviar aceleración
BLEStringCharacteristic accelCharacteristic("2A56", BLERead | BLENotify, 40);

// Characteristic de control (solo escritura)
BLEByteCharacteristic controlCharacteristic("2A57", BLEWrite);

// Variable para activar/desactivar IMU
bool imuEnabled = true;

void setup() {

  Serial.begin(9600);
  while (!Serial);

  // Inicializar IMU
  if (!IMU.begin()) {
    Serial.println("Error iniciando IMU");
    while (1);
  }

  // Inicializar BLE
  if (!BLE.begin()) {
    Serial.println("Error iniciando BLE");
    while (1);
  }

  BLE.setLocalName("Miguel");
  BLE.setAdvertisedService(imuService);

  // Añadir characteristics
  imuService.addCharacteristic(accelCharacteristic);
  imuService.addCharacteristic(controlCharacteristic);

  // Añadir servicio
  BLE.addService(imuService);

  // Empezar advertising
  BLE.advertise();

  Serial.println("BLE IMU listo");
}

void loop() {

  BLEDevice central = BLE.central();

  if (central) {

    Serial.print("Conectado a: ");
    Serial.println(central.address());

    while (central.connected()) {

      // Detectar comandos desde el móvil
      if (controlCharacteristic.written()) {

        if (controlCharacteristic.value() == 1) {
          imuEnabled = true;
          Serial.println("IMU activado");
        }
        if (controlCharacteristic.value() == 0) {
          imuEnabled = false;
          Serial.println("IMU desactivado");
        }
      }

      float x, y, z;

      if (imuEnabled && IMU.accelerationAvailable()) {

        IMU.readAcceleration(x, y, z);
        String data = String(x) + ";" + String(y) + ";" + String(z);
        accelCharacteristic.writeValue(data);
        Serial.println(data);

        delay(100);
      }
    }

    Serial.println("Desconectado");
  }
}