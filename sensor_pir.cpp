#include "sensor_pir.h"
#include <Arduino.h>

const int pirPin = 2;     // Pin connected to PIR sensor
int pirStatus = 0;        // Current PIR state

// Initialize PIR pin
void initPIRSensor() {
    pinMode(pirPin, INPUT);
}

// Read PIR sensor state
int readPIR() {
    pirStatus = digitalRead(pirPin);
    return pirStatus;
}
