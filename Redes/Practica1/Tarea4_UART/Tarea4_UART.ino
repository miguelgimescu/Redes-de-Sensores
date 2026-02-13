// ===============================
// PRACTICA 1 - TAREA 4
// tipo string gestiona por la UART los periféricos 
// Comandos: ADC, ADC(x), PWM(x)
// ===============================

#include <mbed.h>

mbed::Ticker timerADC;
const int pinADC = A0;
const int pinPWM = 9;

volatile bool flagEnviarADC = false;

// Función interrupción timer
void timerISR() {
  flagEnviarADC = true;
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  analogWriteResolution(8);

  Serial.println("=== TAREA 4: Protocolo UART ===");
  Serial.println("Comandos disponibles:");
  Serial.println("  ADC");
  Serial.println("  ADC(x)  -> cada x segundos (x=0 parar)");
  Serial.println("  PWM(x)  -> duty cycle nivel 0-9");
}

void loop() {

  // --- Envío periódico ADC ---
  if (flagEnviarADC) {
    flagEnviarADC = false;

    int val = analogRead(pinADC);
    Serial.print("[ADC PERIODICO] ");
    Serial.println(val);
  }

  // --- Lectura de comandos UART ---
  if (Serial.available()) {

    String cmd = Serial.readStringUntil('\n');
    cmd.trim(); // elimina espacios

    // -------------------------
    // COMANDO: ADC
    // -------------------------
    if (cmd == "ADC") {

      int val = analogRead(pinADC);
      Serial.print("ADC actual = ");
      Serial.println(val);
    }

    // -------------------------
    // COMANDO: ADC(x)
    // -------------------------
    else if (cmd.startsWith("ADC(")) {

      int x = cmd.substring(4, cmd.length() - 1).toInt();

      if (x == 0) {
        timerADC.detach();
        Serial.println("ADC periódico detenido");
      } else {
        timerADC.attach(&timerISR, x);
        Serial.print("ADC enviado cada ");
        Serial.print(x);
        Serial.println(" segundos");
      }
    }

    // -------------------------
    // COMANDO: PWM(x)
    // -------------------------
    else if (cmd.startsWith("PWM(")) {

      int x = cmd.substring(4, cmd.length() - 1).toInt();
      x = constrain(x, 0, 9);

      int duty = map(x, 0, 9, 0, 255);

      analogWrite(pinPWM, duty);

      Serial.print("PWM configurado a nivel ");
      Serial.print(x);
      Serial.print(" -> duty=");
      Serial.println(duty);
    }

   
    // Comando desconocido
    
    else {
      Serial.println("Comando no reconocido");
    }
  }
}
