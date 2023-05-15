#include <mcp_can.h>
#include <M5Stack.h>
#include <sensors.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

MCP_CAN CAN0(&SPI, 12); // Set CS to pin 12
#define CAN0_INT 15     // Set INT to pin 15


// DONNEES RELATIVES AUX CAPTEURS ------------------------------------------------

// Commencer la lecture par le capteur 0
int nextToRead = 0;

// Données sur la position des capteurs relative au centre de l'image de fauteuil
// X (de -60 à 60) ; Y (de -75 à 75) ; SensX (de + à -2) ; SensY (de + à -2)
// La largeur d'un bloc de capteurs affiché est de 22
int blocs[NBBOARD][4] = {
    // Capteurs derrière
    {14, 75, -2, 0},
    {-14, 75, -2, 0},
    // Capteurs sur roues
    {60, 25, 0, 2},
    {-60, 25, 0, -2},
    // Capteurs sur côtés devant
    {50,-35,1,2},
    {-50,-35,1,-2},
    // Capteurs devant
    {14,-75, 2, 0},
    {-14,-75, 2, 0} 
};

// Stocke les données provenant des capteurs
int sensorValues[NBBOARD][6];


// DONNEES RELATIVES AUX DISTANCES -----------------------------------------------

// Choix du type de distances LONG (0, défaut) ou COURT (1)
int d = 0;

// Limites des distances ALERTE et DANGER, pour LONG (défaut) et COURT
int limites[2][2] = {
    {60,30},
    {25,10}
};

// FONCTIONS ---------------------------------------------------------------------

// Initialise le bus CAN
bool initSensors()
{
    // si le bus CAN n'arrive pas à se lancer, alors retourner faux
    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) != CAN_OK)
        return false;

    // Fin de l'initialisation
    CAN0.setMode(MCP_NORMAL);

    // Choix de l'entrée comme étant celle de CAN0_INT
    pinMode(CAN0_INT, INPUT);

    // Init réussie
    return true;
}

// Lis les messages reçus par le bus CAN
// Retourne 0 si pas de nouvelles données
// Retourne bloc (de 1 à NBBOARD) si nouvelles données
int processSensors()
{
    // If CAN0_INT pin is low, read receive buffer
    if (!digitalRead(CAN0_INT))
    {

        // Read data: len = data length, buf = data byte(s)
        CAN0.readMsgBuf(&rxId, &len, rxBuf);

        // DEBUG
        Serial.print(rxId, HEX);
        for(int i = 0 ; i < len ; i++){
            Serial.print(rxBuf[i]);
        }    

        // Si le message est correct, continuer
        if ((rxId & 0x3F0) == 0x00)
        {
            unsigned int boardID = 0;
            // Si le message provient d'un bon board, continuer
            if ((boardID = (rxId & 0x07)) < NBBOARD /*&& boardID == nextToRead*/)
            {   
                // update les donénes du tableau
                for (int i = 0; i < 6; i++)
                {   
                    sensorValues[boardID][i] = rxBuf[i];
                }
                // Mettre à jour le prochain capteur à lire dans la liste
                //nextToRead = (nextToRead + 1) % NBBOARD;

                // Indique qu'il y a de nouvelles valeurs en boardID
                return boardID+1;
            }
        }
    }
    // Indique qu'il n'y a pas de nouvelles valeurs
    return 0;
}

