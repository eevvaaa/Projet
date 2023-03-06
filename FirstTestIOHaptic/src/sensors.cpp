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
    if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) != CAN_OK)
        return false;
    CAN0.setMode(MCP_NORMAL);
    pinMode(CAN0_INT, INPUT);
    return true;
}
void processSensors(){
    if(!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
    {
        CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
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
    if(newValues[id]){
        for(int i = 0 ; i < 6 ; i++){
            values[i] = sensorValues[id][i];
        }
        return true;
    }
    return false;
}