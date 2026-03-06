#include <WiFi.h>
#include <time.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


// Tus credenciales
const char* ssid = "OPPOmiguel";
const char* password = "12345679";

// CONFIGURACIÓN DEL PC
const char* host = "10.138.109.6"; 
const uint16_t port = 455;

WiFiClient client;

bool enviar = false;//para comprobar 

Adafruit_MPU6050 mpu;


void setup() {
  Serial.begin(115200);

  if (!mpu.begin()) {
  Serial.println("Sensor init failed");
  while (1)
    delay(10);
  }

 Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

  // Conexión WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado");
 
  //configTime(3600, 3600, "pool.ntp.org");
}

void loop() {
 

  if (!client.connected()) {
    Serial.println("Conectando al servidor...");
    if (client.connect(host, port)) {
      Serial.println("¡Conectado!");
    }
    delay(2000);
  } else {
    
    // Tarea 5
    if (client.available()) {
      String line = client.readStringUntil('\n');
      line.trim();
      
      if (line == "start") {
        enviar = true;
        client.println(">> Enviando datos del acelerometro...");
      } 
      else if (line == "stop") {
        enviar = false;
        client.println(">> Envio pausado.");
      }
    }

    //
    if (enviar) {
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);

      // Enviamos al PC 
      client.print("AX:"); client.print(a.acceleration.x);
      client.print(", AY:"); client.print(a.acceleration.y);
      client.print(", AZ:"); client.println(a.acceleration.z);

      // Monitor Serie 
      Serial.print("Enviando -> X: "); Serial.print(a.acceleration.x);
      Serial.print(" Y: "); Serial.print(a.acceleration.y);
      Serial.print(" Z: "); Serial.println(a.acceleration.z);
    }
    
    // ---------------------------------

    delay(1000);
  }
}