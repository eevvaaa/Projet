#include <Arduino.h>
#include <M5Stack.h>
#include "BluetoothA2DPSource.h"
#include "BluetoothA2DPCommon.h"
#include "sonore.h"

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

void initSonore(){
    M5.Lcd.println("Bonjour, bienvenue dans le mode sonore");

    M5.Lcd.println("Tentative de connexion au casque...");

// Connexion au casque
    headphones.start("OpenMove by Shokz");

  // Mettre à jour le volume pour les sons
    headphones.set_volume(50);

  // Envoi d'un son pour confirmer la connexion Bluetooth
    headphones.write_data(connection);
}

void sendDanger(){
    headphones.write_data(danger);
}

void sendWarning(){
    headphones.write_data(warning);
}
