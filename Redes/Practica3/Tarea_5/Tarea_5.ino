#include <WiFi.h>
#include <time.h>

// Tus credenciales
const char* ssid = "OPPOmiguel";
const char* password = "12345679";

// CONFIGURACIÓN DEL PC
const char* host = "10.138.109.6"; 
const uint16_t port = 455;

WiFiClient client;

bool enviar = false;//para comprobar 


void setup() {
  Serial.begin(115200);

  // Conexión WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado");
 
  configTime(3600, 3600, "pool.ntp.org");
}

void loop() {
  if (!client.connected()) {
    Serial.println("Conectando al servidor...");
    if (client.connect(host, port)) {
      Serial.println("¡Conectado!");
    }
    delay(2000);
  } else {
    
    //  TAREA 5  
    if (client.available()) {
      String line = client.readStringUntil('\n');
      line.trim(); // Limpia espacios y saltos de línea
      Serial.print("PC dice: ");
      Serial.println(line);

      if (line == "start") {
        enviar = true;
        client.println(">> Iniciando envio de hora...");
      } 
      else if (line == "stop") {
        enviar = false;
        client.println(">> Envio detenido.");
      }
    }

    //  ENVIO CONDICIONAL
    if (enviar) {
      struct tm timeinfo;
      if (getLocalTime(&timeinfo)) {
        char buffer[30];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", &timeinfo);
        client.println(buffer); 
      }
    }
    // ---------------------------------

    delay(1000);
  }
}