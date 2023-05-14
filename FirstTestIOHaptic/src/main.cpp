/* PARTIE HAPTIQUE DU PROJET */

#include <Arduino.h>
#include <M5Stack.h>
#include <sensors.h>

//initialiser les motors à LOW
// enlever le serial.begin ?


/*VIBRATION MOTOR MODULE PINOUT

This module has 3 pins:

    VCC: Module power supply – 5 V
    GND: Ground
    IN: Input
*/

/* On définit une constante MotorPin qui sera le numéro sur lequel on branche notre module
et sensorPin pour le port des sensors */
#define moteurGauche 17
#define moteurDroit 25
#define moteurDevant 2
#define moteurDerrière 5

/* On définit nos limites de vibrations */
//#define LIMITE_DANGER 30
//#define LIMITE_WARNING 60


void setup() {

  // Init de la M5STack
  M5.begin(true, false, true, true);
    
    // Démarrage de la M5Stack
  M5.Power.begin();

    // Taille de la police
  M5.Lcd.setTextSize(4);

    // Si l'init des capteurs a réussi :
  if (initSensors())
  {
    M5.Lcd.print(":) Connexion en mode HAPTIQUE <3\n");
  }
  else
  {
    M5.Lcd.println("Ohhh, ça n'a pas marché... ;((\n");
  } 
   
  /* On définit In comme la sortie --> là où on veut que la arduino envoie les instructions */

  /*pinMode(motorPin1, OUTPUT); 
  pinMode(motorPin2, OUTPUT); 
  pinMode(motorPin3, OUTPUT); 
  pinMode(motorPin4, OUTPUT); */
  /*pinMode(motorPin5, OUTPUT); 
  pinMode(motorPin6, OUTPUT); 
  pinMode(motorPin7, OUTPUT); 
  pinMode(motorPin8, OUTPUT); */


}

void loop() {

  M5.update();
  if(processSensors()){ //je récupère les données des capteurs
  
    getNewSensorValues();
    
  }
  

}