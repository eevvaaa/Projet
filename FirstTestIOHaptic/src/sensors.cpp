#include <mcp_can.h>
#include <M5Stack.h>
#include <Arduino.h>
#include <sensors.h>


//Ensemble du message que l'on reçoit 
long unsigned int rxId; 
unsigned char len = 0;
unsigned char rxBuf[8];


//CAN0 = tout ce qui gère (bus en protocole CAN) l'ini de la M5Stack
MCP_CAN CAN0(&SPI, 12); // Set CS to pin 12
#define CAN0_INT 15     // Set INT to pin 15

//variable pour définir le prochain capteur à lire
//int nextToRead;


// Données sur la position des capteurs relative au centre de l'image de fauteuil
// X (de -60 à 60) ; Y (de -75 à 75) ; SensX (de + à -2) ; SensY (de + à -2)
// La largeur d'un bloc de capteurs affiché est de 22
int blocs[NBBOARD][4] = {
    // Capteurs derrière
    {14, 75, -2, 0}, //derrière droit
    {-14, 75, -2, 0}, //derrière gauche
    // Capteurs sur roues
    {60, 25, 0, 2}, //côté droit derrière
    {-60, 25, 0, -2}, //côté gauche derrière
    // Capteurs sur côtés devant
    {50,-35,1,2}, //côté droit devant
    {-50,-35,1,-2}, //côté gauche devant
    // Capteurs devant
    {14,-75, 2, 0}, //devant droit
    {-14,-75, 2, 0} //devant gauche
};

//tableau qui contient les données des capteurs de tous les boards
int sensorValues[NBBOARD][6];


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
    for (int i = 0; i<4; i++){
        digitalWrite(i,LOW);
    }
    // Commencer la lecture par le capteur 0
    //nextToRead = 0;

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
            if ((boardID = (rxId & 0x07)) < NBBOARD /*&& boardID == nextToRead*/)
            {
                for (int i = 0; i < 6; i++)
                {   
                    //rentre toutes les valeurs du board lu dans la matrice
                    sensorValues[boardID][i] = rxBuf[i];
                }
                // Mettre à jour le prochain capteur à lire dans la liste
                //nextToRead = (nextToRead + 1) % NBBOARD;
                return true;
            }
        }
    }
    //retourne faux si aucun capteur n'a été lu ou relu (qu'on reste sur le même board)
    return false;
}
