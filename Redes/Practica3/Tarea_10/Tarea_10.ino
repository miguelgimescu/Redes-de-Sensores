#include <WiFi.h>
#include "AdafruitIO_WiFi.h"

#define AIO_USERNAME  "miguelge99"    // tu nombre de usuario de io.adafruit.com
#define AIO_KEY       "aio_TLJkadivina"   // la clave larga que sale al pulsar el icono de llave
const char* ssid     = "OPPOmiguel"; // tu red
const char* password = "12345679";   // tu contraseña

AdafruitIO_WiFi io(AIO_USERNAME, AIO_KEY, ssid, password);
AdafruitIO_Feed *temperatura = io.feed("temperatura");

unsigned long lastSend = 0;
const unsigned long periodo = 10000; // 10 segundos

void handleMessage(AdafruitIO_Data *data) {
  Serial.print("[MQTT RX] temperatura: ");
  Serial.println(data->toString());
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  randomSeed(esp_random());

  Serial.print("Conectando a Adafruit IO");
  temperatura->onMessage(handleMessage);
  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("Adafruit IO conectado!");
  Serial.println(io.statusText());

  temperatura->get();
}

void loop() {
  io.run();

  if (millis() - lastSend >= periodo) {
    lastSend = millis();

    float temp = random(2000, 3501) / 100.0; // 20.00 a 35.00
    Serial.print("Enviando temperatura: ");
    Serial.println(temp, 2);

    temperatura->save(temp);
  }
}