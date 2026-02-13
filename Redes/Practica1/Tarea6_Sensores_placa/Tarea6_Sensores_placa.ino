// ===============================
// PRACTICA 1 - TAREA 6
// Lectura y muestra datos de los
// sensores acelerómetro, giróscopo y magnetómetro  
// ===============================

#include <mbed.h>
#include <Arduino_LSM9DS1.h>

//del acelerometro
//float x, y, z;
//int degreesX = 0;
//int degreesY = 0;
//del giroscopo
//float x, y, z;
//int plusThreshold = 30, minusThreshold = -30;
//del magnetometro
//float x,y,z, ledvalue;

unsigned long lastSampleTime = 0;
unsigned long lastSendTime   = 0;

// Variables para almacenar lecturas
float ax, ay, az;
float gx, gy, gz;
float mx, my, mz;


void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("=== TAREA 6: Lectura Sensores ===");
 // Serial.println("Comandos disponibles:");

 if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.println("IMU inicializada correctamente");
}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned long currentTime = millis();
  // 1) Muestreo cada 100 ms
  if (currentTime - lastSampleTime >= 100) {
      lastSampleTime = currentTime;
      //leer acelerometro
    if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);

    }
    if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gx, gy, gz);
    }
     // read magnetic field in all three directions
    //IMU.readMagneticField(mx, my, mz);
    if (IMU.magneticFieldAvailable()) {
      IMU.readMagneticField(mx, my, mz);
    }

  }
  // 2) Envío UART cada 1 segundo
  if (currentTime - lastSampleTime >= 1000) {
    lastSampleTime = currentTime;
    Serial.print("Accel (g): ");
    Serial.print(ax);
    Serial.print(", ");
    Serial.print(ay);
    Serial.print(", ");
    Serial.println(az);





  }
  
}
