#include <driver/i2s.h>

#define I2S_CHANNEL I2S_NUM_0
#define SAMPLE_RATE 16000 // Velocidade padrão para reconhecimento de voz

void setup() {
  Serial.begin(115200);
  
  // Configura o I2S para ler o ADC interno (Microfone Analógico)
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_ADC_BUILT_IN),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 512,
    .use_apll = false
  };

  i2s_driver_install(I2S_CHANNEL, &i2s_config, 0, NULL);
  i2s_set_adc_mode(ADC_UNIT_1, ADC1_CHANNEL_6); // GPIO 34
  i2s_adc_enable(I2S_CHANNEL);
}

void loop() {
  int16_t buffer[512];
  size_t bytes_read = 0;
  
  // Lê os dados do microfone
  i2s_read(I2S_CHANNEL, (void*)buffer, sizeof(buffer), &bytes_read, portMAX_DELAY);
  
  // Envia os dados brutos via Serial para o computador
  int samples = bytes_read / 2;
  for (int i = 0; i < samples; i++) {
    Serial.println(buffer[i]);
  }
}