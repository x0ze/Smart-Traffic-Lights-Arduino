#include "wifi_server.h"
#include "sensor_pir.h"
#include "settings.h"
#include "parser.h"
#include "send_http_response.h"

void setup() {
    Serial.begin(9600);

    initWiFiServer();   // Initialize WiFi and web server
    initPIRSensor();    // Initialize PIR motion sensor
}

void loop() {
    readPIR();          // Read PIR sensor state
    handleWebServer();  // Handle HTTP clients and POST requests
}
