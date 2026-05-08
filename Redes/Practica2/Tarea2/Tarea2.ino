typedef struct {
  float ax, ay, az;
} AccelData;

QueueHandle_t dataQueue;


#define FLASH_GPIO      4
#define PWM_CHANNEL     7
#define PWM_FREQ        5000
#define PWM_RESOLUTION  8

int intensidad = 2;   // cambia aquí 0-255 si es mucho te deja ciego por eso no usar high


void tareaMuestreo(void *pvParameters) {
  AccelData data;
  while (true) {
    data.ax = (float)(random(-200, 200)) / 100.0;
    data.ay = (float)(random(-200, 200)) / 100.0;
    data.az = (float)(random(-200, 200)) / 100.0;
    xQueueOverwrite(dataQueue, &data);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void tareaEnvio(void *pvParameters) {
  AccelData data;
  while (true) {
    if (xQueuePeek(dataQueue, &data, 0) == pdTRUE) {
      Serial.printf("Acc X: %.2f g | Y: %.2f g | Z: %.2f g\n",
                    data.ax, data.ay, data.az);

     // ledcWrite(0, 8);                 // LED encendido 200ms al enviar
      ledcWrite(PWM_CHANNEL, intensidad);
      vTaskDelay(pdMS_TO_TICKS(200));
      //ledcWrite(0, 0);
      ledcWrite(PWM_CHANNEL, 0);
      vTaskDelay(pdMS_TO_TICKS(800));  // resto del segundo
    } else {
      vTaskDelay(pdMS_TO_TICKS(100));
    }
  }
}

void setup() {
  Serial.begin(115200);
  //ledcSetup(0, 5000, 8);
  //ledcAttachPin(GPIO_NUM_4, 0);
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(FLASH_GPIO, PWM_CHANNEL);

  dataQueue = xQueueCreate(1, sizeof(AccelData));

  xTaskCreate(tareaMuestreo, "Muestreo", 2048, NULL, 2, NULL);
  xTaskCreate(tareaEnvio,    "Envio",    2048, NULL, 1, NULL);
}

void loop() {}
