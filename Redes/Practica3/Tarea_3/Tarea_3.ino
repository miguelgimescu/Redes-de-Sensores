#include <WiFi.h>
#include <time.h>

// Tus credenciales
const char* ssid = "OPPOmiguel";
const char* password = "12345679";

// CONFIGURACIÓN DEL PC
const char* host = "10.138.109.6"; 
const uint16_t port = 455;

WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Conexión WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado");

  // Configuración de hora NTP (Tarea 2)
  configTime(3600, 3600, "pool.ntp.org");
}

void loop() {
  // Si no está conectado, intenta conectar al SocketTest del PC
  if (!client.connected()) {
    Serial.println("Conectando al servidor...");
    if (client.connect(host, port)) {
      Serial.println("¡Conectado!");
    }
    delay(2000);
  } else {
    // Tarea 4: Enviar hora local cada segundo
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
      char buffer[30];
      strftime(buffer, sizeof(buffer), "%H:%M:%S", &timeinfo);
      client.println(buffer); // Esto aparecerá en SocketTest
    }

    // Leer si escribes algo desde SocketTest (Chat)
    if (client.available()) {
      String line = client.readStringUntil('\n');
      Serial.print("PC dice: ");
      Serial.println(line);
    }
    delay(1000);
  }
}