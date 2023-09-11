
void setup() {
  DDRB = B111111;

}

void RED(int intensity){
  PORTB = B110111;
  delayMicroseconds(intensity);
  PORTB = B111111;
}

void GREEN(int intensity){
  PORTB = B111011;
  delayMicroseconds(intensity);
  PORTB = B111111;
}

void BLUE(int intensity){
  PORTB = B111101;
  delayMicroseconds(intensity);
  PORTB = B111111;
}

void PURPLE(int intensity){
  RED(400);
  BLUE(1000);
  delayMicroseconds(intensity);
  RED(0);
  BLUE(0);
}

void CYAN(int intensity){
  BLUE(400);
  GREEN(900);
  delayMicroseconds(intensity);
  BLUE(0);
  GREEN(0);
}

void ORANGE(int intensity){
  RED(1000);
  GREEN(200);
  delayMicroseconds(intensity);
  RED(0);
  GREEN(0);
}

void PINK(int intensity){
  RED(400);
  BLUE(200);
  delayMicroseconds(intensity);
  RED(0);
  BLUE(0);
}

void YELLOW(int intensity){
  RED(650);
  GREEN(450);
  delayMicroseconds(intensity);
  RED(0);
  GREEN(0);
}
int count = 0;
void loop() {
  for (int i = 0; i < 256; i++){
    if (i == 255) {count++;}
    if (count == 0){
      RED(i);
      delay(10);
    }
    if (count == 1){
      CYAN(i);
      delay(10);
    }
    if (count == 2){
      ORANGE(i);
      delay(10);
    }
    if (count == 3){
      PURPLE(i);
      delay(10);
    }
    if (count == 4){
      GREEN(i);
      delay(10);
    }
    if (count == 5){
      PINK(i);
      delay(10);
    }
    if (count == 6){
      BLUE(i);
      delay(10);
    }
    if (count == 7){
      YELLOW(i);
      delay(10);
  }
    if (count > 7) count = 0; 
  }
}

