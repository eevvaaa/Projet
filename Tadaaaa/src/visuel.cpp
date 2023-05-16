#include <SPIFFS.h>
#include <M5Stack.h>
#include <sensors.h>
#include <led.h>

// DONNES LIEES AUX PALETTES DE COULEURS -----------------------------------------

uint16_t palettesVisuel[4][3] = {
    {CYAN, YELLOW, RED},      /*Défaut*/
    {MAGENTA, GREEN, RED},    /*Protanopie*/
    {GREEN, MAROON, MAGENTA}, /*Deuteranopie*/
    {BLUE, CYAN, RED}         /*Tritanopie*/
};

// Palette de couleur utilisée, init à "Par défaut"
int pal = 0;

// IMPORTS DEPUIS SENSORS --------------------------------------------------------

// Distances limites
extern int limites[2][2];

// Choix type distances limites
extern int modeDistance;

// Données venant des capteurs
extern int sensorValues[NBBOARD][6];

// Données sur les blocs de capteurs : x y angle
extern int blocs[NBBOARD][5];

// DONNEES RELATIVES A L'AFFICHAGE D'IMAGES --------------------------------------

// Dimensions image : largeur et hauteur
#define FAUTEUIL_L 80
#define FAUTEUIL_H 120

// Position centrée image en x et y
#define FAUTEUIL_X 113
#define FAUTEUIL_Y 98

// MODE VISUEL ACTIF -----------------------
// Initialisé à 1 (activé)
bool modeVisuelEcran = 1;

// FONCTIONS ---------------------------------------------------------------------

// Permet d'afficher la légende sur le côté
void affichageLegende()
{
    // Danger
    M5.Lcd.fillRect(285, 10, 6, 6, palettesVisuel[pal][2]);

    // Alerte
    M5.Lcd.fillRect(285, 25, 6, 6, palettesVisuel[pal][1]);

    // Rien
    M5.Lcd.fillRect(285, 40, 6, 6, palettesVisuel[pal][0]);
}

// Permet de gérer l'initialisation du mode visuel
void changerAffichageModeVisuel()
{   
    // Si le mode visuel écran est activé, alors afficher
    if(modeVisuelEcran){
        // Affichage image fauteuil
        M5.Lcd.drawPngFile(SPIFFS, "/fauteuil.png", FAUTEUIL_X - FAUTEUIL_L / 2, FAUTEUIL_Y - FAUTEUIL_H / 2);

        // Petite police
        M5.Lcd.setTextSize(1);

        // Affichage du texte
        M5.Lcd.drawString("Danger", 240, 10);
        M5.Lcd.drawString("Alerte", 240, 25);
        M5.Lcd.drawString("  Rien", 240, 40);

        // Police normale
        M5.Lcd.setTextSize(2);

        // Affichage couleurs correspondantes
        affichageLegende();
    }else{
        // Désactivation du mode visuel -> suppression (on laisse la légende en cas de LED)
        M5.Lcd.fillRect(40,20,145,145,BLACK);
    }
}

// Fonction permettant de récupérer une couleur à partir d'une distance
uint16_t getCouleur(int dist)
{

    // Si < DANGER : Danger
    if (dist < limites[modeDistance][DANGER])
    {
        return palettesVisuel[pal][2];
    }

    // Sinon, si < ALERTE : Alerte
    if (dist < limites[modeDistance][ALERTE])
    {
        return palettesVisuel[pal][1];
    }

    // Sinon : Rien
    return palettesVisuel[pal][0];
}

// Permet d'afficher un bloc ; les blocs vont de 0 à NBBOARD - 1
// L'affichage est réalisé en prenant un point de départ (x y ajustés)
// Et en le décalant à chaque capteur dans la boucle de (sensX, sensY)
// On peut ainsi former des blocs verticaux, horizontaux ou même diagonaux,
// dans le bon sens d'affichage
int affichageBloc(int bloc)
{
    // for(int j = 0 ; j < 4 ; j++){ /* bloc+j*2 quand test sur 2 capteurs */
    int x = blocs[bloc][0];
    int y = blocs[bloc][1];
    int sensX = blocs[bloc][2];
    int sensY = blocs[bloc][3];

    // Réajustement
    x = x - 1 + FAUTEUIL_X - 5 * (sensX);
    y = y - 1 + FAUTEUIL_Y - 5 * (sensY);

    // Pour chaque capteur du bloc, faire
    for (int i = 0; i < 6; i++)
    {
        // Afficher
        M5.Lcd.fillRect(x, y, 2, 2, getCouleur(sensorValues[bloc][i]));

        // Actualiser x et y
        x = x + 2 * sensX;
        y = y + 2 * sensY;
    }
    //}
    // Pour test Bluetooth
    return sensorValues[bloc][0];
}

void changerPalette()
{
    // Va à la palette suivante sur les 4 palettes
    pal = (pal + 1) % 4;

    // Affiche la nouvelle légende
    affichageLegende();

    for (int i = 0; i < NBBOARD; i++)
    {   
        if(modeVisuelEcran){
            affichageBloc(i);
        }
        affichageLEDs(i);
    }
}