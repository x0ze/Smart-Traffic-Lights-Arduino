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
    int statusLeft = 0;
    int statusRight = 0;

    if (distanceLeft <= 10) {
        statusLeft = 1;
    }
    if (statusRight <= 10) {
        statusRight = 1;
    }
    // Dynamic traffic light management (automatic time calculation)
    Serial.println(statusRight);
    Serial.println(statusLeft);
    start_dynamic(statusLeft, statusRight);

    // Manage HTTP requests (remote update + speed)
    handleWebServer();
}
