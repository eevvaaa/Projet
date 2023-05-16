#ifndef SENSORS_H
#define SENSORS_H

bool initSensors();
bool processSensors();
void getNewSensorValues();

#define NBBOARD 8

#define DANGER 30
#define WARNING 60

#endif