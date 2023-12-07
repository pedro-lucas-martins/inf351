#include<ESP8266WiFi.h>
#include<PubSubClient.h>

///////////////////////////////////// MQTT ESP8266 E LED RGB APP CELULAR //////////////////////////////////////////

#define RED 14
#define GREEN 12
#define BLUE 16

//Conexao com Wifi

const char* ssid = "PEDRO";
const char* password = "12345567p";

//MQTT Broker

const char* broker = "broker.emqx.io";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

#define MSG_BUFFER_SIZE (50)

char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi(){
  delay(10);
  Serial.print("Conectando ao ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  randomSeed(micros());

  Serial.println("Conectado ao WiFi!");
}

void callback(char* topic, byte* payload, unsigned int length){
  //Serial.print("Mensagem recebida [");
  //Serial.print(topic);
  //Serial.print("]");

  //Serial.println(length);


  String redA = "";
  String blueA = "";
  String greenA = "";

  int i = 13;
  while((char)payload[i] != ','){              
    redA += (char)payload[i];
    i++;
  }
  i+=2;
  while((char)payload[i]!= ','){
    greenA += (char)payload[i];
    i++;
  }
  i += 2;
  while((char)payload[i] != ')'){
    blueA += (char)payload[i];
    i++;
  }

  //Serial.print(redA); Serial.print(" "); Serial.println(greenA);Serial.print(" "); Serial.println(blueA);

  analogWrite(RED, 255 -(redA.toInt()));
  analogWrite(GREEN, 255 -(greenA.toInt()));
  //analogWrite(BLUE,255 - (blueA).toInt());
}

void reconnect(){
  while(!client.connected()){
    Serial.println("Tentando conexao com MQTT");
    String clientId = "esp8266";
    clientId += String(random(0xffff), HEX);

    if(client.connect(clientId.c_str())){
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
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  setup_wifi();
  client.setServer(broker, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()){
    reconnect();
  }
  client.loop();
}