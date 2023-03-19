#include <M5Stack.h>
#include <sensors.h>
#include <BluetoothSerial.h>
#include <SPIFFS.h>
#include <led.h>

#define LIMITE_DANGER 10
#define LIMITE_WARNING 40
#define NBBOARD 2

BluetoothSerial SerialBT;
int mode;

void initAffichage();

void setup()
{
    // Init de la M5STack
    M5.begin(true, false, true, true);
    // Démarrage du SPIFFS permettant dl'affichage d'image
    SPIFFS.begin();
    // Démarrage de la M5Stack
    M5.Power.begin();

    // Taille de la police
    M5.Lcd.setTextSize(2);

    // Démarrage du Bluetooth
    SerialBT.begin("M5Stack");

    // Démarrage en mode 0 (affichage capteurs)
    mode = 0;

    // Si l'init des capteurs a réussi :
    if (initSensors())
    {
        M5.Lcd.print("MCP2515 Initialized\nSuccessfully!\n");
    }
    else
    {
        M5.Lcd.println("Error Initializing\nMCP2515...");
    }
    initAffichage();

    initLED();

}

void initAffichage()
{
    for (int i = 0; i < NBBOARD * 6; i++)
    {
        M5.Lcd.printf("Board[%d] :\n", (int)(i / 6));
    }
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

void displayImage()
{
    M5.Lcd.drawPngFile(SPIFFS, "/image.png", 19, 0);
}

void ButtonCheck()
{
    if (M5.BtnA.wasPressed())
    {
        turnOffLEDs();
        M5.Power.deepSleep();
    }

    if (M5.BtnC.wasPressed())
    {
        mode = (mode + 1) % 2;
        M5.Lcd.fillScreen(BLACK);

        if(mode = 0) {
            initAffichage();
        }else{
            displayImage();
        }

    }
}

void loop()
{
    M5.update();
    ButtonCheck();

    if (mode == 0)
    {
        if(processSensors()){
            getNewSensorValues();
            updateLED();
            // bluetoot();
        }
    }
}