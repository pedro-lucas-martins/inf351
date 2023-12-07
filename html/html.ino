//Inclusão das bibliotecas
#include <ESP8266WiFi.h>
  
const char* ssid = "PEDRO"; //Nome da Rede
const char* password = "12345567p"; //Password da rede
  
int ledPin = 16; //GPIO16 do ESP8266 e D0 do NodeMCU
  
WiFiServer server(80); //Porta 80
  
void setup() 
{
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT); //Define o D0 como saída
  digitalWrite(ledPin, LOW); //O LED começa desligado
  
  // Comunicação com a rede WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to "); //Mensagem apresentada no monitor serial
  Serial.println(ssid); //Apresenta o nome da rede no monitor serial
  WiFi.begin(ssid, password); //Inicia a ligação na rede
  
  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print("."); //Enquanto a ligação não for feita com sucesso é apresentada uma sucessão de “.” no monitor serial
  }
  
  Serial.println("");
  Serial.println("WiFi connected"); //Se a ligação é feita com sucesso é apresentada esta mensagem no monitor serial
   
  // Servidor
  server.begin(); //Comunicação com o servidor
  Serial.println("Servidor iniciado"); //É apresentado no monitor serial que o servidor foi iniciado
  
  //Impressão do endereço IP
  Serial.print("Use o seguinte URL para a comunicação: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); //Abrindo este endereço de IP no seu navegador te conduzirá a página HTML para controle do led
  Serial.println("/");
}
  
void loop() 
{
  //Verifica se o cliente está conectado
  WiFiClient client = server.available();
  
  if(!client)
  { 
    //Se o cliente não estiver conectado ao servidor, executa este ciclo até estar conectado
    return;
  }
   
  //Espera até o cliente enviar dados
  Serial.println("novo cliente"); //Apresenta esta mensagem quando o cliente se conecta ao servidor
  
  while(!client.available())
  {
    delay(1);
  }
  
  //Lê a primeira linha do pedido
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  //Operação do pedido
  int value = LOW;
  if(request.indexOf("/LED=OFF") != -1)  
  {
    digitalWrite(ledPin, HIGH); //Se o pedido no LedPin for LED = ON, acende o led
    value = HIGH;
  }
  
  if(request.indexOf("/LED=ON") != -1)  
  {
    digitalWrite(ledPin, LOW); //Se o pedido no LedPin for LED = OFF, apaga o led
    value = LOW;
  }
  
  //Inicialização da página HTML
  
  //Retorno do resposta
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
   
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("<center><font size='5'><b></b></font></center>");
  client.println("<br><br>");
  client.print("<center>Estado do LED: </center>");
  
  if(value == HIGH) 
  { 
    //Se está ligado apresenta “desligado”
    client.print("<center>desligado</center>");
  } 
   
  else
  {
    //Se está desligado apresenta “ligado”
    client.print("<center>ligado</center>");
  }
  
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><center><button>Ligar</button></center></a>"); //Ligar o led corresponde a "ligar"
  client.println("<a href=\"/LED=OFF\"\"><center><button>Desligar</button></center></a><br />");  //Desligar o led corresponde a "desligar"
  client.println("</html>");
  
  delay(1);
  
  Serial.println("Cliente desconectado");
  Serial.println("");
}