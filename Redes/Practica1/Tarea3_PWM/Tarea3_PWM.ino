// ===============================
// PRACTICA 1 - TAREA 3
// PWM proporcional a la lectura del ADC
// ===============================

const int pinADC = A0;    // Entrada analógica (potenciómetro)
const int pinPWM = 9;     // Salida PWM (pin digital con PWM)

int valorADC = 0;
int dutyPWM = 0;

void setup() {

  Serial.begin(115200);
  while (!Serial);

  Serial.println("=== TAREA 3: PWM proporcional al ADC ===");

  // Ajustamos resolución PWM a 8 bits (0-255)
  analogWriteResolution(8);

  // (Opcional) Ajustamos resolución ADC a 10 bits (0-1023)
  analogReadResolution(10);
}

void loop() {

  // 1. Leer ADC (0-1023)
  valorADC = analogRead(pinADC);

  // 2. Convertir ADC → Duty PWM (0-255)
  dutyPWM = map(valorADC, 0, 1023, 0, 255);

  // 3. Generar PWM con ese duty
  analogWrite(pinPWM, dutyPWM);

  // 4. Mostrar valores por consola
  float voltaje = (valorADC * 3.3) / 1023.0;

  Serial.print("ADC = ");
  Serial.print(valorADC);

  Serial.print(" | Voltaje = ");
  Serial.print(voltaje, 2);
  Serial.print(" V");

  Serial.print(" | Duty PWM = ");
  Serial.print(dutyPWM);

  Serial.println(" /255");

  // Pequeña pausa
  delay(200);
}
