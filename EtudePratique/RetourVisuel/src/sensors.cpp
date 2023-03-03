#include <mcp_can.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
#define NBBOARD 2

MCP_CAN CAN0(&SPI, 12);                               // Set CS to pin 10
#define CAN0_INT 15                              // Set INT to pin 2

int sensorValues[NBBOARD][6];
bool newValues[NBBOARD];


bool initSensors(){
    // si le capteur n'arrive pas à se lancer, alors retourner faux
    if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) != CAN_OK)
        return false;
    
    // Fin de l'initialisation
    CAN0.setMode(MCP_NORMAL);

    // Choix de l'entrée comme étant celle de CAN0_INT
    pinMode(CAN0_INT, INPUT);

    //Init réussie
    return true;
}


void processSensors(){
    // If CAN0_INT pin is low, read receive buffer
    if(!digitalRead(CAN0_INT)){  

        // Read data: len = data length, buf = data byte(s)                       
        CAN0.readMsgBuf(&rxId, &len, rxBuf);      
        if((rxId & 0x3F0) == 0x00){
            unsigned int boardID = 0;
            if((boardID = (rxId & 0x07)) < NBBOARD){
                for(int i = 0 ; i < 6 ; i ++){
                    sensorValues[boardID][i] = rxBuf[i];
                    newValues[boardID] = true;
                }
            }
        }
    }
}


bool getNewSensorValues(unsigned int id, int values[6]){
    if(id >= NBBOARD) return false;
    //if(newValues[id]){
        for(int i = 0 ; i < 6 ; i++){
            values[i] = sensorValues[id][i];
        }
        return true;
    //}
    //return false;
}