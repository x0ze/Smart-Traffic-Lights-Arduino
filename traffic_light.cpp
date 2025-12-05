#include "traffic_light.h"
#include <Arduino.h>

void setRed(int pin) {
    digitalWrite(pin, HIGH);
}

void setOrange(int pin) {
    digitalWrite(pin, HIGH);
}

void setGreen(int pin) {
    digitalWrite(pin, HIGH);
}

void turnOffAll(int redPin, int orangePin, int greenPin) {
    digitalWrite(redPin, LOW);
    digitalWrite(orangePin, LOW);
    digitalWrite(greenPin, LOW);
}