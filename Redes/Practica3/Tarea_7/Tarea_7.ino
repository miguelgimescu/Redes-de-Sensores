#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "OPPOmiguel";
const char* password = "12345679";

WebServer server(80);

unsigned long tiempoBase   = 0; // millis() en el momento del último reset
unsigned long offsetSegundos = 0; // segundos acumulados antes del reset

String horaFormateada() {
  unsigned long seg = offsetSegundos + (millis() - tiempoBase) / 1000;
  unsigned long hh  = seg / 3600;
  unsigned long mm  = (seg % 3600) / 60;
  unsigned long ss  = seg % 60;
  char buf[9];
  sprintf(buf, "%02lu:%02lu:%02lu", hh, mm, ss);
  return String(buf);
}

void handleRoot() {
  String html = R"rawhtml(
<!DOCTYPE html><html><head>
<meta charset="utf-8">
<meta http-equiv="refresh" content="1">
<title>ESP32 Hora</title>
<style>
  body { font-family: Arial; text-align: center; margin-top: 80px; background:#1e1e1e; color:white; }
  h1   { font-size: 64px; margin-bottom: 20px; }
  button { font-size: 24px; padding: 12px 32px; background:#e74c3c;
           color:white; border:none; border-radius:8px; cursor:pointer; }
  button:hover { background:#c0392b; }
</style>
</head><body>
<p style="font-size:20px;">Hora del ESP32</p>
<h1>)rawhtml" + horaFormateada() + R"rawhtml(</h1>
<form action="/reset" method="GET">
  <button type="submit">Reset hora</button>
</form>
</body></html>
)rawhtml";
  server.send(200, "text/html", html);
}

void handleReset() {
  offsetSegundos = 0;
  tiempoBase     = millis();
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  tiempoBase = millis();

  server.on("/",      handleRoot);
  server.on("/reset", handleReset);
  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  server.handleClient();
}