#include <Arduino.h>
#include <M5Stack.h>
#include "BluetoothA2DPSource.h"
#include "BluetoothA2DPCommon.h"
#include "sonore.h"
#include "sensors.h"

BluetoothA2DPSource a2dp_source;

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

// Connexion au casque grâce à son nom
    a2dp_source.start("OpenMove by Shokz");

// Mettre à jour le volume pour les sons
    a2dp_source.set_volume(50);

// Envoi d'un son "Connected to M5Stack" pour confirmer la connexion Bluetooth
    a2dp_source.write_data(connection);
}


// Méthode qui permet d'envoyer le son de danger 
void sendDanger(){
    a2dp_source.write_data(danger);
}

// Méthode qui permet d'envoyer le son d'alerte
void sendWarning(){
    a2dp_source.write_data(warning);
}

/**
 * Cette fonction est celle qui permet d'envoyer un signal sonore ou non en fonction de la proximité entre un capteur et un bloc de capteurs
 * 
 * @param value permet d'indiquer la valeur (distance) reçue par un capteur précis
*/
void NewSoundValues1Board()
{
    int value;

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 6; j++){
            value = sensorValues[i][j];
            
            // Envoi du son aigu avec value inférieure à 30 cm (DANGER)
            if (value < DANGER){ 
                    sendDanger();
            }

            // Envoi du son aigu avec value inférieure à 60 cm (WARNING)
            else if (value < WARNING && value >= DANGER){
                sendWarning();
                }
        }
    }
    
/**
 * Cette fonction est celle qui permet d'envoyer un signal sonore ou non en fonction de la proximité entre un capteur et le fauteuil roulant électrique
 * 
 * @param value permet d'indiquer la valeur (distance) reçue par un capteur précis
*/
void NewSoundValues()
{
    int value;

    for(int i = 0; i < NBBOARD; i++){
        for(int j = 0; j < 6; j++){
            value = sensorValues[i][j];
            
            // Envoi du son aigu avec value inférieure à 30 cm (DANGER)
            if (value < DANGER){ 
                    sendDanger();
            }

            // Envoi du son aigu avec value inférieure à 60 cm (WARNING)
            else if (value < WARNING && value >= DANGER){
                sendWarning();
                }
        }
    }
