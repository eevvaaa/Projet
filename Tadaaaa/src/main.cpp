#include <M5Stack.h>
#include <sensors.h>
#include <BluetoothSerial.h>
#include <SPIFFS.h>
#include <led.h>
#include <visuel.h>
#include <sonore.h>
#include <haptique.h>
#include <interface.h>


// ACTIVATION OU NON DES DIFFERENTS MODES ----------------------------------------

// Démarrage par défaut en Visuel Activé, autres désactivés

// ENSEMBLE DES MODES
extern bool modeVisuelEcran;
extern bool modeLED;
extern bool modeSonore;
extern bool modeHaptique;
//-------------------


// Déclaration des fonctions utilisées dans le setup

void affichageBoutons();
void changerAffichageModeVisuel();

void setup()
{
    // Init de la M5STack
    M5.begin(true, false, true, true);
    // Démarrage du SPIFFS permettant d'affichage d'image
    SPIFFS.begin();
    // Démarrage de la M5Stack
    M5.Power.begin();

    // Taille de la police
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 185);

    // Affichage de l'écran de démarrage
    M5.Lcd.fillScreen(0x92E8);
    M5.Lcd.drawPngFile(SPIFFS, "/logo.png", 82, 18);
    M5.Lcd.println("Bienvenue sur FREEWHEEL !");

    M5.Lcd.println("Verification module CAN...");

    // Si l'init du bus CAN a réussi, c'est-à-dire si le module CAN est bien branché :
    while (!initSensors())
    {
        delay(100);
    }

    M5.Lcd.println("Module CAN trouve !");

    // Attente
    delay(1800);

    // Remplissage en noir
    M5.Lcd.fillScreen(BLACK);

    // Initialisation de l'affichage
    affichageBoutons();

    // INITIALISATION DE TOUS LES RETOURS
    // RETOUR VISUEL
    changerAffichageModeVisuel();
    initLED();
    affichageDistances(true);

    // RETOUR SONORE
    initSonore();

    // RETOUR HAPTIQUE 
    initHaptique();

    // RETOUR PAR APPLICATION -> Bluetooth
    initBluetoot();

    M5.Lcd.setCursor(0, 0);
}


void loop()
{
    // Vérification des boutons de la M5Stack
    buttonCheck();

    // ProcessSensor retourne bloc allant de 1 à NBBOARD si données reçues de bloc ou 0 sinon
    if (int bloc = processSensors())
    {
        // RETOUR VISUEL SUR ECRAN ET SUR LED
        if (modeVisuelEcran)
        {
            affichageBloc(bloc - 1);
            // On enlève 1 car la fonction prend un entier allant de 0 à NBBOARD -1
        }
        if (modeLED)
        {
            affichageLEDs(bloc - 1);
        }

        // RETOUR SONORE
        if (modeSonore)
        {
            retourSonore();
        }

        // RETOUR HAPTIQUE
        if (modeHaptique)
        {
            // activationMoteurAvecCapteurs();
            testAutomatiqueHaptique();
            delay(100000);
            // activationMoteurFauteuilComplet();
        }

        //Cette fonction gère les échanges bluetooth avec l'appli
        bluetoot();
    }
}