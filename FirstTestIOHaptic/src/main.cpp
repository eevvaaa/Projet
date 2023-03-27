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

/* On définit une constante MotorPin qui sera le numéro sur lequel on branche notre module
et sensorPin pour le port des sensors */
#define motorPin1 1
#define motorPin2 2
#define motorPin3 3
#define motorPin4 4
#define motorPin5 5
#define motorPin6 6
#define motorPin7 7
#define motorPin8 8

#define sensorPin 9


/* On définit nos limites de vibrations */
#define LIMITE_DANGER 30
#define LIMITE_WARNING 60


void setup() {

  Serial.begin(9600); /* On ouvre le 1er port série Arduino, et fixe la vitesse de communication avec l'ordinateur à 9600 caractères par minute */
  pinMode(motorPin1, OUTPUT); /* On définit In comme la sortie --> là où on veut que la arduino envoie les instructions */
  pinMode(motorPin2, OUTPUT); 
  pinMode(motorPin3, OUTPUT); 
  pinMode(motorPin4, OUTPUT); 
  pinMode(motorPin5, OUTPUT); 
  pinMode(motorPin6, OUTPUT); 
  pinMode(motorPin7, OUTPUT); 
  pinMode(motorPin8, OUTPUT); 

  pinMode(sensorPin, INPUT); /* sensorPIn = INPUT pour la arduino */
}

void loop() {

  // int valeurSensors = analogRead(sensorPin); /* On lit la valeur du sensor */

  // if (valeurSensors<=LIMITE_DANGER){ /* Si la valeur est inféreure ou égale à 30 cm, on met le capteur à fond */
  //   digitalWrite(motorPin, HIGH);
  //   delay(500); /* temps de pause en ms */
  // }else if (valeurSensors>LIMITE_DANGER && valeurSensors<=LIMITE_WARNING){ /* Si la valeur est dans la warning zone, on met le capteur à moitié */
  //   digitalWrite(motorPin, 0.5); 
  //   delay(500);
  // }else{ /* Sinon, on éteint la vibration */
  //   digitalWrite(motorPin, LOW); 
  //   delay(500);
  // }

  M5.update();
  processSensors(); //je récupère les données des capteurs


  //Version très simplifiée : avec une seule trame de capteurs et le même nombre de moteurs que de capteurs
    for(int i = 0 ; i < 2 ; i++){
        int values[6];      // on crée un tableau car on doit en passer un de la fonction suivante
        if(getNewSensorValues(i, values)){ //i c'est le N° de la trame
            for(int j = 0 ; j < 6 ; j++){ // les différents capteurs de la trame
              if (values[j]<=LIMITE_DANGER){
                digitalWrite(j, HIGH);
              }else if(values[j]>LIMITE_DANGER && values[j]<=LIMITE_WARNING){
                digitalWrite(j, 0.5);
              }else{
                digitalWrite(j, LOW);
              }
            }
        }
    }


}