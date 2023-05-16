#ifndef LED_H
#define LED_H

void initLED();
void turnOffLEDs();
void updateLED();
void affichageLEDs(int bloc);
uint32_t getCouleurLED(int dist);
void changerModeLED();

#endif