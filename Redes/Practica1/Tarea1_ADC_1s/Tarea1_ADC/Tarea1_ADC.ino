// ===============================
// PRACTICA 1 - TAREA 1
// Leer ADC cada 1 segundo
// ===============================

const int pinADC = A0;   // Pin analógico (A0)
int valorADC = 0;

void setup() {
  Serial.begin(115200);   // Abrimos comunicación serie
  while (!Serial);        // Espera a que se abra el monitor serie

  Serial.println("=== TAREA 1: Lectura ADC cada 1 segundo ===");
}

void loop() {
  // Leer ADC (0 a 1023)
  valorADC = analogRead(pinADC);

  // Convertir a voltaje (0 - 3.3V)
  float voltaje = (valorADC * 3.3) / 1023.0;

  // Mostrar por consola
  Serial.print("ADC = ");
  Serial.print(valorADC);

  Serial.print("   Voltaje = ");
  Serial.print(voltaje, 2); // 2 decimales
  Serial.println(" V");
  // Esperar 1 segundo
  delay(1000);
}
