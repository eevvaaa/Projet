#include <Arduino.h>

int i=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //soso est trop chaud en arduino
  //c'est meme pas vrai d'abord
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello World !"+i);
  i ++;
  
}
