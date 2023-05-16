#include <Adafruit_NeoPixel.h>
#include <sensors.h>
#include <math.h>

// DONNEES LIEES AUX LEDS --------------------------------------------------------

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 22
#define NUMPIXELS 35

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB);
#define DELAYVAL 100

#define ANGLE_LED (2 * M_PI / NUMPIXELS)

// Les LEDs du mode visuel ont 2 états aussi (désactivé par défaut):
int modeLED = 0;

// DONNEES LIEES AUX COULEURS DES LED --------------------------------------------

#define RED_L pixels.Color(200, 0, 0)
#define YELLOW_L pixels.Color(170, 150, 0)
#define CYAN_L pixels.Color(0, 180, 120)
#define MAROON_L pixels.Color(130, 30, 0)
#define MAGENTA_L pixels.Color(220, 0, 220)
#define GREEN_L pixels.Color(0, 180, 40)
#define BLUE_L pixels.Color(20, 0, 200)
#define WHITE_L pixels.Color(200, 200, 200)

uint32_t palettesLED[4][3] = {
    {CYAN_L, YELLOW_L, RED_L},      /*Défaut*/
    {MAGENTA_L, GREEN_L, RED_L},    /*Protanopie*/
    {GREEN_L, MAROON_L, MAGENTA_L}, /*Deuteranopie*/
    {BLUE_L, CYAN_L, RED_L}         /*Tritanopie*/
};

extern int pal;

// IMPORTS DES DONNES DES CAPTEURS -----------------------------------------------

// Distances limites
extern int limites[2][2];

// Choix type distances limites
extern bool modeDistance;

// Données venant des capteurs
extern int sensorValues[NBBOARD][6];

// Données sur les blocs de capteurs : x y angle
extern int blocs[NBBOARD][5];

// FONCTIONS ---------------------------------------------------------------------

// Met à jour l'affichage des LEDs
void updateLED()
{
    pixels.show();
}

// Permet de désactiver les LEDs
void turnOffLEDs()
{
    pixels.clear();
    pixels.show();
}

// Cette fonction sert pendant l'initialisation Setup du main
void initLED()
{
    pixels.begin();
    pixels.setBrightness(10);
    turnOffLEDs();
    updateLED();
}

// Fonction calculant le numéro de la LED centrale associée à un bloc
int calculNumeroLED(int bloc)
{
    /*
    int x = blocs[bloc][0];
    int y = blocs[bloc][1];
    // Calcule l'angle auquel est situé le bloc (arrondi à l'inférieur du centre)
    double angle = atan2(x,y);

    // Angle dans la partie inférieure du cercle
    if(y > 0){
        angle = M_PI - abs(angle);
    }

    // Angle dans la partie gauche du cercle
    if(x < 0){
        angle = 2*M_PI - abs(angle);
    }

    Serial.print(bloc);
    Serial.print(" : ");
    Serial.println(angle/ANGLE_LED);

    return (int) angle/ANGLE_LED;
    */
    return blocs[bloc][4];
}

// Fonction permettant de récupérer une couleur à partir d'une distance
uint32_t getCouleurLED(int dist)
{

    // Si < DANGER : Danger
    if (dist < limites[modeDistance][DANGER])
    {
        return palettesLED[pal][2];
    }

    // Sinon, si < ALERTE : Alerte
    if (dist < limites[modeDistance][ALERTE])
    {
        return palettesLED[pal][1];
    }

    // Sinon : Rien
    return palettesLED[pal][0];
}

// Fonction permettant l'affichage d'un bloc sur le bandeau de LEDs
// On modélise 1 bloc par 3 LEDs (donc 2 capteurs par LED)
// On affiche la couleur liée à la plus petite distance des 2 capteurs
void affichageLEDs(int bloc)
{

    // for(int j = 0 ; j < 4 ; j++){ /* bloc+2*j si test sur 2 capteurs */

    // Calcul de la LED centrale
    int led = calculNumeroLED(bloc);

    // Plus petite distance entre les deux capteurs modélisés par la LED
    int dist;
    // Couleur de la LED
    uint32_t couleur;

    for (int i = 0; i < 3; i++)
    {
        // Prend la plus petite distance
        dist = _min(sensorValues[bloc][2 * i], sensorValues[bloc][2 * i + 1]);

        // Calcul de la couleur associée
        couleur = getCouleurLED(dist);

        // Changement de la LED
        pixels.setPixelColor(led, couleur);

        // LED suivante
        led++;
        //}
    }

    updateLED();
}

void changerModeLED()
{
    // Alterne entre les modes
    modeLED = (modeLED + 1) % 2;

    if (!modeLED)
    {
        turnOffLEDs();
    }
    else
    {
        pixels.setPixelColor(0, WHITE_L);
        pixels.setPixelColor(34, WHITE_L);
    }
}