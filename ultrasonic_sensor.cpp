#include "ultrasonic_sensor.h"
#include "dynamic_algorithm.h"
#include <Arduino.h>

const float SPEED_OF_SOUND = 0.034;
const int LEFT_TRIG_PIN = 12;     // Left pin connected to sensor
const int LEFT_ECHO_PIN = 9;     // Left pin connected to sensor
const int RIGHT_TRIG_PIN = 11;    // Right pin connected to sensor
const int RIGHT_ECHO_PIN = 10;     // Left pin connected to sensor

void initSensor() {
    pinMode(LEFT_TRIG_PIN, OUTPUT);
    pinMode(LEFT_ECHO_PIN, INPUT);
    pinMode(RIGHT_TRIG_PIN, OUTPUT);
    pinMode(RIGHT_ECHO_PIN, INPUT);
}

// Read PIR sensor state
float readSensor(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    float duration = pulseIn(echoPin, HIGH);
    float distance = duration * SPEED_OF_SOUND / 2;

    return distance;
}

void updateSensorDistance() {
    float distanceLeft = readSensor(LEFT_TRIG_PIN, LEFT_ECHO_PIN);
    float distanceRight = readSensor(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN);
        
    updateLights(distanceLeft <= 10, distanceRight <= 10);
}
