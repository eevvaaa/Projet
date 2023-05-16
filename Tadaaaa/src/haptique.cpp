/* PARTIE HAPTIQUE DU PROJET */

#include <M5Stack.h>
#include <Arduino.h>
#include <sensors.h>

// DONNES RELATIVES AUX MOTEURS --------------------------------------------------

/* On définit une constante MotorPin qui sera le numéro sur lequel on branche notre module
et sensorPin pour le port des sensors */
#define moteurGauche 17
#define moteurDroit 16
#define moteurDevant 2
#define moteurDerriere 5

int pwmChannelDroit = 0;    // Choisit le canal 0-15
int pwmChannelGauche = 1;   // Choisit le canal 0-15
int pwmChannelDevant = 2;   // Choisit le canal 0-15
int pwmChannelDerriere = 3; // Choisit le canal 0-15

int frequence = 1000; // Fréquence PWM de 1 KHz
int resolution = 8;   // Résolution de 8 bits, 256 valeurs possibles

/**
 * Tableau qui permet de stocker les valeurs actuels auxquelles sont allumés nos moteurs
 * Ici, nous utilisons 4 moteurs.
 * On initialise ce tableau à 0.
 */
int *valeurMoteur = new int[4]{0};

// IMPORTS DEPUIS SENSORS --------------------------------------------------------

extern int sensorValues[NBBOARD][6];
extern int limites[2][2];
extern bool modeDistance;

// MODE SONORE------------------------------
// Initialisé à 0 (désactivé)
bool modeHaptique = 0;

// FONCTIONS ---------------------------------------------------------------------

/**
 * Cette fonction permet l'initialisation du retour haptique
 */
void initHaptique()
{
    // Configuration du canal 0 avec la fréquence et la résolution choisie
    ledcSetup(pwmChannelDroit, frequence, resolution);
    ledcSetup(pwmChannelGauche, frequence, resolution);
    ledcSetup(pwmChannelDevant, frequence, resolution);
    ledcSetup(pwmChannelDerriere, frequence, resolution);

    // Assigne le canal PWM au pin
    ledcAttachPin(moteurDroit, pwmChannelDroit);
    ledcAttachPin(moteurGauche, pwmChannelGauche);
    ledcAttachPin(moteurDevant, pwmChannelDevant);
    ledcAttachPin(moteurDerriere, pwmChannelDerriere);

    ledcWrite(pwmChannelDerriere, 0);
    ledcWrite(pwmChannelDevant, 0);
    ledcWrite(pwmChannelDroit, 0);
    ledcWrite(pwmChannelGauche, 0);
}

/**
 * Cette fonction est celle qui permet d'envoyer une vibration ou non en fonction de la proximité pour un capteur, un moteur et un channel donnés
 *
 * @param pwmChannel permet de préciser le canal utilisé pour le moteur
 * @param numMoteur permet d'indiquer quel moteur est concerné par la vibration possible d'un capteur précis
 * @param value permet d'indiquer la valeur (distance) reçue par un capteur précis
 * @param valeurMoteur permet de mettre à jour l'amplitude actuelle de vibration du moteur
 */
void testDistanceVibration(int pwmChannel, int numMoteur, int value, int *valeurMoteur)
{
    if (value < limites[modeDistance][DANGER])
    {
        if (valeurMoteur[numMoteur] != 170)
        {
            ledcWrite(pwmChannel, 170);
            valeurMoteur[numMoteur] = 170;
        }
    }
    else
    {
        if (value < limites[modeDistance][ALERTE])
        {
            if (valeurMoteur[numMoteur] != 63)
            {
                ledcWrite(pwmChannel, 63);
                valeurMoteur[numMoteur] = 63;
            }
        }
        else
        {
            ledcWrite(pwmChannel, 0);
            valeurMoteur[numMoteur] = 0;
        }
    }
}

/**
 * Cette fonction permet de faire fonctionner (position+proximité) 3 moteurs (gauche-devant-droite) en fonction de 2 boards
 */
