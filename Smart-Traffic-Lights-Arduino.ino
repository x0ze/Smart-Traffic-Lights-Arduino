#include "wifi_server.h"
#include "ultrasonic_sensor.h"
#include "traffic_light.h"

void setup() {
    Serial.begin(9600);
    initWiFiAP();
    initSensor();
    initLight();
}

void loop() {
    updateSensorDistance();
    handleWebServer();
}