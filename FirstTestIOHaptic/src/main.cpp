/* PARTIE HAPTIQUE DU PROJET */

#include <Arduino.h>
#include <M5Stack.h>
#include <sensors.h>


/*VIBRATION MOTOR MODULE PINOUT

This module has 3 pins:

    VCC: Module power supply – 5 V
    GND: Ground
    IN: Input
*/

/* On définit une constante In qui sera le numéro sur lequel on branche notre module */
#define In 1

/* On définit nos limites de vibrations */
#define LIMITE_DANGER 30
#define LIMITE_WARNING 60

/* boucle SETUP qui va ne se lancer qu'une seule fois avant tout le reste du code*/
void setup() {

  Serial.begin(9600); /* On ouvre le 1er port série Arduino, et fixe la vitesse de communication avec l'ordinateur à 9600 caractères par minute */
  pinMode(In, OUTPUT); /* On définit In comme la sortie --> là où on veut que la arduino envoie les instructions */

}

/* boucle LOOP qui se répète sans discontinuité */
void loop() {
  
  digitalWrite(In, HIGH); /* On allume la vibration */
  delay(500); /* temps de pause en ms */
  digitalWrite(In, LOW); /* On éteint la vibration */
  delay(800);
  
}