void activationMoteurAvecCapteurs()
{
    int hauteur, value;
    int* valeurMoteur = new int[4]{0};

    /* moteur gauche */
    value = sensorValues[0][0];
        
    M5.Lcd.setCursor(80, 0*30);
    M5.Lcd.print(value);       

    testDistanceVibration(pwmChannelGauche, 0, value, valeurMoteur);

    /* moteur droit */
    value = sensorValues[1][5];

    M5.Lcd.setCursor(130, 5*30);
    M5.Lcd.print(value);       

    testDistanceVibration(pwmChannelDroit, 2, value, valeurMoteur);

    /* moteur devant */
    for (int j = 3; j < 6; j++){
        value = sensorValues[0][j];
    
        M5.Lcd.setCursor(80, j*30);
        M5.Lcd.print(value);       

        testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
    }

    for (int j = 0; j < 3; j++){
        value = sensorValues[1][j];

        M5.Lcd.setCursor(130, j*30);
        M5.Lcd.print(value);

        testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
    }

    /* moteur devant-droit */
    for (int j = 3; j < 5; j++){
        value = sensorValues[1][j];

        M5.Lcd.setCursor(130, j*30);
        M5.Lcd.print(value);

        testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
        testDistanceVibration(pwmChannelDroit, 2, value, valeurMoteur);

    }

     /* moteur devant-gauche */
    for (int j = 1; j < 3; j++){
        value = sensorValues[0][j];

        
        M5.Lcd.setCursor(80, j*30);
        M5.Lcd.print(value);       

        testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
        testDistanceVibration(pwmChannelGauche, 0, value, valeurMoteur);    
    }
    
    
}

/**
 * Cette fonction permet de tester individuellement si les blocs/boards de capteurs fonctionnent.
 * On écrit les valeurs des capteurs du bloc testé sur la M5stack pour plus de lisibilité.
 *
 * i correspond au numéro du bloc, j correspond aux numéros des 6 capteurs sur le bloc testé
 * en fonction de i, ajuster le moteur correspondant, soit les deux premiers paramètres de testDistanceVibration
 */
void testBoard(int boardATester)
{
    int value;
    for(int j=0; j<6; j++){
        M5.Lcd.setCursor(20,j*30);
        M5.Lcd.printf("[%d][%d] : ", boardATester, j);
        value = sensorValues[boardATester][j];
        M5.Lcd.print(value);
    }
    
}

/**
 * Cette fonction permet de tester individuellement si les capteurs fonctionnent.
 * On écrit la valeur du capteur testé sur la M5stack pour plus de lisibilité.
 *
 * i correspond au numéro du bloc, j correspond au numéro du capteur testé sur le bloc
 * en fonction de i, ajuster le moteur correspondant, soit les deux premiers paramètres de testDistanceVibration
 */
void testCapteurIndiv(int board, int capteur)
{
    int value;
    M5.Lcd.setCursor(20,80);
    M5.Lcd.printf("[%d][%d] : ", board, capteur);
    value = sensorValues[board][capteur];
    M5.Lcd.print(value);

}


/**
 * Cette fonction permet de tester le retour haptique sur le fauteuil complet, en prenant en compte 8 blocs de 6 capteurs
 */
