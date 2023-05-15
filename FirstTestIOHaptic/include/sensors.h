#ifndef SENSORS_H
#define SENSORS_H

bool initSensors();
bool processSensors();

//NBOARD = le nombre de barres de capteurs dans 1 barre de capteurs
#define NBBOARD 8

#define DANGER 30
#define WARNING 60

#endif