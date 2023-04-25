#include <M5Stack.h>
#include <sensors.h>
#include "BluetoothA2DPSource.h"

#define c3_frequency  130.81
BluetoothA2DPSource a2dp_source;

int32_t get_data_channels(Frame *frame, int32_t channel_len) {
    static double m_time = 0.0;
    double m_amplitude = 10000.0;  // -32,768 to 32,767
    double m_deltaTime = 1.0 / 44100.0;
    double m_phase = 0.0;
    double double_Pi = PI * 2.0;
    // fill the channel data
    for (int sample = 0; sample < channel_len; ++sample) {
        double angle = double_Pi * c3_frequency * m_time + m_phase;
        frame[sample].channel1 = m_amplitude * sin(angle);
        frame[sample].channel2 = frame[sample].channel1;
        m_time += m_deltaTime;
    }

    return channel_len;
}

void setup() {
    // Init de la M5STack
    M5.begin(true, false, true, true);
    
    // Démarrage de la M5Stack
    M5.Power.begin();

    M5.Lcd.println("Hello");
    
    a2dp_source.start("OpenMove by Shokz", get_data_channels);  
    if(a2dp_source.is_connected()){
        M5.Lcd.println("Connexion réussie");
    }
    a2dp_source.set_volume(30);
}

void loop(){
    delay(10);
}