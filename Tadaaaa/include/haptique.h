#ifndef HAPTIQUE_H
#define HAPTIQUE_H

//fonctions de test 
void testBoard();
void testCapteurHaptique();
void testAutomatiqueHaptique();

// Initialisation
void initHaptique(); 

//activation des moteurs avec 2 blocs/boards de capteurs
void activationMoteurAvecCapteurs();

//activation des moteurs avec le fauteuil, utilisation d'une fonction test pour envoyer ou non la vibration
void testDistanceVibration(int pwmChannel, int numMoteur, int value, int* valeurMoteur);
void activationMoteurFauteuilComplet();
void activationMoteursCapteursOKFauteuil();

#endif