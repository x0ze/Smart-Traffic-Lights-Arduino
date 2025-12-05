#include "sensor_pir.h"
#include <Arduino.h>

int pirStatus = 0;        // Current PIR state

// Initialize PIR pin
void initPIRSensor(int pirPin) {
    pinMode(pirPin, INPUT);
}

// Read PIR sensor state
int readPIR(int pirPin) {
    pirStatus = digitalRead(pirPin);
    return pirStatus;
}
