#include "wifi_server.h"
#include "sensor_pir.h"
#include "settings.h"
#include "parser.h"
#include "algo_dynamic.h"
#include "send_http_response.h"

const int trigPinLeft = 12;     // Left pin connected to sensor
const int echoPinLeft = 9;     // Left pin connected to sensor
const int trigPinRight = 11;    // Right pin connected to sensor
const int echoPinRight = 10;     // Left pin connected to sensor

int distanceLeft;
int distanceRight;
bool carOnLeft;
bool carOnRight;

void setup() {
    Serial.begin(9600);

    initWiFiServer();           // Initialize WiFi + Web Server
    initSensor(trigPinLeft,echoPinLeft);  // Left Sensor
    initSensor(trigPinRight,echoPinRight); // Right Sensor
    pinMode(4, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
}

void loop() {
    // Read the Sensors
    distanceLeft = readSensor(trigPinLeft, echoPinLeft);
    distanceRight = readSensor(trigPinRight, echoPinRight);
    
    carOnLeft = false;
    carOnRight = false;

    if (distanceLeft <= 10) {
        carOnLeft = 1;
    }
    if (distanceRight <= 10) {
        carOnRight = 1;
    }
    // Dynamic traffic light management (automatic time calculation)
    Serial.println(carOnRight);
    Serial.println(carOnLeft);
    start_dynamic(carOnLeft, carOnRight);

    // Manage HTTP requests (remote update + speed)
    handleWebServer();
}
