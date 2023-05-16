#ifndef SENSORS_H
#define SENSORS_H

bool initSensors();
int processSensors();

// Nombre de blocs sur le fauteuil
#define NBBOARD 8

// Pour les limites (limites[d][DANGER] par exemple récupère la distance de danger)
#define ALERTE 0
#define DANGER 1

#endif