#ifndef SENSORS_H
#define SENSORS_H

bool initSensors();
bool processSensors();

//NBOARD = le nombre de barres de capteurs
#define NBBOARD 8

// Distances de danger (danger) et d'alerte (warning)
#define DANGER 30
#define WARNING 60

#endif