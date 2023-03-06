#ifndef SENSORS_H
#define SENSORS_H

bool initSensors();
void processSensors();
bool getNewSensorValues(unsigned int id, int values[6]);

#endif