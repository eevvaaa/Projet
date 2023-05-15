#include <M5Stack.h>
#include <sensors.h>
#include <BluetoothSerial.h>
#include <SPIFFS.h>
#include <led.h>
#include <visuel.h>

BluetoothSerial SerialBT;

// Démarrage par défaut en Visuel Activé, autres désactivés

// mode Visuel a plusieurs états : 0 (désactivé), 1 (activé), 2 (activé + LED)
int modeVisuel = 1;

// mode Sonore a 2 états : 0 (désactivé), 1 (activé)
int modeSonore = 0;

// mode Haptique a 2 états : 0 (désactivé), 1 (activé)
int modeHaptique = 0;



// Déclaration des fonctions utilisées dans le setup

void affichageBarreBoutons();
void affichageModeVisuel();


void setup()
{
    // Init de la M5STack
    M5.begin(true, false, true, true);
    // Démarrage du SPIFFS permettant d'affichage d'image
    SPIFFS.begin();
    // Démarrage de la M5Stack
    M5.Power.begin();

    // Démarrage du Bluetooth
    SerialBT.begin("M5Stack");

    // Taille de la police 
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0,185);

    // Affichage de l'écran de démarrage
    M5.Lcd.fillScreen(0x92E8);
    M5.Lcd.drawPngFile(SPIFFS, "/logo.png", 82, 18);
    M5.Lcd.println("Bienvenue sur FREEWHEEL !");

    M5.Lcd.println("Verification module CAN...");

    // Si l'init du bus CAN a réussi, c'est-à-dire si le module CAN est bien branché :
    while(!initSensors()){
        delay(100);
    }

    M5.Lcd.println("Module CAN trouve !");

    // Attente
    delay(2300);

    // Remplissage en noir 
    M5.Lcd.fillScreen(BLACK);

    // Initialisation de l'affichage 
    affichageBarreBoutons();
    affichageModeVisuel();

    M5.Lcd.setCursor(0,0);
}

// Affiche la barre des boutons, commune à tous les modes
void affichageBarreBoutons()
{   
    // Remplacement si besoin des param. visuels
    M5.Lcd.fillRect(0,204,320,36,BLACK);
    
    // Affichage de la barre supérieure horizontale des boutons
    M5.Lcd.drawFastHLine(0,204,320,WHITE);

    // Affichage des barres verticales à 1 et 2 tiers de l'écran pour la séparation des 3 boutons
    M5.Lcd.drawFastVLine(106,204,36,WHITE);
    M5.Lcd.drawFastVLine(214,204,36,WHITE); 

    // Affichage des noms des retours aux boutons correspondants
    // x et y sont calculés pour centrer sur le bouton après tests
    M5.Lcd.drawString("Visuel",16, 214);
    
    M5.Lcd.drawString("Sonore",106 + 19,214);

    M5.Lcd.drawString("Haptique",214 + 8,214);
}


void bluetoot()
{
    if (M5.BtnB.read())
    {
        SerialBT.println("Hello world, from M5Stack - Key B!");
    }

    M5.Lcd.setCursor(0, 0);

    if (SerialBT.available())
    {
        char ch = SerialBT.read();
        if (ch == 'c')
        {
            M5.Lcd.print("Connection made with smartphone successfully !");
        }
    }
}



void ButtonCheck()
{
    // Permet d'éteindre la M5Stack, ce qui n'est pas possible sinon
    if (M5.BtnA.isPressed() && M5.BtnB.isPressed())
    {
        turnOffLEDs();
        M5.Power.deepSleep();
    }
    
    // BOUTON A
    if (M5.BtnA.wasPressed())
    {   
        // Activation mode Visuel
        if(!modeVisuel){
            modeVisuel ++;
            affichageModeVisuel();
        }else{
            // Paramètres du mode visuel
            if(modeVisuel == 1){
                modeVisuel++;
                affichageParametres();
            }else{
                // Quitter les paramètres visuels
                modeVisuel--;
                affichageBarreBoutons();
            }

        }
    }

    // BOUTON A
    if(M5.BtnB.wasPressed()){
        // Paramètres mode visuel -> changer la palette
        if(modeVisuel == 2){
            changerPalette();
        }
    }

    // Activation mode haptique OU quitter param visuels
    if(M5.BtnC.wasPressed()){
    }
    
}

void loop()
{
    M5.update();
    ButtonCheck();

    //ProcessSensor retourne bloc allant de 1 à NBBOARD si données reçues de bloc ou 0 sinon
    if (int bloc = processSensors())
    {
        // On enlève 1 car la fonction prend un entier allant de 0 à NBBOARD -1
        affichageBloc(bloc-1);
        bluetoot();
    }
        
}