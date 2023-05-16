#include <Arduino.h>
#include <M5Stack.h>
#include <sensors.h>
#include "BluetoothA2DPSource.h"
#include "sonore.h"

extern BluetoothA2DPSource headphones;

void setup()
{
  // Init de la M5Stack
  M5.begin(true, false, true, true);

  // Démarrage de la M5Stack
  M5.Power.begin();

  // Taille de la police
  M5.Lcd.setTextSize(2.5);

  initSonore();

}

void loop(){
  M5.update();

  // Récupération des données des capteurs
  if(processSensors()){
   //Envoi ou non d'un son en fonction des données
    NewSoundValues1Board();
  }
}
