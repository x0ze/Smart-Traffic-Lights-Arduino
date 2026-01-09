#include "form_data_parser.h"
#include <Arduino.h>

float distance = 100.0;
float minSpeed = 60.0;

// Extract distance and speed values from HTTP request
void parseForm(String data) {
    int dIndex = data.indexOf("distance=");
    if(dIndex != -1) {
        int amp = data.indexOf('&', dIndex);
        String d = data.substring(dIndex + 9, amp);
        distance = d.toFloat();
        Serial.print("Distance set to: "); Serial.println(distance);
    }

    int sIndex = data.indexOf("speed=");
    if(sIndex != -1) {
        String s = data.substring(sIndex + 6);
        minSpeed = s.toFloat();
        Serial.print("Speed set to: "); Serial.println(minSpeed);
    }
}
