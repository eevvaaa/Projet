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
MCP_CAN CAN0(&SPI, 12); // Set CS to pin 12
#define CAN0_INT 15     // Set INT to pin 15

//variable pour définir le prochain capteur à lire
int nextToRead;
//tableau qui contient les données des capteurs de tous les boards
int sensorValues[NBBOARD][6];

#define DANGER 30
#define WARNING 60

extern int pwmChannelDroit; 
extern int pwmChannelGauche; 
extern int pwmChannelDevant; 
extern int pwmChannelDerriere; 

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
    nextToRead = 0;

    // Init réussie
    return true;
}


void processSensorsDeux()
{
    // If CAN0_INT pin is low, read receive buffer
    if (!digitalRead(CAN0_INT))
    {

        // Read data: len = data length, buf = data byte(s)
        CAN0.readMsgBuf(&rxId, &len, rxBuf);

        // Si le message est correct, continuer
        if ((rxId & 0x3F0) == 0x00)
        {
            unsigned int boardID = rxId & 0x07;
            M5.Lcd.print(boardID);
        }
        
    }
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

void getNewSensorValues()
{
    
    int valueGauche, valueDroite, valueDevant, valueCoteGauche, valueCoteDroit, hauteur, value;
    int* valeurMoteur = new int[4]{0};

    /* moteur gauche */
    valueGauche = sensorValues[0][0];
        
    M5.Lcd.setCursor(128, 2*16);
    M5.Lcd.print(valueGauche);       

    if (valueGauche<DANGER){
        if (valeurMoteur[0]!=170){
            ledcWrite(pwmChannelGauche, 170); //1.65 V
            valeurMoteur[0]=170;
        }
    } else{
        if (valueGauche < WARNING && valueGauche >= DANGER){
            if (valeurMoteur[0]!=63){
                ledcWrite(pwmChannelGauche, 63); 
                valeurMoteur[0]=63;
            }
        } else {
            ledcWrite(pwmChannelGauche, 0); 
            valeurMoteur[0]=0;
        }
    }

    /* moteur droit */
    valueDroite = sensorValues[1][5];

    hauteur = (2 + 6 * 1 + 5) * 16;
    M5.Lcd.setCursor(128, hauteur);
    M5.Lcd.print(valueDroite);

    if (valueDroite<DANGER){
        if (valeurMoteur[2]!=170){
            ledcWrite(pwmChannelDroit, 170); 
            valeurMoteur[2]=170;
        }
    } else{
        if (valueDroite < WARNING && valueDroite >= DANGER){
            if (valeurMoteur[2]!=63){
                ledcWrite(pwmChannelDroit, 63); 
                valeurMoteur[2]=63;
            }
        } else {
            ledcWrite(pwmChannelDroit, 0); 
            valeurMoteur[2]=0;
        }
    } 

    /* moteur devant */
    for (int j = 3; j < 6; j++){
        valueDevant = sensorValues[0][j];

        hauteur = (2 + 6 * 0 + j) * 16;
        M5.Lcd.setCursor(128, hauteur);
        M5.Lcd.print(valueDevant);

        if (valueDevant<DANGER){
            if (valeurMoteur[1]!=170){
                ledcWrite(pwmChannelDevant, 170); 
                valeurMoteur[1]=170;
            }
        } else{
            if (valueDevant < WARNING && valueDevant >= DANGER){
                if (valeurMoteur[1]!=63){
                    ledcWrite(pwmChannelDevant, 63); 
                    valeurMoteur[1]=63;
                }
            } else {
                ledcWrite(pwmChannelDevant, 0); 
                valeurMoteur[1]=0;
            }
        } 
    }

    for (int j = 0; j < 3; j++){
        valueDevant = sensorValues[1][j];

        hauteur = (2 + 6 * 1 + j) * 16;
        M5.Lcd.setCursor(128, hauteur);
        M5.Lcd.print(valueDevant);

        if (valueDevant<DANGER){
            if (valeurMoteur[1]!=170){                
                ledcWrite(pwmChannelDevant, 170); 
                valeurMoteur[1]=170;
            }
        } else{
            if (valueDevant < WARNING && valueDevant >= DANGER){
                if (valeurMoteur[1]!=63){
                    ledcWrite(pwmChannelDevant, 63); 
                    valeurMoteur[1]=63;
                }
            } else {
                ledcWrite(pwmChannelDevant, 0); 
                valeurMoteur[1]=0;
            }
        } 
    }

    /* moteur devant-droit */
    for (int j = 3; j < 5; j++){
        valueCoteDroit = sensorValues[1][j];

        hauteur = (2 + 6 * 1 + j) * 16;
        M5.Lcd.setCursor(128, hauteur);
        M5.Lcd.print(valueCoteDroit);

        if (valueCoteDroit<DANGER){
            if (valeurMoteur[1]!=170 || valeurMoteur[2]!=170){
                ledcWrite(pwmChannelDevant, 170);
                valeurMoteur[1]=170;
                ledcWrite(pwmChannelDroit, 170); 
                valeurMoteur[2]=170;
            }
        } else{
            if (valueCoteDroit < WARNING && valueCoteDroit >= DANGER){
                if (valeurMoteur[1]!=63 || valeurMoteur[2]!=63){
                    ledcWrite(pwmChannelDevant, 63);
                    valeurMoteur[1]=63;
                    ledcWrite(pwmChannelDroit, 63);
                    valeurMoteur[2]=63;
                }
            } else {
                ledcWrite(pwmChannelDevant, 0);
                valeurMoteur[1]=0;
                ledcWrite(pwmChannelDroit, 0);
                valeurMoteur[2]=0;
            }
        } 
    }

     /* moteur devant-gauche */
    for (int j = 1; j < 3; j++){
        valueCoteGauche = sensorValues[0][j];

        hauteur = (2 + 6 * 0 + j) * 16;
        M5.Lcd.setCursor(128, hauteur);
        M5.Lcd.print(valueCoteGauche);

        if (valueCoteGauche<DANGER){
            if (valeurMoteur[1]!=170 || valeurMoteur[0]!=170){
                ledcWrite(pwmChannelDevant, 170);
                valeurMoteur[1]=170;
                ledcWrite(pwmChannelGauche, 170); 
                valeurMoteur[0]=170;
            }
        } else{
            if (valueCoteGauche < WARNING && valueCoteGauche >= DANGER){
                if (valeurMoteur[1]!=63 || valeurMoteur[0]!=63){
                    ledcWrite(pwmChannelDevant, 63);
                    valeurMoteur[1]=63;
                    ledcWrite(pwmChannelGauche, 63);
                    valeurMoteur[0]=63;
                }
            } else {
                ledcWrite(pwmChannelDevant, 0);
                valeurMoteur[1]=0;
                ledcWrite(pwmChannelGauche, 0);
                valeurMoteur[0]=0;
            }
        } 
    }
    
    

}