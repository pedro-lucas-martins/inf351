#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Fonts/FreeSans9pt7b.h>

#include <Wire.h>
#include <VL53L0X.h>

#define PIN            3 // Pin do ESP8266 conectado ao painel LED
#define WIDTH          8 // Largura do painel LED
#define HEIGHT         8 // Altura do painel LED

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

VL53L0X sensor;

void setup() {
    Serial.begin(9600);
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(50); // Ajuste o brilho conforme necessário
  matrix.setFont(&FreeSans9pt7b); // Escolha a fonte desejada

  // Cor da fonte (vermelho, verde, azul)
  matrix.setTextColor(matrix.Color(255, 255, 255));
  
}

void eyeAnimation(){
  uint8_t eye0[] = {
    0b00111100,
    0b01000010,
    0b10011001,
    0b10111101,
    0b10111101,
    0b10011001,
    0b01000010,
    0b00111100
  };

    uint8_t eye1[] = {
    0b00111100,
    0b01000010,
    0b10110001,
    0b10011111,
    0b11111001,
    0b10001101,
    0b01000010,
    0b00111100
  };

  uint8_t eye2[] = {
    0b00111100,
    0b01000010,
    0b10001101,
    0b11111001,
    0b10011111,
    0b10110001,
    0b01000010,
    0b00111100
  };

  // Exibir imagem no painel LED
  for (int16_t y = 0; y < HEIGHT; y++) {
    for (int16_t x = 0; x < WIDTH; x++) {
      if (eye0[y] & (1 << x)) {
        matrix.drawPixel(x, y, matrix.Color(255, 0, 0)); // Cor da imagem (vermelho, verde, azul)
      } else {
        matrix.drawPixel(x, y, matrix.Color(0, 0, 0)); // Cor de fundo (vermelho, verde, azul)
      }
    }
  }

  matrix.show();
  delay(1000); // Aguarda 2 segundos antes de limpar a tela
  for (int16_t y = 0; y < HEIGHT; y++) {
    for (int16_t x = 0; x < WIDTH; x++) {
      if (eye1[y] & (1 << x)) {
        matrix.drawPixel(x, y, matrix.Color(255, 0, 0)); // Cor da imagem (vermelho, verde, azul)
      } else {
        matrix.drawPixel(x, y, matrix.Color(0, 0, 0)); // Cor de fundo (vermelho, verde, azul)
      }
    }
  }
  matrix.show();
  delay(1000); // Aguarda 1 segundo antes de exibir novamente
  for (int16_t y = 0; y < HEIGHT; y++) {
    for (int16_t x = 0; x < WIDTH; x++) {
      if (eye0[y] & (1 << x)) {
        matrix.drawPixel(x, y, matrix.Color(255, 0, 0)); // Cor da imagem (vermelho, verde, azul)
      } else {
        matrix.drawPixel(x, y, matrix.Color(0, 0, 0)); // Cor de fundo (vermelho, verde, azul)
      }
    }
  }
  matrix.show();
  delay(1000); // Aguarda 1 segundo antes de exibir novamente
  for (int16_t y = 0; y < HEIGHT; y++) {
    for (int16_t x = 0; x < WIDTH; x++) {
      if (eye2[y] & (1 << x)) {
        matrix.drawPixel(x, y, matrix.Color(255, 0, 0)); // Cor da imagem (vermelho, verde, azul)
      } else {
        matrix.drawPixel(x, y, matrix.Color(0, 0, 0)); // Cor de fundo (vermelho, verde, azul)
      }
    }
  }
  matrix.show();
  delay(1000);
}

void closeEyes(){

  uint8_t eyeC[] = {
    0b00111100,
    0b01111110,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b01111110,
    0b00111100
  };


  for (int16_t y = 0; y < HEIGHT; y++) {
    for (int16_t x = 0; x < WIDTH; x++) {
      if (eyeC[y] & (1 << x)) {
        matrix.drawPixel(x, y, matrix.Color(255, 0, 0)); // Cor da imagem (vermelho, verde, azul)
      } else {
        matrix.drawPixel(x, y, matrix.Color(0, 0, 0)); // Cor de fundo (vermelho, verde, azul)
      }
    }
  }

  matrix.show();
  delay(1000); // Aguarda 2 segundos antes de limpar a tela
}

void loop() {

    if (sensor.timeoutOccurred()) {
    Serial.println("Timeout!");
  } else {
    int distance = sensor.readRangeSingleMillimeters(); // Lê a distância em milímetros
    if (distance >= 800){
      eyeAnimation();
    }
    if (distance <= 50){
        closeEyes();
    }

    if (distance >= 0) {
      Serial.print("Distancia: ");
      Serial.print(distance);
      Serial.println(" mm");
    } else {
      Serial.println("Fora de alcance");
    }
  }

  delay(1000); // Aguarda 1 segundo antes de ler novamente
}