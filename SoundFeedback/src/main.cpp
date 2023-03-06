#include <Arduino.h>
#include <M5Stack.h>
#include <BLEDevice.h>
#include <BluetoothSerial.h>
#include <sensors.h>

#define WARNING 60
#define DANGER 30

#define sensorPin 1

BLEDevice BLE;

void setup(){
  pinMode(sensorPin, OUTPUT);
  M5.begin();
  BLE.begin();

  M5.begin(true, false, true, true);
    M5.Power.begin();
    if(initSensors())
        Serial.println("MCP2515 Initialized Successfully!");
    else
        Serial.println("Error Initializing MCP2515...");


}

void loop(){
  //code Prof
  processSensors();
    for(int i = 0 ; i < 2 ; i++){
        int values[6];
        if(getNewSensorValues(i, values)){
            Serial.printf("Board[%d] : ", i);
            for(int j = 0 ; j < 6 ; j++){
                Serial.printf("%d ", values[j]);
            }
            Serial.printf("\n");
        }
    }




  BLEScanResults results = BLE.scan(5);
  int valeurSensors = analogRead(sensorPin);

  for(int i = 0; i<results.getCount(); i++){
    BLEAdvertisedDevice advertisedDevice = results.getDevice(i);
    M5.Lcd.print(advertisedDevice.getName().c_str());
  }

  while(valeurSensors<=DANGER){ //Capteurs à moins de 30 cm du danger, son à émettre en continu
    tone(sensorPin, 1000); //Fréquence de 1000 Hz mais à déterminer 
    delay(500);
    valeurSensors = analogRead(sensorPin); //On récupère à chaque fois la distance
  }

  while(valeurSensors>=WARNING && valeurSensors<DANGER){
    tone(sensorPin, 500); //Valeur de fréquence à déterminer
    delay(500); //Pas de son en continu mais bip pour annoncer qu'on s'approche d'un danger

  }
  noTone(sensorPin);
}