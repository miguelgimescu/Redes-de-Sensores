
#define PIN_LED 2  

// Tarea 1: parpadeo de LED cada 200ms
void tareaLED(void *pvParameters) {
  pinMode(GPIO_NUM_4, OUTPUT);

  while (true) {
    digitalWrite(GPIO_NUM_4, 1);//me dejo ciego
    vTaskDelay(pdMS_TO_TICKS(200));
    digitalWrite(GPIO_NUM_4, LOW);
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

// Tarea 2: enviar "Hola mundo" por UART cada segundo
void tareaUART(void *pvParameters) {
  while (true) {
    Serial.println("Hola mundo");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  Serial.begin(115200);

  xTaskCreate(
    tareaLED,     // función de la tarea
    "LED",        // nombre (debug)
    1000,         // tamaño del stack (words)
    NULL,         // parámetros
    1,            // prioridad
    NULL          // handle (no lo necesitamos)
  );

  xTaskCreate(
    tareaUART,
    "UART",
    1000,
    NULL,
    1,
    NULL
  );

  // En ESP32 con FreeRTOS el scheduler arranca solo, no hace falta vTaskStartScheduler()
}

void loop() {
  // Vacío: todo corre en las tareas
}