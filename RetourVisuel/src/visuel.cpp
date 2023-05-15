#include <SPIFFS.h>
#include <M5Stack.h>
#include <sensors.h>
#include <led.h>

// VARIABLES LIEES AUX PALETTES DE COULEURS ---------------------------

uint16_t palettes[4][3] = {
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
extern int d;

// Données venant des capteurs
extern int sensorValues[NBBOARD][6];

// Données sur les blocs de capteurs : x y angle
extern int blocs[NBBOARD][4];

// DONNEES RELATIVES A L'AFFICHAGE D'IMAGES --------------------------------------

// Dimensions image : largeur et hauteur
#define FAUTEUIL_L 80
#define FAUTEUIL_H 120

// Position centrée image en x et y
#define FAUTEUIL_X 113
#define FAUTEUIL_Y 98

// FONCTIONS ---------------------------------------------------------------------

// Permet d'afficher les paramètres sur le côté
void affichageParametres()
{
    // Remplace les boutons classiques Vis/Son/Hapt

    M5.Lcd.fillRect(0, 205, 105, 35, BLACK);
    M5.Lcd.drawString("Quitter", 12, 214);

    M5.Lcd.fillRect(107, 205, 105, 35, BLACK);
    M5.Lcd.drawString("Palette", 106 + 14, 214);

    M5.Lcd.fillRect(215, 205, 105, 35, BLACK);
    M5.Lcd.drawString("LEDs", 214 + 30, 214);
}

// Permet d'afficher la légende sur le côté
void affichageLegende()
{
    // Danger
    M5.Lcd.fillRect(285, 10, 6, 6, palettes[pal][2]);

    // Alerte
    M5.Lcd.fillRect(285, 25, 6, 6, palettes[pal][1]);

    // Rien
    M5.Lcd.fillRect(285, 40, 6, 6, palettes[pal][0]);
}

// Permet de gérer l'initialisation du mode visuel
void affichageModeVisuel()
{
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
}

// Fonction permettant de récupérer une couleur à partir d'une distance
uint16_t getCouleur(int dist)
{

    // Si < DANGER : Danger
    if (dist < limites[d][DANGER])
    {
        return palettes[pal][2];
    }

    // Sinon, si < ALERTE : Alerte
    if (dist < limites[d][ALERTE])
    {
        return palettes[pal][1];
    }

    // Sinon : Rien
    return palettes[pal][0];
}


// Permet d'afficher un bloc ; les blocs vont de 0 à NBBOARD - 1
// L'affichage est réalisé en prenant un point de départ (x y ajustés)
// Et en le décalant à chaque capteur dans la boucle de (sensX, sensY)
// On peut ainsi former des blocs verticaux, horizontaux ou même diagonaux,
// dans le bon sens d'affichage
int affichageBloc(int bloc)
{   
    //for(int j = 0 ; j < 4 ; j++){
        int x = blocs[bloc][0];
        int y = blocs[bloc][1]; 
        int sensX = blocs[bloc][2]; 
        int sensY = blocs[bloc][3]; 

        // Réajustement
        x = x - 1 + FAUTEUIL_X - 5*(sensX); 
        y = y - 1 + FAUTEUIL_Y - 5*(sensY); 

        // Pour chaque capteur du bloc, faire
        for (int i = 0; i < 6; i++)
        {
            // Afficher
            M5.Lcd.fillRect(x, y, 2, 2, getCouleur(sensorValues[bloc][i]));
            
            // Actualiser x et y
            x = x + 2*sensX;
            y = y + 2*sensY;
        }

        return sensorValues[bloc][0];
    //}
}

void changerPalette()
{
    // Va à la palette suivante sur les 4 palettes
    pal = (pal + 1) % 4;

    // Affiche la nouvelle légende
    affichageLegende();
}