void activationMoteurFauteuilComplet()
{

    int value;

    /* Activation du moteur derrière */
    /* arrière board 0 */
    for (int j = 0; j < 6; j++)
    {
        value = sensorValues[0][j];
        testDistanceVibration(pwmChannelDerriere, 3, value, valeurMoteur);
        if (j < 3)
        {
            testDistanceVibration(pwmChannelDroit, 2, value, valeurMoteur);
        }
    }
    /* arrière board 1*/
    for (int j = 0; j < 6; j++)
    {
        value = sensorValues[1][j];
        testDistanceVibration(pwmChannelDerriere, 3, value, valeurMoteur);
        if (j >= 3)
        {
            testDistanceVibration(pwmChannelGauche, 0, value, valeurMoteur);
        }
    }

    /* Activation du moteur devant */
    /* devant board 7 */
    for (int j = 0; j < 6; j++)
    {
        value = sensorValues[7][j];
        testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
        if (j < 3)
        {
            testDistanceVibration(pwmChannelGauche, 0, value, valeurMoteur);
        }
    }
    /* devant board 6 */
    for (int j = 0; j < 6; j++)
    {
        value = sensorValues[6][j];
        testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
        if (j >= 3)
        {
            testDistanceVibration(pwmChannelDroit, 2, value, valeurMoteur);
        }
    }

    /* Activation du moteur droit */
    /* droit board 4 */
    for (int j = 0; j < 6; j++)
    {
        value = sensorValues[4][j];
        testDistanceVibration(pwmChannelDroit, 2, value, valeurMoteur);
        if (j < 3)
        {
            testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
        }
    }
    /* droit board 2*/
    for (int j = 0; j < 6; j++)
    {
        value = sensorValues[2][j];
        testDistanceVibration(pwmChannelDroit, 2, value, valeurMoteur);
        if (j >= 3)
        {
            testDistanceVibration(pwmChannelDerriere, 3, value, valeurMoteur);
        }
    }

    /* Activation du moteur gauche */
    /* gauche board 3*/
    for (int j = 0; j < 6; j++)
    {
        value = sensorValues[3][j];
        testDistanceVibration(pwmChannelGauche, 0, value, valeurMoteur);
        if (j < 3)
        {
            testDistanceVibration(pwmChannelDerriere, 3, value, valeurMoteur);
        }
    }
    /* gauche board 5 */
    for (int j = 0; j < 6; j++)
    {
        value = sensorValues[5][j];
        testDistanceVibration(pwmChannelGauche, 0, value, valeurMoteur);
        if (j >= 3)
        {
            testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
        }
    }
}

/**
 * Cette fonction permet de tester le retour haptique sur le fauteuil complet mais en utilisant seulement les capteurs (individuels) qui renvoie une valeur exploitable.
 */
void activationMoteursCapteursOKFauteuil()
{

    int value;

    /* Activation du moteur derrière */
    /* arrière board 0*/
    for (int j = 0; j < 6; j++){
        value = sensorValues[0][j];
        testDistanceVibration(pwmChannelDerriere, 3, value, valeurMoteur);
        if (j<3){
            testDistanceVibration(pwmChannelDroit, 2, value, valeurMoteur);
        }
    }
    /* arrière board 1 --> seul le capteur 5 marche*/
    for (int j = 0; j < 6; j++){
        value = sensorValues[1][j];
        testDistanceVibration(pwmChannelDerriere, 3, value, valeurMoteur);
        if (j>=3){
            testDistanceVibration(pwmChannelGauche, 0, value, valeurMoteur);
        }
    }

    /* Activation du moteur devant */
    /* devant board 7 --> seul le capteur 5 marche*/
    for (int j = 0; j < 6; j++){
        value = sensorValues[7][j];
        testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
        if (j<3){
            testDistanceVibration(pwmChannelGauche, 0, value, valeurMoteur);
        }
    }
    /* devant board 6 --> seul le capteur 0 marche */
    for (int j = 0; j < 6; j++){
        value = sensorValues[6][j];
        testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
        if (j>=3){
            testDistanceVibration(pwmChannelDroit, 2, value, valeurMoteur);
        }
    }

    /* Activation du moteur droit */
    /* droit board 4 */
    for (int j = 0; j < 6; j++){
        value = sensorValues[4][j];
        testDistanceVibration(pwmChannelDroit, 2, value, valeurMoteur);
        if (j<3){
            testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
        }
    }  

    /* droit board 2 --> rien ne marche*/

    /* Activation du moteur gauche */
    /* gauche board 3 --> toujours au max donc on n'active pas*/
    /* gauche board 5 --> toujours au max donc on n'active pas*/

}

// Permet d'activer ou désactiver le mode haptique
void changerModeHaptique()
{
    // Alterne entre les modes
    modeHaptique = !modeHaptique;
}