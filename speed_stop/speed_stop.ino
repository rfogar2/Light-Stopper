#include "pitches.h"

int LED_ON;
int dir;
int delay_length;
String game_choice;

void setup() {
  dir = 1; // direction; 1 for up, -1 for down
  game_choice = digitalRead(1) == HIGH ? "random_light" : "timer_light";
  if (game_choice == "random_light") {
    delay_length = 500;
  } else {
    delay_length = 300;
  }
  
  for(int i = 5; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  
  pinMode(2, INPUT);
  
  LED_ON = 13;
  digitalWrite(LED_ON, HIGH); 
  delay(delay_length);
  randomSeed(analogRead(0));
}

void (* reset) (void) = 0; 

void win() {
  tone(4, NOTE_C7, 200);
  
  for(int i = 5; i <= 13; i++) {
    digitalWrite(i, HIGH);
  }
  delay(200);
  tone(4, NOTE_D7, 100);
  delay(100);
  tone(4, NOTE_DS7, 500);
  delay(3700);
  for(int i = 5; i <= 13; i++) {
    digitalWrite(i, LOW);
  }
  
  reset();
}

void success_blink() {
  tone(4, NOTE_A5, 20);
  
  if (game_choice == "random_light" && delay_length <= 200) {
    win();
  }
  if (game_choice == "timer_light" && delay_length <= 80) {
    win();
  }
  
  
  if(delay_length <= 100) 
    delay_length -= 10;
  else 
    delay_length -= 50;
    
    
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED_ON, HIGH);
    delay(delay_length);
    digitalWrite(LED_ON, LOW);
    delay(delay_length);
  }
}

void fail_blink() {
  tone(4, NOTE_G3, 20);
  
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED_ON, HIGH);
    delay(delay_length);
    digitalWrite(LED_ON, LOW);
    delay(delay_length);
  }
  
  digitalWrite(LED_ON, HIGH);
  delay(1000);
  digitalWrite(LED_ON, LOW);

  // go back one round
  if (delay_length < 100) {
    delay_length += 10;
  } else {
    delay_length += 50;
  }
}



void loop() {
  if (game_choice == "timer_light") {
    timer_light();
  } else {
    random_light();
  }
}

void timer_light() {
  int switchState = digitalRead(2);
  
  if(switchState == HIGH) {
    if(LED_ON == 9) 
      success_blink();
    else
       fail_blink();
  }
  if(switchState == LOW) { // move to next color
    digitalWrite(LED_ON, LOW);
    switch(LED_ON) {
      case 13: dir = -dir;
               break;
      case 5: dir = -dir;
               break;
      default: break;
    }
    LED_ON += dir;
    digitalWrite(LED_ON, HIGH);
  }
  delay(delay_length);
}

void random_light() {
  // randomly select a light to light up. if use stops on
  // green light, move to next round
  // if user stops on other light, reset();

  int buttonState = digitalRead(2);

  if (buttonState == HIGH) {
    // check if they are on the right light
    if (LED_ON == 9)
      success_blink();
    else
      fail_blink();
  } else {
    // move to next light
    digitalWrite(LED_ON, LOW);
    
    // must be a different light from last time
    int nextLight = random(5, 14);
    while (LED_ON == nextLight) {
      nextLight = random(5, 14);
    }
    
    LED_ON = nextLight;
    digitalWrite(LED_ON, HIGH);
  }
  delay(delay_length);
}

