#include <mcp_can.h>
#include <M5Stack.h>
#include <Arduino.h>

//Ensemble du message que l'on reçoit 
long unsigned int rxId; 
unsigned char len = 0;
unsigned char rxBuf[8];

//NBOARD = le nombre de barres de capteurs dans 1 barre de capteurs
#define NBBOARD 2

//CAN0 = tout ce qui gère (bus en protocole CAN) l'ini de la M5Stack
MCP_CAN CAN0(&SPI, 12); // Set CS to pin 10
#define CAN0_INT 15     // Set INT to pin 2

//variable pour définir le prochain capteur à lire
int nextToRead;
//tableau qui contient les données des capteurs de tous les boards
int sensorValues[NBBOARD][6];

#define DANGER 30
#define WARNING 60

#define moteurGauche 17
#define moteurDroit 25
#define moteurDevant 2
#define moteurDerriere 5


bool initSensors()
{
    // si le bus CAN n'arrive pas à se lancer, alors retourner faux
    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) != CAN_OK)
        return false;

    // Fin de l'initialisation
    CAN0.setMode(MCP_NORMAL);

    // Choix de l'entrée comme étant celle de CAN0_INT
    pinMode(CAN0_INT, INPUT);

    // On initialise tous les moteurs à LOW
    for (int i = 0; i<8; i++){
        digitalWrite(i,LOW);
    }
    // Commencer la lecture par le capteur 0
    nextToRead = 0;

    // Init réussie
    return true;
}

bool processSensors()
{
    // If CAN0_INT pin is low, read receive buffer
    if (!digitalRead(CAN0_INT))
    {

        // Read data: len = data length, buf = data byte(s)
        //reception du message
        CAN0.readMsgBuf(&rxId, &len, rxBuf);
        //RxId vérifie si le message est valide
        if ((rxId & 0x3F0) == 0x00)
        {
            //on initialise à 0 le board sur lequel on est 
            unsigned int boardID = 0;
            //RxId récupère le n° de port, qui doit être inférieur au nombre de board 
            //et égal au nextToRead pour ne pas ré-afficher le même
            if ((boardID = (rxId & 0x07)) < NBBOARD && boardID == nextToRead)
            {
                for (int i = 0; i < 6; i++)
                {   
                    //rentre toutes les valeurs du board lu dans la matrice
                    sensorValues[boardID][i] = rxBuf[i];
                }
                // Mettre à jour le prochain capteur à lire dans la liste
                nextToRead = (nextToRead + 1) % NBBOARD;
                return true;
            }
        }
    }
    //retourne faux si aucun capteur n'a été lu ou relu (qu'on reste sur le même board)
    return false;
}

void getNewSensorValues()
{
    int valueGauche, valueDroite, valueDevant, valueCoteGauche, valueCoteDroit;
    int* valeurMoteur = new int[4]{0};

    /* moteur gauche */
    valueGauche = sensorValues[0][0];
    if (valueGauche<DANGER){
        if (valeurMoteur[0]!=255){
            dacWrite(moteurGauche,255);
            valeurMoteur[0]=255;
        }
    } else{
        if (valueGauche < WARNING && valueGauche >= DANGER){
            if (valeurMoteur[0]!=127){
                dacWrite(moteurGauche, 127);
                valeurMoteur[0]=127;
            }
        } else {
            dacWrite(moteurGauche, 0);
            valeurMoteur[0]=0;
        }
    }

    /* moteur droit */
    valueDroite = sensorValues[1][5];
    if (valueDroite<DANGER){
        if (valeurMoteur[2]!=255){
            dacWrite(moteurDroit,255);
            valeurMoteur[2]=255;
        }
    } else{
        if (valueDroite < WARNING && valueDroite >= DANGER){
            if (valeurMoteur[2]!=127){
                dacWrite(moteurDroit, 127);
                valeurMoteur[2]=127;
            }
        } else {
            dacWrite(moteurDroit, 0);
            valeurMoteur[2]=0;
        }
    } 

    /* moteur devant */
    for (int j = 3; j < 6; j++){
        valueDevant = sensorValues[0][j];
        if (valueDevant<DANGER){
            if (valeurMoteur[1]!=255){
                dacWrite(moteurDevant,255);
                valeurMoteur[1]=255;
            }
        } else{
            if (valueDevant < WARNING && valueDevant >= DANGER){
                if (valeurMoteur[1]!=127){
                    dacWrite(moteurDevant, 127);
                    valeurMoteur[1]=127;
                }
            } else {
                dacWrite(moteurDevant, 0);
                valeurMoteur[1]=0;
            }
        } 
    }

    for (int j = 0; j < 3; j++){
        valueDevant = sensorValues[1][j];
        if (valueDevant<DANGER){
            if (valeurMoteur[1]!=255){
                dacWrite(moteurDevant,255);
                valeurMoteur[1]=255;
            }
        } else{
            if (valueDevant < WARNING && valueDevant >= DANGER){
                if (valeurMoteur[1]!=127){
                    dacWrite(moteurDevant, 127);
                    valeurMoteur[1]=127;
                }
            } else {
                dacWrite(moteurDevant, 0);
                valeurMoteur[1]=0;
            }
        } 
    }

    /* moteur devant-droit */
    for (int j = 3; j < 5; j++){
        valueCoteDroit = sensorValues[1][j];
        if (valueCoteDroit<DANGER){
            if (valeurMoteur[1]!=255){
                dacWrite(moteurDevant,255);
                valeurMoteur[1]=255;
                if (valeurMoteur[2]!=255){
                    dacWrite(moteurDroit, 255);
                    valeurMoteur[2]=255;
                }
            }
        } else{
            if (valueCoteDroit < WARNING && valueCoteDroit >= DANGER){
                if (valeurMoteur[1]!=127){
                    dacWrite(moteurDevant, 127);
                    valeurMoteur[1]=127;
                    if (valeurMoteur[2]!=127){
                        dacWrite(moteurDroit, 127);
                        valeurMoteur[2]=127;
                    }
                }
            } else {
                dacWrite(moteurDevant, 0);
                valeurMoteur[1]=0;
                dacWrite(moteurDroit, 0);
                valeurMoteur[2]=0;
            }
        } 
    }

     /* moteur devant-gauche */
    for (int j = 1; j < 3; j++){
        valueCoteGauche = sensorValues[0][j];
        if (valueCoteGauche<DANGER){
            if (valeurMoteur[1]!=255){
                dacWrite(moteurDevant,255);
                valeurMoteur[1]=255;
                if (valeurMoteur[0]!=255){
                    dacWrite(moteurGauche, 255);
                    valeurMoteur[0]=255;
                }
            }
        } else{
            if (valueCoteGauche < WARNING && valueCoteGauche >= DANGER){
                if (valeurMoteur[1]!=127){
                    dacWrite(moteurDevant, 127);
                    valeurMoteur[1]=127;
                    if (valeurMoteur[0]!=127){
                        dacWrite(moteurGauche, 127);
                        valeurMoteur[0]=127;
                    }
                }
            } else {
                dacWrite(moteurDevant, 0);
                valeurMoteur[1]=0;
                dacWrite(moteurGauche, 0);
                valeurMoteur[0]=0;
            }
        } 
    }
    


}