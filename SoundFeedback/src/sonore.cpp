#include <Arduino.h>
#include <M5Stack.h>
#include "BluetoothA2DPSource.h"
#include "BluetoothA2DPCommon.h"
#include "sonore.h"
#include "sensors.h"

BluetoothA2DPSource headphones;

extern const unsigned char connectionCheck_wav[];
extern const unsigned int connectionCheck_wav_len;

extern const unsigned char warning_wav[];
extern const unsigned int warning_wav_len;

extern const unsigned char danger_wav[];
extern const unsigned int danger_wav_len;

SoundData *connection = new TwoChannelSoundData((Frame *) connectionCheck_wav, connectionCheck_wav_len / 4);
SoundData *warning = new TwoChannelSoundData((Frame *)warning_wav, warning_wav_len / 4);
SoundData *danger = new TwoChannelSoundData((Frame *)danger_wav, danger_wav_len / 4);

extern int sensorValues[NBBOARD][6];

void initSonore(){
    M5.Lcd.println("Bonjour, bienvenue dans le mode sonore");

    M5.Lcd.println("Tentative de connexion au casque...");

// Connexion au casque
    headphones.start("OpenMove by Shokz");

  // Mettre à jour le volume pour les sons
    headphones.set_volume(50);

  // Envoi d'un son "Connected to M5Stack" pour confirmer la connexion Bluetooth
    headphones.write_data(connection);
}

void sendDanger(){
    headphones.write_data(danger);
}

void sendWarning(){
    headphones.write_data(warning);
}

void NewSoundValues()
{
    int value0, value1, value4, value5;

    for(int j = 0; j < 6; j++){
        //value0 = sensorValues[0][j];
        //value1 = sensorValues[1][j];
        //value4 = sensorValues[4][j];
        value5 = sensorValues[5][1];

        if (/*value0 < DANGER || value1 < DANGER ||*/ value5 < DANGER){ 
                M5.Lcd.print("danger");
                sendDanger();
            }

            // Envoi du son aigu avec value inférieure à 60 cm (WARNING)
            else if (/*value0 < WARNING && value0 >= DANGER || value1 < WARNING && value1 >= DANGER ||*/ value5 < WARNING && value5 >= DANGER){
                M5.Lcd.print("warning");
                sendWarning();
            }
    }
    
    
    /* for (int i = 0; i < NBBOARD; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            value = sensorValues[i][j];

            // Envoi du son aigu avec value inférieure à 30 cm (DANGER)
            
        }
    }*/
} 
