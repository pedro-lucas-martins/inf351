
// Definição de variáveis
#define ledR 11
#define ledG 10
#define ledB 9

int sequencia[200];

int tamSeq = 0;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);
  //Serial.println("0");
  // Declaração dos pinos usados
  pinMode(ledG, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledB, OUTPUT);
  analogWrite(ledR, 255);
  analogWrite(ledG, 255);
  analogWrite(ledB, 255);

  randomSeed(analogRead(0)); // Garante que os números serão aleatórios quando o jogo é reiniciado
      analogWrite(ledR, 0);
      delay(500);
      analogWrite(ledR, 255);
      analogWrite(ledG, 0);
      delay(500);
      analogWrite(ledG, 255);
      analogWrite(ledB, 0);
      delay(500);
      analogWrite(ledB, 255);
      analogWrite(ledG, 0);
      analogWrite(ledR, 100);
      delay(500);
      

    analogWrite(ledG, 255); // Apaga leds
    analogWrite(ledR, 255);
    analogWrite(ledB, 255);
    delay(1000); // Pausa de 1 segundo
}

int readKeyboard(){

  while(!Serial.available()) {}
  char reading = Serial.read();
  switch (reading) {
    case '1':
    delay(200);
    return 1;
    break;

    case '2':
    delay(200);
    return 2;
    break;

    case '3':
    delay(200);
    return 3;
    break;

    case '4':
    delay(200);
    return 4;
    break;

    default:
    delay(200);
    return -1;
  }
}

int releaseKey(){
  return 0;
}

void blinkSequencia(){
  for (int i = 0; i < tamSeq; i++){
      int cor = sequencia[i];

      switch(cor){
        case 1:
        delay(500);
        analogWrite(ledG, 0);
        Serial.println("green");
        delay(500);
        analogWrite(ledG, 255);
        delay(500);
        break;
        case 2:
        delay(500);
        analogWrite(ledR, 0);
        Serial.println("red");
        delay(500);
        analogWrite(ledR,255);
        delay(500);
        break;
        case 3:
        delay(500);
        analogWrite(ledG, 0);
        analogWrite(ledR, 100);
        Serial.println("yellow");
        delay(500);
        analogWrite(ledG, 255);
        analogWrite(ledR, 255);
        delay(500);
        break;
        case 4:
        delay(500);
        analogWrite(ledB, 0);
        Serial.println("blue");
        delay(500);
        analogWrite(ledB,255);
        delay(500);
        break;
        default:
        break;
      }

  }
}



void loop() {
    // Como os botão estão ligados em portas analógicas, quando eles são pressionados, o valor de retorno é 1023

    int newColor = random(1,5);
    sequencia[tamSeq++] = newColor;

    blinkSequencia();

    for (int i = 0; i < tamSeq; i++){
      int escolha = readKeyboard();
      if (escolha == -1 || escolha != sequencia[i]){
        Serial.println("fail");
        while(true){}
      }
    }
}