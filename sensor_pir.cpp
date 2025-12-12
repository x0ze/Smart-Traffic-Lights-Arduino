#include "sensor_pir.h"
#include <Arduino.h>

int pirStatus = 0;        // Current PIR state

int distanceSensor;
long duration;

// Initialize PIR pin
void initSensor(int trigPin, int echoPin) {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

// Read PIR sensor state
int readSensor(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    
    distanceSensor = duration * 0.034 / 2;

    return distanceSensor;
}
