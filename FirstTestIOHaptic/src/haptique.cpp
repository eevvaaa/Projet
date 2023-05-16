#include <M5Stack.h>
#include <Arduino.h>
#include <sensors.h>

extern int pwmChannelDroit; 
extern int pwmChannelGauche; 
extern int pwmChannelDevant; 
extern int pwmChannelDerriere; 

extern int sensorValues[NBBOARD][6];

/**
 * Tableau qui permet de stocker les valeurs actuels auxquelles sont allumés nos moteurs
 * Ici, nous utilisons 4 moteurs.
 * On initialise ce tableau à 0. 
*/
int* valeurMoteur = new int[4]{0};


/**
 * Cette fonction est celle qui permet d'envoyer une vibration ou non en fonction de la proximité pour un capteur, un moteur et un channel donnés
 * 
 * @param pwmChannel permet de préciser le canal utilisé pour le moteur
 * @param numMoteur permet d'indiquer quel moteur est concerné par la vibration possible d'un capteur précis
 * @param value permet d'indiquer la valeur (distance) reçue par un capteur précis
 * @param valeurMoteur permet de mettre à jour l'amplitude actuelle de vibration du moteur
*/
void testDistanceVibration(int pwmChannel, int numMoteur, int value, int* valeurMoteur){
        if (value<DANGER){
            if (valeurMoteur[numMoteur]!=170){
                ledcWrite(pwmChannel, 170); 
                valeurMoteur[numMoteur]=170;
            }
        } else{
            if (value < WARNING){
                if (valeurMoteur[numMoteur]!=63){
                    ledcWrite(pwmChannel, 63); 
                    valeurMoteur[numMoteur]=63;
                }
            } else {
                ledcWrite(pwmChannel, 0); 
                valeurMoteur[numMoteur]=0;
            }
        } 
}


/** 
 * Cette fonction permet de faire fonctionner (position+proximité) 3 moteurs (gauche-devant-droite) en fonction de 2 boards
*/
void activationMoteurAvecCapteurs(){
    
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
        testDistanceVibration(pwmChannelGauche, 0, value, valeurMoteur);    }
    
    
}

/**
 * Cette fonction permet de tester individuellement si les blocs/boards de capteurs fonctionnent.
 * On écrit les valeurs des capteurs du bloc testé sur la M5stack pour plus de lisibilité.
 * 
 * i correspond au numéro du bloc, j correspond aux numéros des 6 capteurs sur le bloc testé
 * en fonction de i, ajuster le moteur correspondant, soit les deux premiers paramètres de testDistanceVibration
*/
void testBoard(){
    int hauteur, value;
    int i=6;

    for (int j = 0; j < 6; j++){
        value = sensorValues[i][j];

        hauteur = (2 + 6 * i + j) * 16;
        M5.Lcd.setCursor(128, hauteur);
        M5.Lcd.print(value);

        testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
    }

    // BOARD 0 seul le capteur 0 en parteant de la gauche marche
    // BOARD 1 seul le plus à gauche (gauche-arrière) marche le reste vibre très très faiblement
    // BOARD 2 il est au max tout le temps 
    // BOARD 3 au max tout le temps 
    // BOARD 4 seul le plus vers le derrière capte (0 ?)
    // BOARD 5 au max tout le temps
    // BOARD 6 seul le 0 marche ( le plus à gauche sur la board de droite)
    // BOARD 7 gauche : seul le plus à droite marche (le 0 ?)
}

/**
 * Cette fonction permet de tester individuellement si les capteurs fonctionnent.
 * On écrit la valeur du capteur testé sur la M5stack pour plus de lisibilité.
 * 
 * i correspond au numéro du bloc, j correspond au numéro du capteur testé sur le bloc
 * en fonction de i, ajuster le moteur correspondant, soit les deux premiers paramètres de testDistanceVibration
*/
void testCapteur(){
    int hauteur, value;
    int i=6;
    int j=0;

    value = sensorValues[i][j];

    hauteur = (2 + 6 * i + j) * 16;
    M5.Lcd.setCursor(128, hauteur);
    M5.Lcd.print(value);

    testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);

    //[7][0] ok à activer pour devant et gauche
    //[7][1-5] OSError: [Errno 71] Protocol error
}

/**
 * Permet de noter les numéros des capteurs qui fonctionnent 
*/
void testCapteurRapide(int i){
    int value;
    for(int j=0; j<6; j++){
        M5.Lcd.setCursor(20,j*30);
        M5.Lcd.printf("[%d][%d] : ", i, j);
        value = sensorValues[i][j];
        M5.Lcd.print(value);
    }
    
}

/**
 * Permet de noter les numéros des capteurs qui fonctionnent 
*/
void testCapteurRapideIndiv(int i, int j){
    int value;
    M5.Lcd.setCursor(20,80);
    M5.Lcd.printf("[%d][%d] : ", i, j);
    value = sensorValues[i][j];
    M5.Lcd.print(value);

}


/**
 * Cette fonction permet de tester le retour haptique sur le fauteuil complet, en prenant en compte 8 blocs de 6 capteurs
*/
void activationMoteurFauteuilComplet(){

    int value;

    /* Activation du moteur derrière */
    /* arrière board 0 */
    for (int j = 0; j < 6; j++){
        value = sensorValues[0][j];
        testDistanceVibration(pwmChannelDerriere, 3, value, valeurMoteur);
        if (j<3){
            testDistanceVibration(pwmChannelDroit, 2, value, valeurMoteur);
        }
    }
    /* arrière board 1*/
    for (int j = 0; j < 6; j++){
        value = sensorValues[1][j];
        testDistanceVibration(pwmChannelDerriere, 3, value, valeurMoteur);
        if (j>=3){
            testDistanceVibration(pwmChannelGauche, 0, value, valeurMoteur);
        }
    }

    /* Activation du moteur devant */
    /* devant board 7 */
    for (int j = 0; j < 6; j++){
        value = sensorValues[7][j];
        testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
        if (j<3){
            testDistanceVibration(pwmChannelGauche, 0, value, valeurMoteur);
        }
    }
    /* devant board 6 */
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
    /* droit board 2*/
    for (int j = 0; j < 6; j++){
        value = sensorValues[2][j];
        testDistanceVibration(pwmChannelDroit, 2, value, valeurMoteur);
        if (j>=3){
            testDistanceVibration(pwmChannelDerriere, 3, value, valeurMoteur);
        }
    }

    /* Activation du moteur gauche */
    /* gauche board 3*/
    for (int j = 0; j < 6; j++){
        value = sensorValues[3][j];
        testDistanceVibration(pwmChannelGauche, 0, value, valeurMoteur);
        if (j<3){
            testDistanceVibration(pwmChannelDerriere, 3, value, valeurMoteur);
        }
    }
    /* gauche board 5 */
    for (int j = 0; j < 6; j++){
        value = sensorValues[5][j];
        testDistanceVibration(pwmChannelGauche, 0, value, valeurMoteur);
        if (j>=3){
            testDistanceVibration(pwmChannelDevant, 1, value, valeurMoteur);
        }
    }
}

/**
 * Cette fonction permet de tester le retour haptique sur le fauteuil complet mais en utilisant seulement les capteurs (individuels) qui renvoie une valeur exploitable. 
*/
void activationMoteursCapteursOKFauteuil(){

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