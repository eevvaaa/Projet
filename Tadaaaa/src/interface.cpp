// Ce fichier gère l'affichage et l'interface sur la M5Stack
// Boutons, Visuels, Bluetooth avec application...

#include <M5Stack.h>
#include <led.h>
#include <visuel.h>
#include <sonore.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

// IMPORTS -----------------------------------------------------------------------
extern bool modeVisuelEcran;
extern bool modeHaptique;
extern bool modeSonore;

extern bool modeDistance;
extern int limites[2][2];

// MODE PARAMETRE --------------------------
// Permet de savoir si les paramètres sont affichés ou non
bool paramVisuels = 0;

// FONCTIONS D'AFFICHAGE ---------------------------------------------------------

// Cette fonction vérifie à chaque loop l'état des boutons de la M5Stack

//Affichage texte boutons
void affichageTexteBoutons(){
    if(!paramVisuels){
        // Affichage des noms des retours aux boutons correspondants
        // x et y sont calculés pour centrer sur le bouton après tests
        M5.Lcd.drawString("Visuel", 16, 214);
        M5.Lcd.drawString("Sonore", 106 + 19, 214);
        M5.Lcd.drawString("Haptique", 214 + 8, 214);
        M5.Lcd.drawString("Distances", 214 + 4, 178);
    }else{
        // Permet d'afficher les paramètres sur le côté
        // Remplace les boutons classiques Vis/Son/Hapt
        M5.Lcd.drawString("Quitter", 12, 214);
        M5.Lcd.drawString("Palette", 106 + 14, 214);
        M5.Lcd.drawString("LEDs", 214 + 30, 214);
        M5.Lcd.drawString("Visuel", 214 + 16, 178);
        }
}


// Affiche la barre des boutons
void affichageBoutons()
{
    // Remplacement si besoin des param. visuels
    M5.Lcd.fillRect(0, 204, 320, 36, BLACK);
    M5.Lcd.fillRect(214,169,106,36,BLACK);

    // Affichage de la barre supérieure horizontale des boutons
    M5.Lcd.drawFastHLine(0, 204, 320, WHITE);

    //Affichage de la 2e barre horizontale à doite pour le 4e bouton
    M5.Lcd.drawFastHLine(214,169,106,WHITE);

    // Affichage des barres verticales à 1 et 2 tiers de l'écran pour la séparation des 4 boutons
    M5.Lcd.drawFastVLine(106, 204, 36, WHITE);
    M5.Lcd.drawFastVLine(214, 169, 71, WHITE);

    // Affichage du texte à l'intérieur des boutons
    affichageTexteBoutons();
}

// Affiche les distances en cours d'utilisation
void affichageDistances(bool init){
    if(init){
        M5.Lcd.drawString("Distances :", 240, 70);
    }
    // Distances longues par défaut
    if(!modeDistance){
        M5.Lcd.drawString("LONGUES", 240, 70);
    }else{
        // Sinon distances courtes
        M5.Lcd.drawString("COURTES", 240, 70);
    }

    //Affichage des distances au niveau de la légende
    M5.Lcd.drawNumber(limites[modeDistance][1], 300, 10);
    M5.Lcd.drawNumber(limites[modeDistance][0], 300, 40);

}

void buttonCheck()
{      
    // Met à jour les informations sur les boutons de la M5Stack
    M5.update();

    // BOUTON A 
    // Aller dans les paramètres visuels et les quitter
    if (M5.BtnA.wasPressed())
    {
        paramVisuels = !paramVisuels;
        affichageBoutons();
    }

    // BOUTON B
    // Activation mode sonore OU changer palette
    if (M5.BtnB.wasPressed())
    {
        if(!paramVisuels){
            modeSonore = !modeSonore;
            if(modeSonore){
                activerSonore();
            }
        }else{
            changerPalette();
        }
    }

    // BOUTON C
    // Activation mode haptique OU Activer LEDs
    if (M5.BtnC.wasPressed())
    {
        if(!paramVisuels){
            modeHaptique = !modeHaptique;
        }else{
            changerModeLED();
        }
    }

    // BOUTON A ET B
    // Permet d'éteindre la M5Stack, ce qui n'est pas possible sinon
    if (M5.BtnA.isPressed() && M5.BtnB.isPressed())
    {
        turnOffLEDs();
        M5.Power.deepSleep();
    }

    // BOUTON B ET C
    // Permet de changer le mode de distance OU désactiver le retour visuel par écran
    if(M5.BtnB.isPressed() && M5.BtnC.isPressed()){
        if(!paramVisuels){
            modeDistance = !modeDistance;
            affichageDistances(false);
        }else{
            modeVisuelEcran = !modeVisuelEcran;
            changerAffichageModeVisuel();
        }
    }
}

// FONCTIONS BLUETOOTHS

// Initialise le Bluetooth application
void initBluetoot(){
    // Démarrage du Bluetooth
    SerialBT.begin("M5Stack");
}

// Gère le Bluetooth avec l'application - ENCORE UN TEST !!!
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