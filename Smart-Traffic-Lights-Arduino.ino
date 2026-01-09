#include "wifi_server.h"
#include "ultrasonic_sensor.h"

void setup() {
    Serial.begin(9600);
    initWiFiAP();
}

void loop() {
    updateSensorDistance();
    handleWebServer();
}