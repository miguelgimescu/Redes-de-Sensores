//void tareaLED(void *pvParameters) {
//  ledcSetup(0, 5000, 8);
//  ledcAttachPin(GPIO_NUM_4, 0);

//  while (true) {
//    ledcWrite(0, 8);            // encendido suave se puede subir hasta 255 si se usa high te deja ciego
//    vTaskDelay(pdMS_TO_TICKS(200));
//    ledcWrite(0, 0);            // apagado
//    vTaskDelay(pdMS_TO_TICKS(200));
//  }
//}

#define FLASH_GPIO      4
#define PWM_CHANNEL     7
#define PWM_FREQ        5000
#define PWM_RESOLUTION  8

int intensidad = 2;   // cambia aquí 0-255 si es mucho te deja ciego por eso no usar high

void tareaLED(void *pvParameters) {

  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(FLASH_GPIO, PWM_CHANNEL);

  while (true) {

    // ENCENDIDO
    ledcWrite(PWM_CHANNEL, intensidad);

    //Serial.printf("Intensidad: %d\n", intensidad);

    vTaskDelay(pdMS_TO_TICKS(200));

    // APAGADO
    ledcWrite(PWM_CHANNEL, 0);

    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

void tareaUART(void *pvParameters) {
  while (true) {
    Serial.println("Hola mundo");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(tareaLED,  "LED",  1000, NULL, 1, NULL);
  xTaskCreate(tareaUART, "UART", 1000, NULL, 1, NULL);
}

void loop() {}