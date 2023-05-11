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

#define LIMITE_DANGER 30
#define LIMITE_WARNING 60

bool initSensors()
{
    // si le bus CAN n'arrive pas à se lancer, alors retourner faux
    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) != CAN_OK)
        return false;

    // Fin de l'initialisation
    CAN0.setMode(MCP_NORMAL);

    // Choix de l'entrée comme étant celle de CAN0_INT
    pinMode(CAN0_INT, INPUT);

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
    int value, hauteur;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            value = sensorValues[i][j];

            // affichage des distances aux capteurs
            hauteur = (2 + 6 * i + j) * 16;
            M5.Lcd.setCursor(128, hauteur);
            // s'il y a update des données, alors traiter le tableau du demi capteur
            // M5.Lcd.fillRect(130,hauteur+8,24,16,BLACK);
            M5.Lcd.print(value);

            // Affichage du carré représenté par le capteur
            if (value < LIMITE_DANGER && !(analogRead(j)==255)){ 
                analogWrite(j, 255);
            }
            else
            {
                if (value < LIMITE_WARNING && value >= LIMITE_DANGER)
                {
                    analogWrite(j, 127);
                }
                else
                {
                    analogWrite(j, 0);
                }
            }

        }
    }
}