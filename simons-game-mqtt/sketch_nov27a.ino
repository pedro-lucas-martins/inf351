#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define LED_PIN 3
#define NUM_LEDS 64

#define WIFI_SSID "PEDRO"
#define WIFI_PASSWORD "12345567p"

#define MQTT_BROKER "broker.emqx.io"
#define MQTT_PORT 1883

WiFiClient espClient;
PubSubClient client(espClient);

char sequencia[100];
char cor[100];
int tamCor = 0;
bool comecou = false;
int tamSeq = 0;

CRGB leds[NUM_LEDS];

void setup_wifi() {
  delay(10);
  Serial.print("Conectando ao ");
  Serial.print(" ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  randomSeed(micros());

  Serial.println("Conectado ao Wifi!");
}

void callback(char* topic, byte* payload, unsigned int length) {
  cor[tamCor++] = (char)payload[0];
  Serial.print((char)payload[0]);
  comecou = true;
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Tentando conexao com MQTT");
    String clientId = "esp8266";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado ao MQTT");
      client.publish("outTopic", "UFV");
      client.subscribe("device/led");
    } else {
      Serial.print("Falha, rc= ");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);
  FastLED.addLeds<WS2811, LED_PIN>(leds, NUM_LEDS);
  randomSeed(analogRead(0));

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Green;
  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Yellow;
  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;
  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(1000);
  setup_wifi();
  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);
}

void loop() {
  int sequence;
  for (int i = 0; i < 100; i++){
    Serial.print(sequencia[i]);
  }
  if (!client.connected()) {
    reconnect();
  }
  Serial.println(tamSeq);
  if (tamSeq == 0) {  //correto
    sequencia[tamSeq++] = 'y';
  } 
  
  
  for (int i = 0; i <= tamSeq; i++) {
    if (sequencia[i] == 'r') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Green;
      }
      FastLED.show();
      delay(1000);
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
      }
      FastLED.show();
    } else if (sequencia[i] == 'g') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;
      }
      FastLED.show();
      delay(1000);
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
      }
      FastLED.show();
    } else if (sequencia[i] == 'b') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Blue;
      }
      FastLED.show();
      delay(1000);
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
      }
      FastLED.show();
    } else if (sequencia[i] == 'y') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Yellow;
      }
      FastLED.show();
      delay(1000);
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
      }
      FastLED.show();
    }
  }
  client.loop();
  if (comecou) {  //erro toda hora
    sequence = random(1, 5);
    Serial.println(sequence);
    for (int i = 0; i < tamSeq; i++) {
      if (cor[i] != sequencia[i]) {
        Serial.println("Sequencia errada!");
        tamSeq = 0;
        tamCor = 0;
        
      }
      else {comecou = false;}
    }
    if (sequence == 1) {
      sequencia[tamSeq++] = 'r';
    }

    if (sequence == 2) {
      sequencia[tamSeq++] = 'g';
    }

    if (sequence == 3) {
      sequencia[tamSeq++] = 'b';
    }

    if (sequence == 4) {
      sequencia[tamSeq++] = 'y';
    }
    comecou = false;
    
  }
}