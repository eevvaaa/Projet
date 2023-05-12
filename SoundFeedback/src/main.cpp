#include <M5Stack.h>
#include <sensors.h>
#include "BluetoothA2DPSource.h"
#include "BluetoothA2DPCommon.h"

#define LIMITE_DANGER 30
#define LIMITE_WARNING 60

BluetoothA2DPSource a2dp_source;

extern const unsigned char warning_wav[];
extern unsigned int warning_wav_len;
extern const unsigned char danger_wav[];
extern const unsigned char danger_wav_len;

/* SoundData *warning = new TwoChannelSoundData((Frame *)warning_wav, warning_wav_len / 4);
SoundData *danger = new TwoChannelSoundData((Frame *)danger_wav, danger_wav_len / 4); */ 

void buttonCheck()
{
  if (M5.BtnA.wasPressed())
  {
    M5.Power.deepSleep();
  }
}

void setup()
{
  // Init de la M5STack
  M5.begin(true, false, true, true);

  // Démarrage de la M5Stack
  M5.Power.begin();

  M5.Lcd.setTextSize(2.5);

  M5.Lcd.println("Bonjour, bienvenue dans le mode sonore");

  M5.Lcd.println("Tentative de connexion au casque...");

  // Connexion au casque
  a2dp_source.start("OpenMove by Shokz");

  a2dp_source.set_volume(30);

  //a2dp_source.write_data(warning);

  // a2dp_source.write_data(danger);

  /*//Si la connexion est réussie, affichage message et envoi son
  if(a2dp_source.is_connected()){
      M5.Lcd.println("Connexion au casque réussie");
      a2dp_source.write_data(danger);

  //Sinon, message erreur
  }else{
      M5.Lcd.println("Tentative de connexion échouée, vérifiez que l'appareil est bien allumé");
  }*/

  // Si l'init des capteurs a réussi :
  if (initSensors())
  {
    M5.Lcd.print("MCP2515 Initialized\nSuccessfully!");
  }
  else
  {
    M5.Lcd.println("Error Initializing MCP2515...");
  }
}

void loop()
{

  buttonCheck(); // On vérifie que l'utilisateur n'a pas mis la M5Stack en Deep sleep
  M5.update();

  M5.Lcd.print(processSensors());
  if (processSensors())
  {
    getNewSensorValues();
  }
}