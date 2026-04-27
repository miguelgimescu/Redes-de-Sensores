#include <Wire.h>
#include <Arduino_LSM9DS1.h>

#define SLAVE_ADDRESS 0x08

void setup() {
  Wire.begin();
  Serial.begin(9600);
  if (!IMU.begin()) {
    Serial.println("Error al iniciar IMU!");
    while (1);
  }
  Serial.println("PLACA 1 lista. Escribe 'start' para capturar.");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "start") capturarYEnviar();
  }
}

void capturarYEnviar() {
  const int N = 5;  // 5 muestras x 200ms = 1 segundo
  float ax[N], ay[N], az[N];
  float gx[N], gy[N], gz[N];
  float mx[N], my[N], mz[N];

  Serial.println("Capturando...");
  for (int i = 0; i < N; i++) {
    unsigned long t = millis();
    if (IMU.accelerationAvailable())  IMU.readAcceleration(ax[i], ay[i], az[i]);
    if (IMU.gyroscopeAvailable())     IMU.readGyroscope(gx[i], gy[i], gz[i]);
    if (IMU.magneticFieldAvailable()) IMU.readMagneticField(mx[i], my[i], mz[i]);
    while (millis() - t < 200);
  }

  Serial.println("Enviando por I2C...");
  for (int i = 0; i < N; i++) {
    Wire.beginTransmission(SLAVE_ADDRESS);
    enviarFloat(ax[i]); enviarFloat(ay[i]); enviarFloat(az[i]);
    enviarFloat(gx[i]); enviarFloat(gy[i]); enviarFloat(gz[i]);
    enviarFloat(mx[i]); enviarFloat(my[i]); enviarFloat(mz[i]);
    Wire.endTransmission();
    delay(10);
  }

  // Señal de fin
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(0xFF);
  Wire.endTransmission();
  Serial.println("Listo.");
}

void enviarFloat(float val) {
  byte* b = (byte*)&val;
  for (int i = 0; i < 4; i++) Wire.write(b[i]);
}