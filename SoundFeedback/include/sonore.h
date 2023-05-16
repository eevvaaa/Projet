#ifndef SONORE_H
#define SONORE_H

// Initialise la connexion Bluetooth entre la M5Stack et le casque audio
void initSonore();

// Méthode qui permet d'envoyer le son de danger 
void sendDanger();

// Méthode qui permet d'envoyer le son d'alerte
void sendWarning();

//Cette fonction est celle qui permet d'envoyer un signal sonore ou non en fonction de la proximité entre un capteur et le fauteuil roulant électrique
void NewSoundValues();

#endif 