// ===============================
// PRACTICA 1 - TAREA 2
// Timer hardware cada 10 segundos
// Lee ADC y lo muestra por UART
// ===============================

#include <mbed.h>

mbed::Ticker timerADC;

const int pinADC = A0;
volatile bool flagLeerADC = false;

// Función de interrupción (se ejecuta cada 10s)
void interrupcionTimer() {
  flagLeerADC = true;
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("=== TAREA 2: Timer cada 10 segundos ===");

  // Configurar interrupción cada 10 segundos
  timerADC.attach(&interrupcionTimer, 10.0);
}

void loop() {

  // Solo se ejecuta cuando el timer lo pide
  if (flagLeerADC) {
    flagLeerADC = false;

    int valorADC = analogRead(pinADC);

    float voltaje = (valorADC * 3.3) / 1023.0;

    Serial.print("[TIMER] ADC = ");
    Serial.println(valorADC);

    
    Serial.print("Voltaje = ");
    Serial.println(voltaje);
  }

  // Aquí el micro podría hacer otras cosas
}
