#include <M5Stack.h>
#include <sensors.h>
#include <BluetoothSerial.h>
#include <SPIFFS.h>

#define LIMITE_DANGER 10
#define LIMITE_WARNING 40

BluetoothSerial SerialBT;
int mode;


void setup(){
    // Init de la M5STack
    M5.begin(true, false, true, true);
    // Démarrage du SPIFFS permettant dl'affichage d'image
    SPIFFS.begin();
    // Démarrage de la M5Stack
    M5.Power.begin();

    //Taille de la police 
    M5.Lcd.setTextSize(2);

    // Démarrage du Bluetooth
    SerialBT.begin("M5Stack");

    //Démarrage en mode 0 (affichage capteurs)
    mode = 0;

    // Si l'init des capteurs a réussi :
    if(initSensors()){
        M5.Lcd.print("MCP2515 Initialized\nSuccessfully!");
    }else{
        M5.Lcd.println("Error Initializing MCP2515...");
    }
}

void afficheCapteurBT(){
    for(int i = 0 ; i<2 ; i++){
        int values[6];
        for(int j = 0 ; j < 6 ; j++){
            int hauteur = (2+6*i+j)*16;
            M5.Lcd.setCursor(0,hauteur);

            // s'il y a update des données, alors traiter le tableau du demi capteur
            if(getNewSensorValues(i, values)){
                M5.Lcd.printf("Board[%d] : ",i);
                M5.Lcd.printf("%d ", values[j]);

                // Affichage du carré représenté par le capteur
                if(values[j] < LIMITE_DANGER){
                        M5.Lcd.fillRect(220-10*(i+j == 0 || i+j == 6),hauteur+2, 5, 5, RED);
                    } else {
                        if(values[j] < LIMITE_WARNING && values[j] >= LIMITE_DANGER){
                            M5.Lcd.fillRect(220-10*(i+j == 0 || i+j == 6), hauteur+2, 5, 5, YELLOW);
                        } else {
                            M5.Lcd.fillRect(220-10*(i+j == 0 || i+j == 6), hauteur+2, 5, 5, GREEN);
                        }
                    }

                // Envoi des infos du capteur 0 en bluetooth    
                if(i == 0 && j == 0){
                    SerialBT.printf("%d\n",values[j]);
                }
            }
        }
    }
}

void bluetoot(){
    if(M5.BtnB.read()){
        SerialBT.println("Hello world, from M5Stack - Key B!");
    }

    M5.Lcd.setCursor(0,0);

    if(SerialBT.available()){
        char ch = SerialBT.read();
        if(ch == 'c'){
            M5.Lcd.print("Connection made with smartphone successfully !");
        }
    }
}

void displayImage(){
    M5.Lcd.drawPngFile(SPIFFS,"/image.png",19,0);
}


void ButtonCheck(){
    if(M5.BtnA.wasPressed()){
        M5.Power.deepSleep();
    }

    if(M5.BtnC.wasPressed()){
        mode = (mode + 1) % 2;
        M5.Lcd.fillScreen(BLACK);
    }
}


void loop(){
    M5.update();
    ButtonCheck();

    processSensors();

    if(mode == 0){
        afficheCapteurBT();
        bluetoot();
    }else{
        if(mode == 1 && M5.BtnC.wasPressed()){
            displayImage();
        }
    }
}