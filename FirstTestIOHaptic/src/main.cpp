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
#define moteurDroit 16
#define moteurDevant 2
#define moteurDerriere 5

/* On définit nos limites de vibrations */
//#define LIMITE_DANGER 30
//#define LIMITE_WARNING 60

int pwmChannelDroit = 0; //Choisit le canal 0-15
int pwmChannelGauche = 1; //Choisit le canal 0-15
int pwmChannelDevant = 2; //Choisit le canal 0-15
int pwmChannelDerriere = 3; //Choisit le canal 0-15

int frequence = 1000; //Fréquence PWM de 1 KHz
int resolution = 8; // Résolution de 8 bits, 256 valeurs possibles


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

  // Configuration du canal 0 avec la fréquence et la résolution choisie
  ledcSetup(pwmChannelDroit, frequence, resolution);
  ledcSetup(pwmChannelGauche, frequence, resolution);
  ledcSetup(pwmChannelDevant, frequence, resolution);
  ledcSetup(pwmChannelDerriere, frequence, resolution);

  // Assigne le canal PWM au pin 
  ledcAttachPin(moteurDroit, pwmChannelDroit);
  ledcAttachPin(moteurGauche, pwmChannelGauche);
  ledcAttachPin(moteurDevant, pwmChannelDevant);
  ledcAttachPin(moteurDerriere, pwmChannelDerriere);  

}

void loop() {

  M5.update();

  processSensorsDeux();
  /*
  if(processSensors()){ //je récupère les données des capteurs
    getNewSensorValues();    
  }
  */
  

}