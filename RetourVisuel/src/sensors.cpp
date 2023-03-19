#include <mcp_can.h>
#include <M5Stack.h>
#include <led.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
#define NBBOARD 2

MCP_CAN CAN0(&SPI, 12); // Set CS to pin 10
#define CAN0_INT 15     // Set INT to pin 2

int nextToRead;
int sensorValues[NBBOARD][6];
bool newValues[NBBOARD];

#define LIMITE_DANGER 20
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
        CAN0.readMsgBuf(&rxId, &len, rxBuf);
        if ((rxId & 0x3F0) == 0x00)
        {
            unsigned int boardID = 0;
            if ((boardID = (rxId & 0x07)) < NBBOARD && boardID == nextToRead)
            {
                for (int i = 0; i < 6; i++)
                {   
                    sensorValues[boardID][i] = rxBuf[i];
                }
                // Mettre à jour le prochain capteur à lire dans la liste
                nextToRead = (nextToRead + 1) % NBBOARD;
                return true;
            }
        }
    }
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
            hauteur = (2 + 6 * i + j) * 16;
            M5.Lcd.setCursor(128, hauteur);

            // s'il y a update des données, alors traiter le tableau du demi capteur
            // M5.Lcd.fillRect(130,hauteur+8,24,16,BLACK);
            M5.Lcd.print(value);

            // Affichage du carré représenté par le capteur
            if (value < LIMITE_DANGER)
            {
                M5.Lcd.fillRect(220 - 10 * (i + j == 0 || i + j == 6), hauteur + 2, 5, 5, RED);
                LEDLight(i*6+j,0);
            }
            else
            {
                if (value < LIMITE_WARNING && value >= LIMITE_DANGER)
                {
                    M5.Lcd.fillRect(220 - 10 * (i + j == 0 || i + j == 6), hauteur + 2, 5, 5, YELLOW);
                    LEDLight(i*6+j,1);
                }
                else
                {
                    M5.Lcd.fillRect(220 - 10 * (i + j == 0 || i + j == 6), hauteur + 2, 5, 5, DARKCYAN);
                    LEDLight(i*6+j,2);
                }
            }

            // Envoi des infos du capteur 0 en bluetooth
            if (i == 0 && j == 0)
            {
                // SerialBT.printf("%d\n",values[j]);
            }
        }
    }
}