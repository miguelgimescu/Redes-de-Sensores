#include <ArduinoJson.h>

unsigned long lastSend = 0;
const unsigned long periodo = 10000;  // 10 segundos
const unsigned long baseEpoch = 1710000000UL;

void setup() {
  Serial.begin(115200);
  delay(1000);

  randomSeed(esp_random());
}

void loop() {
  if (millis() - lastSend >= periodo) {
    lastSend = millis();

    float temperatura = random(2000, 3501) / 100.0;  // 20.00 a 35.00
    unsigned long t = baseEpoch + millis() / 1000;

    StaticJsonDocument<200> doc;
    JsonArray array = doc.to<JsonArray>();

    JsonObject obj = array.createNestedObject();
    obj["bn"] = "urn:dev:esp32:";
    obj["n"]  = "temperature";
    obj["u"]  = "Cel";
    obj["v"]  = temperatura;
    obj["t"]  = t;

    serializeJson(doc, Serial);
    Serial.println();
  }
}