#include <WiFi.h>
#include <time.h>
//#include <Adafruit_MPU6050.h>
//#include <Adafruit_Sensor.h>
//#include <Wire.h>


// Tus credenciales
const char* ssid = "OPPOmiguel";
const char* password = "12345679";

// CONFIGURACIÓN DEL PC
const char* host = " 10.101.89.6"; 
const uint16_t port = 455;

WiFiClient client;

bool enviar = false;//para comprobar 

//Adafruit_MPU6050 mpu;


void setup() {
  Serial.begin(115200);

 // if (!mpu.begin()) {
 // Serial.println("Sensor init failed");
  //while (1)
 //   delay(10);
  //}

 //Serial.println("MPU6050 Found!");

  //mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

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
      //sensors_event_t a, g, temp;
      //mpu.getEvent(&a, &g, &temp);

          float ax = random(-100,100) / 100.0;
          float ay = random(-100,100) / 100.0;
          float az = random(-100,100) / 100.0;

           String data = String(ax) + ";" + String(ay) + ";" + String(az);

           client.println(data);

            Serial.println(data);

      
    }
    
    // ---------------------------------

    delay(1000);
  }
}