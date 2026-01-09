#include "traffic_light.h"
#include <Arduino.h>

const int RIGHT_RED_PIN = 2;
const int RIGHT_AMBER_PIN = 3;
const int RIGHT_GREEN_PIN = 4;

const int LEFT_RED_PIN = 5;
const int LEFT_AMBER_PIN = 6;
const int LEFT_GREEN_PIN = 7;

LightState leftLightState = GREEN;
LightState rightLightState = RED;

void initLight() {
    pinMode(RIGHT_RED_PIN, OUTPUT);
    pinMode(RIGHT_AMBER_PIN, OUTPUT);
    pinMode(RIGHT_GREEN_PIN, OUTPUT);

    pinMode(LEFT_RED_PIN, OUTPUT);
    pinMode(LEFT_AMBER_PIN, OUTPUT);
    pinMode(LEFT_GREEN_PIN, OUTPUT);
}

void setRed(Side side) {
    if (side == RIGHT) {
        digitalWrite(RIGHT_RED_PIN, HIGH);
        digitalWrite(RIGHT_AMBER_PIN, LOW);
        digitalWrite(RIGHT_GREEN_PIN, LOW);
        rightLightState = RED;
    } else if (side == LEFT) {
        digitalWrite(LEFT_RED_PIN, HIGH);
        digitalWrite(LEFT_AMBER_PIN, LOW);
        digitalWrite(LEFT_GREEN_PIN, LOW);
        leftLightState = RED;
    }
}

void setRedAndAmber(Side side) {
    if (side == RIGHT) {
        digitalWrite(RIGHT_RED_PIN, HIGH);
        digitalWrite(RIGHT_AMBER_PIN, HIGH);
        digitalWrite(RIGHT_GREEN_PIN, LOW);
        rightLightState = RED_AND_AMBER;
    } else if (side == LEFT) {
        digitalWrite(LEFT_RED_PIN, HIGH);
        digitalWrite(LEFT_AMBER_PIN, HIGH);
        digitalWrite(LEFT_GREEN_PIN, LOW);
        leftLightState = RED_AND_AMBER;
    }
}

void setAmber(Side side) {
    if (side == RIGHT) {
        digitalWrite(RIGHT_RED_PIN, LOW);
        digitalWrite(RIGHT_AMBER_PIN, HIGH);
        digitalWrite(RIGHT_GREEN_PIN, LOW);
        rightLightState = AMBER;
    } else if (side == LEFT) {
        digitalWrite(LEFT_RED_PIN, LOW);
        digitalWrite(LEFT_AMBER_PIN, HIGH);
        digitalWrite(LEFT_GREEN_PIN, LOW);
        leftLightState = AMBER;
    }
}

void setGreen(Side side) {
    if (side == RIGHT) {
        digitalWrite(RIGHT_RED_PIN, LOW);
        digitalWrite(RIGHT_AMBER_PIN, LOW);
        digitalWrite(RIGHT_GREEN_PIN, HIGH);
        rightLightState = GREEN;
    } else if (side == LEFT) {
        digitalWrite(LEFT_RED_PIN, LOW);
        digitalWrite(LEFT_AMBER_PIN, LOW);
        digitalWrite(LEFT_GREEN_PIN, HIGH);
        leftLightState = GREEN;
    }
}