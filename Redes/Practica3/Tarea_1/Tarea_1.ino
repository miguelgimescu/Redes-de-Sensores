#include <WiFi.h>

// Tus credenciales tal cual las tienes
const char* ssid = "OPPOmiguel";
const char* password = "12345679";

void setup() {
  Serial.begin(115200);
  delay(1000); // Un pequeño respiro para que el monitor serie cargue bien

  Serial.println("--- INICIANDO PRACTICA 3: TAREA 1 ---");
  
  // 1. Conectarse a la red wifi del laboratorio o móvil 
  WiFi.begin(ssid, password);
  Serial.print("Conectando a: ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // 2. Extraer la IP local 
  Serial.println("\nWiFi Conectado correctamente.");
  Serial.print("IP asignada: ");
  Serial.println(WiFi.localIP());

  // 3. Comprobar la conectividad con Google 
  Serial.println("Verificando conexion con Google...");
  
  WiFiClient client;
  if (client.connect("www.google.com", 80)) {
    Serial.println("Conexion con Google: OK (Ping exitoso)");
    client.stop(); // Cerramos la conexion despues de comprobar
  } else {
    Serial.println("Error: No se pudo conectar con Google.");
  }
}

void loop() {
  // Para la Tarea 1 el loop se queda vacio
}