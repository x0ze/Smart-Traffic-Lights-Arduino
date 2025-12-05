#include "parser.h"
#include "settings.h"
#include <Arduino.h>

// Extract distance and speed values from HTTP request
void parseForm(String data) {
    int dIndex = data.indexOf("distance=");
    if(dIndex != -1) {
        int amp = data.indexOf('&', dIndex);
        String d = data.substring(dIndex + 9, amp);
        setDistance(d.toFloat());
        Serial.print("Distance set to: "); Serial.println(getDistance());
    }

    int sIndex = data.indexOf("speed=");
    if(sIndex != -1) {
        String s = data.substring(sIndex + 6);
        setMaxSpeed(s.toFloat());
        Serial.print("Speed set to: "); Serial.println(getMaxSpeed());
    }
}
