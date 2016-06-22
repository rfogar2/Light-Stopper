#include "pitches.h"

int LED_ON;
int dir;
int delay_length;

void setup() {
  dir = 1; // direction; 1 for up, -1 for down
  delay_length = 300;
  
  for(int i = 5; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  
  pinMode(2, INPUT);
  
  LED_ON = 13;
  digitalWrite(LED_ON, HIGH); 
  delay(delay_length);
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
  
  if(delay_length <= 100) {
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
  
  reset();
}

void loop() {
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
