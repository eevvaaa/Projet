#include <M5Stack.h>
#include <sensors.h>
#include <BluetoothSerial.h>
#include <SoftwareSerial.h>

#define LIMITE_DANGER 30
#define LIMITE_WARNING 60

SoftwareSerial BTSerial(2,3); // 2 et 3 : broches de la carte Arduino
BluetoothSerial SerialBT;
int mode;

void setup(){
    SerialBT.begin("M5Stack");
    Serial.begin(9600); //vitesse : 9600 bauds
    BTSerial.begin(9600);
    pinMode(9,OUTPUT); // mettre la bonne broche
}

void bluetooth(){
    if (BTSerial.available()) { // Le casque émet déjà un son quand on le connecte donc pas utile je pense
        char command = BTSerial.read();
        if (command == 's') { // si la commande reçue est 's'
        tone(9, 1000); // émettre un signal sonore à 1 kHz
        delay(500); // attendre 500 millisecondes
        noTone(9); // arrêter le signal sonore
        }
    }
}

void loop(){
    M5.update();
    if(mode == 0){
        bluetooth();
    }
    processSensors(); //On récupère les données des capteurs
    for(int i = 0 ; i<2 ; i++){ //i : numéro de la trame
        int values[6];
        if(getNewSensorValues(i,values)){
            for(int j = 0 ; j < 6 ; j++){ //j : différents capteurs sur la barre
                if(values[j]<=LIMITE_DANGER){ //Emettre un son en continu
                    tone(9, 1000) //envoyer le son, broche 9, fréquence 1000Hz
                    break; //car dès qu'il y a un capteur trop proche, on envoie le son, quelque soit le capteur
                }

                else if(values[j]<=LIMITE_WARNING && values[j]>LIMITE_DANGER){ //Emettre un bip sonore pas en continu
                    tone(9, 1000); //Fréquence de 1000 Hz mais à déterminer
                    delay(500); //On émet le son 500 ms
                    noTone(9); //On arrête le son 
                    break;
                }
            }
        }
    }
}