#include <Arduino.h>
#include <M5Stack.h>
#include <sensors.h>
#include "BluetoothA2DPSource.h"
#include "sonore.h"

extern BluetoothA2DPSource headphones;

void setup()
{
  // Init de la M5Stack
  M5.begin(true, false, true, true);

  // Démarrage de la M5Stack
  M5.Power.begin();

  M5.Lcd.setTextSize(2.5);

}

void loop(){
  M5.update();

  if(processSensors()){
    getNewSensorValues();
  }
}