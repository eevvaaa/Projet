#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN       22
#define NUMPIXELS 35

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB);
#define DELAYVAL 100

#define RED pixels.Color(120,0,0)
#define YELLOW pixels.Color(170,150,0)
#define GREEN pixels.Color(0,180,120)

//Cette fonction sert pendant l'initialisation Setup du main
void initLED(){
    pixels.begin();
    pixels.setBrightness(10);
    pixels.clear();
}

void LEDLight(int number,int color) {
    if(color == 2){
        pixels.setPixelColor(number,GREEN);
    }else{
        if(color == 1){
            pixels.setPixelColor(number,YELLOW);
        }else{
            pixels.setPixelColor(number,RED);
        }
    }
}

void turnOffLEDs(){
    pixels.setBrightness(0);
    pixels.clear();
    pixels.show();
}

void updateLED() {
    pixels.show();
}