/* PARTIE HAPTIQUE DU PROJET */

#include <Arduino.h>

/*VIBRATION MOTOR MODULE PINOUT

This module has 3 pins:

    VCC: Module power supply – 5 V
    GND: Ground
    IN: Input
*/

/* On définit une constante MotorPin qui sera le numéro sur lequel on branche notre module
et sensorPin pour le port des sensors */
#define motorPin 1
#define sensorPin 2


/* On définit nos limites de vibrations */
#define LIMITE_DANGER 30
#define LIMITE_WARNING 60

/* boucle SETUP qui va ne se lancer qu'une seule fois avant tout le reste du code*/
void setup() {

  Serial.begin(9600); /* On ouvre le 1er port série Arduino, et fixe la vitesse de communication avec l'ordinateur à 9600 caractères par minute */
  pinMode(motorPin, OUTPUT); /* On définit In comme la sortie --> là où on veut que la arduino envoie les instructions */
  pinMode(sensorPin, INPUT); /* sensorPIn = INPUT pour la arduino */
}

/* boucle LOOP qui se répète sans discontinuité */
void loop() {
  
  /* peut-être en faire une fonction pour chaque sensor ? */
  
  int valeurSensors = analogRead(sensorPin); /* On lit la valeur du sensor */

  if (valeurSensors<=LIMITE_DANGER){ /* Si la valeur est inféreure ou égale à 30 cm, on met le capteur à fond */
    digitalWrite(motorPin, HIGH);
    delay(500); /* temps de pause en ms */
  }else if (valeurSensors>LIMITE_DANGER && valeurSensors<=LIMITE_WARNING){ /* Si la valeur est dans la warning zone, on met le capteur à moitié */
    digitalWrite(motorPin, 0.5); 
    delay(500);
  }else{ /* Sinon, on éteint la vibration */
    digitalWrite(motorPin, LOW); 
    delay(500);
  }
  
  
}
